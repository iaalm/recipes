export PREFIX=/home/simon/workspace/msp430/mspgcc
export MAKEFLAGS='-j 5'

# extract all the following files into the msp430-build directory
tar xvfj binutils-2.21.1a.tar.bz2
tar xvfj gcc-core-4.6.3.tar.bz2
tar xvfj gdb-7.2a.tar.bz2
tar xvfj mspgcc-20120406.tar.bz2
tar xvfj msp430mcu-20120406.tar.bz2
tar xvfj msp430-libc-20120224.tar.bz2

cd gcc-4.6.3
tar xvfj ../mpfr-2.4.2.tar.bz2
ln -sf mpfr-2.4.2 mpfr
tar xvfj ../gmp-4.3.2.tar.bz2
ln -sf gmp-4.3.2 gmp
tar xvfz ../mpc-0.8.1.tar.gz
ln -sf mpc-0.8.1 mpc

# Return to the build directory
cd ..

# The next line is optional for the debugger and is not officially part of the mspgcc project.
tar xvfz mspdebug-0.19.tar.gz

# patch binutils (using the files provided in the Release Files, and repeat for any additional patches or LTS files)
cd binutils-2.21.1
# Patch binutils to bring it to Release 20120406 (still at 20120406)
patch -p1<../mspgcc-20120406/msp430-binutils-2.21.1a-20120406.patch


# Return to the build directory
cd ..

# patch GCC to bring it up to Release 20120406
cd gcc-4.6.3
patch -p1<../mspgcc-20120406/msp430-gcc-4.6.3-20120406.patch

# update with LTS files
patch -p1<../msp430-gcc-4.6.3-20120406-sf3540953.patch
patch -p1<../msp430-gcc-4.6.3-20120406-sf3559978.patch

# Return to the build directory
cd ..

# Patch GDB to bring it to release 20120406
cd gdb-7.2
patch -p1<../mspgcc-20120406/msp430-gdb-7.2a-20111205.patch

# Return to the build directory
cd ..

#Create a sub-set of Build Directories
mkdir binutils-2.21.1-msp430
mkdir gcc-4.6.3-msp430
mkdir gdb-7.2-msp430

# Configure Binutils
cd binutils-2.21.1-msp430
# We need to build binutils for the msp430
../binutils-2.21.1/configure --target=msp430 --program-prefix="msp430-" --prefix=$PREFIX

make
# Do the install as root (e.g., sudo)
make install

#  I have seen issues where the msp430-ranlib doesn't get detected correctly causing build issues later.
#  if that happens uncomment the following:
#  cd /usr/bin
#  sudo ln -s /usr/local/bin/msp430-ranlib

#Configure GCC
cd ../gcc-4.6.3-msp430
../gcc-4.6.3/configure --target=msp430 --enable-languages=c --program-prefix="msp430-"  --prefix=$PREFIX


make
# Do the install as root (e.g., sudo)
make install

#Configure GDB

cd ../gdb-7.2-msp430
../gdb-7.2/configure --target=msp430 --program-prefix="msp430-"  --prefix=$PREFIX


make
# Do the install as root (e.g., sudo)
make install

#Install the mspgcc-mcu files
cd ../msp430mcu-20120406
MSP430MCU_ROOT=`pwd` ./scripts/install.sh $PREFIX

# Install the mspgcc-libc
cd ../msp430-libc-20120224

#  If you need to disable features, run configure here with any of the following flags to enable/disable features.
#  --disable-printf-int64 : Remove 64-bit integer support to printf formats
#  --disable-printf-int32 : Remove 32-bit integer support from printf formats
#  --enable-ieee754-errors : Use IEEE 754 error checking in libfp functions

cd src
make 
# Do the install as root (e.g., sudo)
PATH=$PATH make PREFIX=$PREFIX install
cd ..

# Now let's build the debugger
cd ../mspdebug-0.19
PREFIX=$PREFIX make 
# Do the install as root (e.g., sudo)
make install
cd ../..

# ALL DONE

