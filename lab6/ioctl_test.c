#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define CDEV_NAME "ioctl_cdev"

int main(void) {
    int fd;
    char path[256];
    sprintf(path, "/dev/%s", CDEV_NAME); 
    fd = open(path, O_RDWR);
    printf("Device %s opened with descriptor %d\n", path, fd);

    if (0 < fd)
        printf("ioctl return = %d\n", ioctl(fd, 0, NULL));

    return 0;
}
