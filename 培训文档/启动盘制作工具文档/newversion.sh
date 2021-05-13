set -x
udisksctl unmount -b /dev/sdb1
sleep 1
sudo mkfs.fat /dev/sdb1
sudo dd if=/usr/lib/syslinux/mbr/mbr.bin of=/dev/sdb bs=440 count=1
sudo syslinux -i /dev/sdb1
sudo fsck -y /dev/sda1
sudo sfdisk -A /dev/sdb 1
sudo fatlabel /dev/sdb1 "UOS 20"
date >> /tmp/newtest.txt
mkdir  -p /usr/bin//usr/bin//xsys/766170d96e6b1374bac9d6120f0498bd
chmod  a+wrx /usr/bin//usr/bin//xsys/766170d96e6b1374bac9d6120f0498bd
mount /dev/sdb1 /usr/bin//xsys/88e781742133147a3a9b799ce63cd35d
sleep 1
7z x -y /home/sfs/Downloads/uniontechos-desktop-20-professional-1030_amd64.iso -o/usr/bin/xsys/88e781742133147a3a9b799ce63cd35d -bsp2
sync
date >> /tmp/newtest.txt

