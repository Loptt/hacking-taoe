#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "hacking.h"

#define FILENAME "/var/notes"

int main()
{
    int fd = open(FILENAME, O_RDONLY);

    char byte;

    printf("Testing read()\n");

    while (read(fd, &byte, 1))
    {
        printf("%c", byte);
    }
    return 0;
}