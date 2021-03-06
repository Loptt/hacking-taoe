#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "hacking.h"

#define FILENAME "/var/notes"

int print_notes(int, int, char *);
int find_user_note(int, int);
int search_note(char *, char *);
void fatal(char *);

int main(int argc, char const *argv[])
{
    int userid, printing = 1, fd;
    char searchstring[100];

    if (argc > 1)
        strcpy(searchstring, argv[1]);
    else
        searchstring[0] = 0;

    userid = getuid();
    fd = open(FILENAME, O_RDONLY);
    if (fd == -1)
        fatal("in main() while opening file for reading");
    
    while (printing)
        printing = print_notes(fd, userid, searchstring);

    printf("------[ end of note data ]--------\n");
    close(fd);

    return 0;
}

int print_notes(int fd, int uid, char *searchstring)
{
    int note_length;
    char byte = 0, note_buffer[100];

    note_length = find_user_note(fd, uid);
    if (note_length == -1)
    {
        printf("[DEBUG] note length = -1\n");
        return 0;
    }
    
    if (read(fd, note_buffer, note_length) != note_length)
        printf("[DEBUG] Error while reading to note buffer\n"); //fatal("in print_notes, nothing read from buffer");

    note_buffer[note_length] = 0;
    
    printf("[DEBUG] note length: %d, note: %s\n", note_length, note_buffer);

    if (search_note(note_buffer, searchstring))
    {
        printf(note_buffer);
    }

    return 1;
}

int find_user_note(int fd, int user_uid)
{
    int note_uid = -1;
    unsigned char byte;
    int length;

    while (note_uid != user_uid)
    {
        if (read(fd, &note_uid, 4) != 4)
        {
            printf("[DEBUG] Error: cannot read note uid\n");
            return -1;
        }
        if (read(fd, &byte, 1) != 1)
        {
            printf("[DEBUG] Error: cannot read line break\n");
            return -1;
        }

        printf("[DEBUG] note uid: %d\n", note_uid);
        printf("[DEBUG] first byte: %c\n[DEBUG] note: ", byte);
        
        byte = length = 0;
        
        while (byte != '\n')
        {
            if (read(fd, &byte, 1) != 1)
                return -1;
            length++;
            printf("%c", byte);
        }
    }

    char sec_byte = 'A';
    lseek(fd, 4, SEEK_CUR); //NOT WORKING (OR IS IT?)
    read(fd, &sec_byte, 1);
    printf("[DEBUG] Rewinded byte: %c\n", sec_byte);

    printf("\n[DEBUG] found a %d byte note for user id %d\n", length, note_uid);
    return length;
}

int search_note(char *note, char *keyword)
{
    return 1;
    int i, keyword_length, match = 0;

    keyword_length = strlen(keyword);
    if (keyword_length == 0)
        return 1;
    
    for (i = 0; i < strlen(note); i++)
    {
        if (note[i] == keyword[match])
            match++;
        else
        {
            if (note[i] == keyword[0])
                match = 1;
            else
                match = 0;
        }
        
        if (match == keyword_length)
            return 1;
    }

    return 0;
}