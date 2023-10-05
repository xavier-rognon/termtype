/*
** EPITECH PROJECT, 2023
** usefull_function
** File description:
** my_str_to_word_array
*/

#include "../../include/include.h"

bool my_is_in_str(char *str, char a)
{
    for (int i = 0; str[i] != 0; i++)
        if (str[i] == a && str != NULL)
            return true;
    return false;
}

int count_word(char *str, char *limiter)
{
    int nb_word = 0;

    for (int i = 0; str[i] != 0; i++) {
        if ((my_is_in_str(limiter, str[0]) == 0 && i == 0 )||
        (my_is_in_str(limiter, str[i]) == 0 &&
        my_is_in_str(limiter, str[i - 1]) == 1
        && i != 0))
            nb_word++;
    }
    return nb_word;
}

void fill_the_arr(char *str, char *arr, char *limiter, int index)
{
    int i = 0;

    for (; my_is_in_str(limiter, str[index + i]) == 0 &&
    str[i + index] != 0; i++) {
        arr[i] = str[i + index];
    }
    arr[i] = 0;
}

char **my_str_to_word_array(char *str, char *limiter)
{
    int word_lenght = 0;
    int word_count = 0;
    char **arr = malloc(sizeof(char *) * (count_word(str, limiter) + 2));
    int i = 0;

    for (; str[i] != 0; i++) {
        if (my_is_in_str(limiter, str[i]) == 0)
            word_lenght++;
        if (my_is_in_str(limiter, str[i]) == 1 &&
        my_is_in_str(limiter, str[i - 1]) == 0 && i != 0) {
            arr[word_count] = malloc(sizeof(char) * (word_lenght + 1));
            fill_the_arr(str, arr[word_count], limiter, i - word_lenght);
            word_lenght = 0;
            word_count++;
        }
    }
    arr[word_count] = malloc(sizeof(char) * (word_lenght + 1));
    fill_the_arr(str, arr[word_count], limiter, i - word_lenght);
    arr[word_count + 1] = NULL;
    return arr;
}
