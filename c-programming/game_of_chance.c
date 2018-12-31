#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include "hacking.h"

#define DATAFILE "/var/chance.data"

struct user
{
    int uid;
    int credits;
    int highscore;
    char name[100];
    int (*current_game) ();
};

int get_player_data();
void register_new_player();
void update_player_data();
void show_highscore();
void jackpot();
void input_name();
void print_cards(char *, char *, int);
int take_wager(int, int);
void play_the_game();
int pick_a_number();
int dealer_no_match();
int find_the_ace();
void fatal(char *);

struct user player;

int main(int argc, char const *argv[])
{
    int choice, last_game;

    srand(time(0));

    if (get_player_data() == -1)
        register_new_player();
    
    while (choice != 7)
    {
        printf("-=[ Game of Chance Menu ]=-\n");
        printf("1 - Play the Pick a Number game\n");
        printf("2 - Play the No Match Dealer game\n");
        printf("3 - Play the Find the Ace game\n");
        printf("4 - View current highscore\n");
        printf("5 - Change your username\n");
        printf("6 - Reset your account at 100 credits\n");
        printf("7 - Quit\n");
        printf("[Name: %s]\n", player.name);
        printf("[You have %u credits] ->  ", player.credits);
        scanf("%d", &choice);

        if ((choice < 1) || (choice > 7))
            printf("\n[!!] The number %d is an invalid selection. \n\n", choice);
        else if (choice > 4)
        {
            if (choice != last_game)
            {
                if (choice == 1)
                    player.current_game = pick_a_number;
                else if (choice == 2)
                    player.current_game = dealer_no_match;
                else
                    player.current_game = find_the_ace;

                last_game = choice;
            }

            play_the_game();
        }
        else if (choice == 4)
            show_highscore();
        else if (choice == 5)
        {
            printf("\nChange user name\n");
            printf("Enter your new name: ");
            input_name();
            printf("Your name has been changed. \n\n");
        }
        else if (choice == 6)
        {
            printf("\nYour account has been reset with 100 credits.\n\n");
            player.credits = 100;
        }
    }
    update_player_data();
    printf("\nThanks for playing! Bye.\n");

    return 0;
}

int get_player_data()
{
    int fd, uid, read_bytes;
    struct user entry;

    uid = getuid();

    fd = open(DATAFILE, O_RDONLY);
    if (fd == -1)
        return -1;

    read_bytes = read(fd, &entry, sizeof(struct user));

    while (entry.uid != uid && read_bytes > 0)
    {
        read_bytes = read(fd, &entry, sizeof(struct user));
    }

    close(fd);

    if (read_bytes < sizeof(struct user))
        return -1;
    else
        player = entry;
    
    return 1;
}

void register_new_player()
{
    int fd;

    printf("-=-={ New Player REgistration }=-=-\n");
    printf("Enter your name: ");
    input_name();

    player.uid = getuid();
    player.highscore = player.credits = 100;

    fd = open(DATAFILE, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    if (fd == -1)
        fatal("in register_new_player() while opening file");
    
    write(fd, &player, sizeof(struct user));
    close(fd);

    printf("\nWelcome to the Game of Chance, %s. \n", player.name);
    printf("You have been given %u credits.\n", player.credits);
}

void update_player_data()
{
    int fd, i, read_uid;
    char burned_byte;

    fd = open(DATAFILE, O_RDWR);
    if (fd == -1)
        fatal("in update_player_data() while opening file");
    
    read(fd, &read_uid, 4);
    while(read_uid != player.uid)
    {
        for (i = 0; i < sizeof(struct user) - 4; i++)
            read(fd, &burned_byte, 1);
        read(fd, &read_uid, 4);
    }

    write(fd, &(player.credits), 4);
    write(fd, &(player.highscore), 4);
    write(fd, &(player.name), 100);
    close(fd);
}

void show_highscore()
{
    unsigned int top_score = 0;
    char top_name[100];
    struct user entry;
    int fd;

    printf("\n==================| HIGH SCORE |==================\n");

    fd = open(DATAFILE, O_RDONLY);
    if (fd == -1)
        fatal("in show_highscore() while opening file");

    
}