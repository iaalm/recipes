dest=${2:-"/dev/sdb"}
if [ -b /dev/sdb ] ; then
	sudo dd if=$1 of=$dest seek=3862510
	sync
else
	echo $dest is not exists!
fi
