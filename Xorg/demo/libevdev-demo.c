#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <libevdev-1.0/libevdev/libevdev.h>


static int
print_event(struct input_event *ev)
{
	if (ev->type == EV_SYN)
		printf("Event: time %ld.%06ld, ++++++++++++++++++++ %s +++++++++++++++\n",
				ev->input_event_sec,
				ev->input_event_usec,
				libevdev_event_type_get_name(ev->type));
	else
		printf("Event: time %ld.%06ld, type %d (%s), code %d (%s), value %d\n",
			ev->input_event_sec,
			ev->input_event_usec,
			ev->type,
			libevdev_event_type_get_name(ev->type),
			ev->code,
			libevdev_event_code_get_name(ev->type, ev->code),
			ev->value);
	return 0;
}

int
main(int argc, char **argv)
{
	struct libevdev *dev = NULL;
	const char *file;
	int fd;
	int rc = 1;

	if (argc < 2)
		goto out;

	file = argv[1];
	fd = open(file, O_RDONLY);
	if (fd < 0) {
		perror("Failed to open device");
		goto out;
	}

	rc = libevdev_new_from_fd(fd, &dev);
	if (rc < 0) {
		fprintf(stderr, "Failed to init libevdev (%s)\n", strerror(-rc));
		goto out;
	}


	do {
		struct input_event ev;
		rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL|LIBEVDEV_READ_FLAG_BLOCKING, &ev);
		if (rc == LIBEVDEV_READ_STATUS_SUCCESS)
			print_event(&ev);
	} while (1);

out:
	libevdev_free(dev);

	return rc;
}
