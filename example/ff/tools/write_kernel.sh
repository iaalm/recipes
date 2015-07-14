dest=${2:-"/dev/sdb"}
if [ -b /dev/sdb ] ; then
	sudo dd if=$1 of=$dest
	sync
else
	echo $dest is not exists!
fi
