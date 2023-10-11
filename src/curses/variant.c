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
        ui->lenght = 25;
    if (ui->variant == M)
        ui->lenght = 50;
    if (ui->variant == L)
        ui->lenght = 100;
    if (ui->variant == XL)
        ui->lenght = 200;
    free_parser(ui->parser);
    ui->parser = parser_language(
        my_strcat("./asset/languages/", ui->language->language_list_json[ui->language->current_language]),
        ui->lenght);
    cut_sentence_for_display(ui, ui->parser->sentence);
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

