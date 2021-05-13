https://xcb.freedesktop.org/manual/group__XCB____API.html
https://xcb.freedesktop.org/XcbApi/
https://xcb.freedesktop.org/manual/modules.html

# 一、数据结构
## 1、xcb_connection_t
* 包含了xcb与ｘ服务通信的所需的所有信息，定义在xcbint.h头文件中。

## ２、xcb_extension_t

## 3、xcb_auth_info_t
* 存放发送放到Ｘ服务的授权信息，定义在xcb.h头文件中：
```
typedef struct xcb_auth_info_t {
	int namelen;
	char *name;
	int datalen;
	char *data;
} xcb_auth_info_t;
```

# 二、函数接口
## 1、xcb_connect
## 2、xcb_connect_to_display_with_auth_info
## 3、xcb_connect_to_fd
## 4、xcb_disconnect
## 5、xcb_parse_display
## 6、xcb_get_setup
## 9、xcb_get_file_descriptor
## 10、xcb_get_maximum_request_length
## 11、xcb_wait_for_event
## 13、xcb_poll_for_event
## 14、xcb_connection_has_error
## 15、xcb_flush
## 16、xcb_get_extension_data
## 17、xcb_prefetch_extension_data
## 18、xcb_generate_id
