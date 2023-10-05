/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** variant
*/

#include "../../include/include.h"

void time_variant(ui_t *ui, player_t *player)
{
    if (ui->variant == S)
        player->playtime = 15;
    if (ui->variant == M)
        player->playtime = 30;
    if (ui->variant == L)
        player->playtime = 60;
    if (ui->variant == XL)
        player->playtime = 120;
}

void word_variant(ui_t *ui, player_t *player)
{
    if (ui->variant == S)
        player->playtime = 15;
    if (ui->variant == M)
        player->playtime = 30;
    if (ui->variant == L)
        player->playtime = 60;
    if (ui->variant == XL)
        player->playtime = 120;
}

void quote_variant(ui_t *ui, player_t *player)
{
    if (ui->variant == S)
        player->playtime = 15;
    if (ui->variant == M)
        player->playtime = 30;
    if (ui->variant == L)
        player->playtime = 60;
    if (ui->variant == XL)
        player->playtime = 120;
}

void manage_variant(ui_t *ui, player_t *player)
{
    void (*gamemode_variant[3])(ui_t *, player_t *) = {&time_variant, &word_variant,
                                                    &quote_variant};
    gamemode_variant[ui->gamemode](ui, player);
}
