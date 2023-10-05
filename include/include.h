/*
** EPITECH PROJECT, 2023
** bin
** File description:
** include
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <curses.h>
#include <dirent.h>
#include <signal.h>
#include <time.h>
#include <locale.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

#include "parser.h"
#include "my_curses.h"
#include "player.h"

extern int check_alarm_g;

#ifndef INCLUDE_H_
    #define INCLUDE_H_

void exit_with_message(char *message, int code);
int my_strlen_til_c(char *str, char c);
char **my_str_to_word_array(char *str, char *limiter);
int my_arrlen(char **array);
void my_show_word_array(char **array);
void my_show_word_array_ncurses(char **array);
void free_array(char **array);
char *my_strcat(char *str1, char *str2);
char *my_strcpy(char *dest, char *src);
char **my_realloc(char **array, int lenght);
bool my_char_isalphanum(char c);

#endif /* !INCLUDE_H_ */
