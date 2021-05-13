set -x
/usr/bin/xfbinst_x64 "(hd1)" format --fat32 --align --force
/usr/bin/xfbinst_x64 "(hd1)" add-menu fb.cfg /usr/bin//xsys/1622db802c9a725aa212036e88f64e66.cfg
sleep 1
udisksctl unmount -b /dev/sdb1
partprobe  /dev/sdb
sleep 1
/sbin/fsck -y /dev/sdb1
isoinfo -i /home/sfs/Downloads/uniontechos-desktop-20-professional-1030_amd64.iso -d
/sbin/fatlabel  /dev/sdb1 UOS
/bin/syslinux  -i /dev/sdb1
dd  if=/dev/sdb1 of=/usr/bin//xsys/3e1fdf417f1580879e5af87f7834de5b.bin bs=512 count=1
umount -v -f /dev/sdb1
/usr/bin/xfbinst_x64  "(hd1)" add ldlinux.bin /usr/bin//xsys/3e1fdf417f1580879e5af87f7834de5b.bin -s
sleep 1
date >> /tmp/oldtest.txt
mkdir  -p /usr/bin//usr/bin//xsys/766170d96e6b1374bac9d6120f0498bd
chmod  a+wrx /usr/bin//usr/bin//xsys/766170d96e6b1374bac9d6120f0498bd
mount /dev/sdb1 /usr/bin//xsys/88e781742133147a3a9b799ce63cd35d
7z x -y /home/sfs/Downloads/uniontechos-desktop-20-professional-1030_amd64.iso -o/usr/bin/xsys/88e781742133147a3a9b799ce63cd35d -bsp2
sync
date >> /tmp/oldtest.txt
#bash -c "udisksctl power-off -b /dev/sdb?*"


