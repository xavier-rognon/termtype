/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** free_player
*/

#include "../../include/include.h"

void free_player(player_t *player)
{
    free(player->correct_input);
    free(player->wrong_input);
    free(player);
}
