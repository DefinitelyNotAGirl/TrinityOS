dd if=/dev/zero of=geos.img bs=512 count=131072
echo -e "o\nn\np\n1\n2048\n\na\nw\n" | fdisk geos.img

umount /mnt/GEOS_dev0
umount /mnt/GEOS_dev1

losetup /dev/loopG0 geos.img
losetup /dev/loopG1 geos.img -o 1048576

mkfs.ext4 /dev/loopG1

mount /dev/loopG1 /mnt/GEOS_dev1
