#include <stdio.h>
#include <fcntl.h>
int main()
{
    int fd;
    char buffer[80];
    static char message[] = "Hello";
    fd = open("myfile.txt", O_RDWR);
    if (fd != -1)
    {
        printf("myfile.txt opened with read/write access\n");
        write(fd, message, sizeof(message));
        lseek(fd, 0, 0);
        read(fd, buffer, sizeof(message));
        printf("%s — was written to myfile.txt \n", buffer);
        close(fd);
    }
}