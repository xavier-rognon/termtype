/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** start
*/

#include "../../include/include.h"
#include <stdio.h>

void init_top_bar(ui_t *ui)
{
    ui->top_bar = newwin(3, ui->col / 2, ui->row - (3 * ui->row / 4) - 2, ui->col / 4);
    box(ui->top_bar, 0, 0);
    curs_set(0);
    keypad(ui->top_bar, true);
}

void init_language_menu(ui_t *ui)
{
    ui->language->language_menu = newwin(ui->row, 50, 0, (ui->col - 50) / 2);
    ui->language->search = strdup("\0");
    waddch(ui->language->language_menu, '|');
    box(ui->language->language_menu, 0, 0);
    keypad(ui->language->language_menu, true);
}

void update_playtime(ui_t *ui, player_t *player)
{
    if (ui->gamemode != TIME) {
        player->playtime = 0;
        return;
    }
    if (ui->variant == S)
        player->playtime = 15;
    if (ui->variant == M)
        player->playtime = 30;
    if (ui->variant == L)
        player->playtime = 60;
    if (ui->variant == XL)
        player->playtime = 120;
}

void display_top_bar(ui_t *ui)
{
    int lenght = 1;

    box(ui->top_bar, 0, 0);
    for (int i = 0; ui->top_bar_button[i] != NULL; i++) {
        if (i == ui->top_bar_highlight && i != 3 && ui->menu == TOP_BAR)
            wattron(ui->top_bar, A_REVERSE);
        if (i == ui->gamemode)
            wattron(ui->top_bar, COLOR_PAIR(3));
        mvwprintw(ui->top_bar, 1, lenght, "%s", ui->top_bar_button[i]);
        wattroff(ui->top_bar, A_REVERSE);
        wattroff(ui->top_bar, COLOR_PAIR(3));
        lenght += strlen(ui->top_bar_button[i]);
    }
    lenght++;
    for (int i = 0; i < 4; i++) {
        if (i == ui->top_bar_highlight - 3 && ui->menu == TOP_BAR)
            wattron(ui->top_bar, A_REVERSE);
        if (i == ui->variant)
            wattron(ui->top_bar, COLOR_PAIR(3));
        mvwprintw(ui->top_bar, 1, lenght, "%s", ui->top_bar_option[ui->gamemode][i]);
        wattroff(ui->top_bar, A_REVERSE);
        wattroff(ui->top_bar, COLOR_PAIR(3));
        lenght += strlen(ui->top_bar_option[ui->gamemode][i]);
    }
    refresh();
    wrefresh(ui->top_bar);
}

void clean_language_menu(ui_t *ui)
{
    char *clean_line = malloc(sizeof(char) * 47);

    clean_line = memset(clean_line, ' ', 46);
    clean_line[46] = 0;
    for (int i = 0; i < ui->row - 4; i++)
        mvwprintw(ui->language->language_menu, i + 3, 2, "%s", clean_line);
    free(clean_line);
}

void display_language(ui_t *ui)
{
    int i_2 = 0;

    if (ui->menu == LANGUAGE_BUTTON)
        attron(A_REVERSE);
    mvprintw(ui->row / 2 - 4, (ui->col - strlen(ui->language->language)) / 2, "%s", ui->language->language);
    attroff(A_REVERSE);
    if (ui->menu == LANGUAGE_MENU) {
        box(ui->language->language_menu, 0, 0);
        clean_language_menu(ui);
        for (int i = ui->language->start_showing + ui->language->search_offset;
        i < ui->row - 4 + ui->language->start_showing + ui->language->search_offset &&
        ui->language->language_list[i] != NULL; i++, i_2++) {
            if (i == ui->language->current_language)
                wattron(ui->language->language_menu, COLOR_PAIR(3));
            if (i == ui->language->language_highlight)
                wattron(ui->language->language_menu, A_REVERSE);
            if (strncmp(ui->language->language_list[i],
                        ui->language->search, strlen(ui->language->search)) == 0)
                mvwprintw(ui->language->language_menu, i_2 + 3, 2, "%s", ui->language->language_list[i]);
            wattroff(ui->language->language_menu, A_REVERSE);
            wattroff(ui->language->language_menu, COLOR_PAIR(3));
        }
        mvwprintw(ui->language->language_menu, 1, 2, "> %s| ", ui->language->search);
        refresh();
        wrefresh(ui->language->language_menu);
    }
}

void start(player_t *player, ui_t *ui)
{
    char info[85] = "to exit press esc then q, you can navigate inside of the menus with the arrow keys.";
    char info_2[26] = "press tab to change menu.";
    char start[18] = " 󰐊 start test \0";

    if (player->state != START)
        return;
    print_sentence(player, ui);
    mvprintw(ui->row / 5 * 4, (ui->col - 83) / 2, "%s", info);
    mvprintw(ui->row / 5 * 4 + 1, (ui->col - 26) / 2, "%s", info_2);
    if (ui->menu == START_BUTTON)
        attron(A_REVERSE);
    mvprintw(ui->row / 5 * 3, (ui->col - strlen(start)) / 2, "%s", start);
    attroff(A_REVERSE);
    display_top_bar(ui);
    display_language(ui);
    analyze_input(ui, player);
}

