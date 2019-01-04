#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    int fd = open("/tmp/lseek_test", O_RDONLY);
    char burn;

    read(fd, &burn, 1);
    while(burn != 'y')
        read(fd, &burn, 1);
    
    printf("%c", burn);

    lseek(fd, -3, SEEK_CUR);

    read(fd, &burn, 1);
    read(fd, &burn, 1);
    read(fd, &burn, 1);

    printf("%c\n", burn);

    close(fd);
    return 0;
}