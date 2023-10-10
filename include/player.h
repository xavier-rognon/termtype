/*
** EPITECH PROJECT, 2023
** PLAYER_H_
** File description:
** player
*/

#include "parser.h"
#include "curses.h"

#ifndef PLAYER_H_
    #define PLAYER_H_

    typedef struct player_s {
        char *correct_input;
        char *wrong_input;
        char last_input;
        int cursor_pos[2];
        int current_row[3];
        int end_of_line;
        int lenght_input;
        int start_showing_player_input;
        int current_line;
        int state;
        int playtime;
        int offset;
        int offset_current_line;
    }player_t;

player_t *player_init(parser_t *parser);
void free_player(player_t *player);
void player_reset_test(player_t *player, parser_t *parser);

#endif /* PLAYER_H_ */
