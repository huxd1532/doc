#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>

int main (void)
{
    struct udev *udev;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *dev_list_entry;
    struct udev_device *dev;

    struct udev_monitor *mon;
    int fd;
    
    /*创建udev library context*/
    udev = udev_new();
    if (!udev) {
        printf("Can't create udev\n");
        exit(1);
    }

    /*创建一个monitor,用于监控设备热拔插*/
    mon = udev_monitor_new_from_netlink(udev, "udev");
    /*添加监控过滤条件，只监控subsystem 为input的设备*/
    udev_monitor_filter_add_match_subsystem_devtype(mon, "input", NULL);
    /*开启监控*/
    udev_monitor_enable_receiving(mon);

    /*获取monitor对应的文件描述符*/
    fd = udev_monitor_get_fd(mon);

    /*创建遍历器enumerate*/
    enumerate = udev_enumerate_new(udev);
    /*添加遍历条件*/
    udev_enumerate_add_match_subsystem(enumerate, "input");
    /*扫描满足遍历条件的设备*/
    udev_enumerate_scan_devices(enumerate);
    /*获取扫描的遍历链表*/
    devices = udev_enumerate_get_list_entry(enumerate);
    /*遍历设备*/
    udev_list_entry_foreach(dev_list_entry, devices) {
        const char *path;
	  dev_t devnum;
        /*获取设sysfs下的路径*/
        path = udev_list_entry_get_name(dev_list_entry);
        /*根据sys路径创建udevs设备映射*/
        dev = udev_device_new_from_syspath(udev, path);

	 devnum = udev_device_get_devnum(dev);

        printf("Sys path:%s\n", path);
        printf("Dev node: %s\n", udev_device_get_devnode(dev));
        printf("Major id:%d\n", major(devnum));
	 printf("Minor id:%d\n", minor(devnum));
	 printf("\n\n");
	/*释放udev_device*/
        udev_device_unref(dev);
    }
    /*释放遍历器*/
    udev_enumerate_unref(enumerate);
    

    while (1) {

        fd_set fds;
        struct timeval tv;
        int ret;
        
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        tv.tv_sec = 100;
        tv.tv_usec = 0;
        
        /*监控设备热拔插*/
        ret = select(fd+1, &fds, NULL, NULL, &tv);
        
        if (ret > 0 && FD_ISSET(fd, &fds)) {
            
            dev = udev_monitor_receive_device(mon);
            if (dev) {
                printf("***********************\n");
                printf("Got Device\n");
                printf(" Node: %s\n", udev_device_get_devnode(dev));
                printf(" Subsystem: %s\n", udev_device_get_subsystem(dev));
                printf(" Devtype: %s\n", udev_device_get_devtype(dev));
                printf(" Action: %s\n", udev_device_get_action(dev));
                printf("***********************\n\n");
                udev_device_unref(dev);
            }
            else {
                printf("No Device from receive_device(). An error occured.\n");
            }                    
        }
    }
    udev_unref(udev);

    return 0;
}