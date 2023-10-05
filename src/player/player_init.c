/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** player_init
*/

#include "../../include/include.h"

void player_reset_test(player_t *player, parser_t *parser)
{
    free(player->wrong_input);
    free(player->correct_input);
    player->lenght_input = 0;
    player->start_showing_player_input = 0;
    player->current_line = 1;
    player->current_row[0] = 0;
    player->current_row[1] = 1;
    player->current_row[2] = 2;
    player->offset = 0;
    player->wrong_input = malloc(sizeof(char) * strlen(parser->sentence));
    player->correct_input = malloc(sizeof(char) * strlen(parser->sentence));
    player->wrong_input = memset(player->wrong_input, 0, strlen(parser->sentence) - 1);
    player->correct_input = memset(player->correct_input, 0, strlen(parser->sentence) - 1);
}

player_t *player_init(parser_t *parser)
{
    player_t *player = malloc(sizeof(player_t));

    player->lenght_input = 0;
    player->offset = 0;
    player->start_showing_player_input = 0;
    player->current_line = 1;
    player->last_input = 0;
    player->state = START;
    player->playtime = 30;
    player->current_row[0] = 0;
    player->current_row[1] = 1;
    player->current_row[2] = 2;
    player->wrong_input = malloc(sizeof(char) * strlen(parser->sentence));
    player->correct_input = malloc(sizeof(char) * strlen(parser->sentence));
    player->wrong_input = memset(player->wrong_input, 0, strlen(parser->sentence) - 1);
    player->correct_input = memset(player->correct_input, 0, strlen(parser->sentence) - 1);
    return player;
}
