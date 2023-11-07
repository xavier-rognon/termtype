/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** display_ascii_from_art
*/

#include "../../../include/include.h"
#include <curses.h>

void display_ascii_from_file(WINDOW *window, char *file, int x, int y)
{
    int fd = open(file, O_RDONLY);
    char **to_print;
    char *buffer;
    struct stat s;

    if (fd == -1)
        exit_with_message("file not found", 84);
    stat(file, &s);
    buffer = malloc(sizeof(char) * (s.st_size + 1));
    read(fd, buffer, s.st_size);
    buffer[s.st_size] = 0;
    to_print = my_str_to_word_array(buffer, "\n");
    for (int i = 0; to_print[i] != NULL; i++) {
        mvwprintw(window, y + i, x, "%s", to_print[i]);
    }
    free(buffer);
    free_array(to_print);
    close(fd);
}
