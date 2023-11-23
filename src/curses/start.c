/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** start
*/

/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** start
*/

#include "../../include/include.h"
#include <curses.h>
#include <stdio.h>

void init_top_bar(ui_t *ui)
{
    ui->top_bar = newwin(3, ui->col / 2, ui->row / 4 - 2, ui->col / 4);
    box(ui->top_bar, 0, 0);
    curs_set(0);
    keypad(ui->top_bar, true);
}

void init_language_menu(ui_t *ui)
{
    ui->language->language_menu = newwin(ui->row, ui->col / 3, 0, (ui->col - ui->col / 3) / 2);
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
        mvwprintw(ui->language->language_menu, i + 1, 2, "%s", clean_line);
    free(clean_line);
}

void display_language(ui_t *ui)
{
    int i_2 = 0;
    gamemode_language_info_t *current_type = ui->language->info[ui->language->current_type];

    if (ui->menu == LANGUAGE_BUTTON)
        attron(A_REVERSE);
    mvprintw(ui->row / 5 * 2, (ui->col - strlen(current_type->language)) / 2, "%s", current_type->language);
    attroff(A_REVERSE);
    if (ui->menu == LANGUAGE_MENU) {
        box(ui->language->language_menu, 0, 0);
        clean_language_menu(ui);
        for (int i = current_type->start_showing + current_type->search_offset;
        i < ui->row - 4 + current_type->start_showing + current_type->search_offset &&
        current_type->language_list[i] != NULL; i++, i_2++) {
            if (i == current_type->current_language)
                wattron(ui->language->language_menu, COLOR_PAIR(3));
            if (i == current_type->language_highlight && ui->language->state == SEARCH)
                wattron(ui->language->language_menu, A_REVERSE);
            if (current_type->search != NULL && strncmp(current_type->language_list[i],
                        current_type->search, strlen(current_type->search)) == 0)
                mvwprintw(ui->language->language_menu, i_2 + 3, 2, "%s", current_type->language_list[i]);
            wattroff(ui->language->language_menu, A_REVERSE);
            wattroff(ui->language->language_menu, COLOR_PAIR(3));
        }
        mvwprintw(ui->language->language_menu, 1, 2, "> %s| ", current_type->search);
        for (int i = 1; i < ui->col / 3 - 1; i++)
            mvwprintw(ui->language->language_menu, 2, i, "—");
        if (ui->language->state == EXIT)
            wattron(ui->language->language_menu, A_REVERSE);
        mvwprintw(ui->language->language_menu, 0, ui->col / 3 - 1, "X");
        wattroff(ui->language->language_menu, A_REVERSE);
        refresh();
        wrefresh(ui->language->language_menu);
        clear_window(ui->language->language_menu);
    }
}

void start(player_t *player, ui_t *ui)
{
    char info[49] = "Use tab and the arrow key to navigates the menus";
    char info_2[26] = "Press tab to change menu.";
    char start[18] = " 󰐊 start test ";
    char exit[21] = " 󰗼 exit termtype ";

    if (player->state != START)
        return;
    print_sentence(player, ui);
    mvprintw(ui->row / 5 * 4, (ui->col - 48) / 2, "%s", info);
    mvprintw(ui->row / 5 * 4 + 1, (ui->col - 26) / 2, "%s", info_2);
    if (ui->menu == START_BUTTON)
        attron(A_REVERSE);
    mvprintw(ui->row / 3 * 2, ui->col / 2 - strlen(start), "%s", start);
    attroff(A_REVERSE);
    if (ui->menu == EXIT_BUTTON)
        attron(A_REVERSE);
    mvprintw(ui->row / 3 * 2, ui->col / 2, "%s", exit);
    attroff(A_REVERSE);
    display_top_bar(ui);
    display_language(ui);
    analyze_input(ui, player);
}

