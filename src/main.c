/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** main
*/

#include "../include/include.h"
#include <curses.h>

int check_alarm_g;

void sig_handler(int signum)
{
    check_alarm_g = 1;
    signum = signum;
}

int main(void)
{
    srand(time(NULL));
    check_alarm_g = 0;
    setlocale(LC_ALL, "");
    nodelay(stdscr, true);
    signal(SIGALRM, sig_handler);
    my_curses();
    return 0;
}
