/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** language
*/

#include "../../include/include.h"

char **my_arrdup(char **arr)
{
    int j;
    int i = 0;
    char **arr2 = malloc(sizeof(char *) * (my_arrlen(arr) + 2));

    for (; arr[i] != NULL; i++) {
        arr2[i] = malloc(sizeof(char) * (strlen(arr[i]) + 1));
        for (j = 0; arr[i][j] != 0; j++)
            arr2[i][j] = arr[i][j];
        arr2[i][j] = 0;
    }
    arr2[i] = NULL;
    return arr2;
}

char **clean_for_display(char **list_json)
{
    char **clean_list = my_arrdup(list_json);

    for (int i = 0; clean_list[i] != NULL; i++)
        for (int j = 0; clean_list[i][j] != 0; j++) {
            if (clean_list[i][j] == '_')
                clean_list[i][j] = ' ';
            if (clean_list[i][j] == '.') {
                clean_list[i][j] = 0;
                break;
            }
        }
    return clean_list;
}

int find_english_index(char **language_json)
{
    for (int index = 0; language_json[index] != NULL; index++) {
        if (strcmp("english.json", language_json[index]) == 0)
            return index;
    }
    return -1;
}

void free_gamemode_info(gamemode_language_info_t *gamemode_info)
{
    free_array(gamemode_info->language_list);
    free_array(gamemode_info->language_list_json);
    free(gamemode_info->search);
    free(gamemode_info->language);
    free(gamemode_info);
}

void language_free(language_t *language)
{
    free_gamemode_info(language->info[0]);
    free_gamemode_info(language->info[1]);
    free(language->info);
    free(language);
}

gamemode_language_info_t *load_language_from_dir(char *path_to_dir)
{
    gamemode_language_info_t *language = malloc(sizeof(gamemode_language_info_t));
    DIR *language_dir;
    char *file_names;
    char *temp;
    struct dirent *de;

    language_dir = opendir(path_to_dir);
    if (language_dir == NULL)
        exit_with_message("failed to open the directory\n", 1);
    for (int i = 0; i < 5; i++)
        de = readdir(language_dir);
    de = readdir(language_dir);
    file_names = strdup(de->d_name);
    while ((de = readdir(language_dir)) != NULL) {
        temp = file_names;
        file_names = my_strcat(file_names, "|");
        free(temp);
        temp = file_names;
        file_names = my_strcat(file_names, de->d_name);
        free(temp);
    }
    closedir(language_dir);
    language->language_list_json = my_str_to_word_array(file_names, "|");
    language->language_list = clean_for_display(language->language_list_json);
    language->current_language = find_english_index(language->language_list_json);
    language->language = my_strcat("󰇧 ", language->language_list[language->current_language]);
    language->search = strdup("\0");
    language->start_showing = 0;
    language->language_highlight = 0;
    language->search_offset = 0;
    free(file_names);
    return language;
}

language_t *language_init(void)
{
    language_t *language = malloc(sizeof(language_t));

    language->info = malloc(sizeof(gamemode_language_info_t *) * 2);
    language->info[0] = load_language_from_dir("./asset/quotes");
    language->info[1] = load_language_from_dir("./asset/languages");
    language->state = 0;
    language->current_type = RANDOM_WORDS;
    return language;
}

