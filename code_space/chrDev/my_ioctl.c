#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int my_dev_fd = open("/dev/mydev", 0);

    if(my_dev_fd < 0)
    {
        perror("Fail to open /dev/mydev");
    }
    else
    {
        ioctl(my_dev_fd, 0x12345677, 110); // 调用ioctl
        close(my_dev_fd);
    }

    return 0;
}