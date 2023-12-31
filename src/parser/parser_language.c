/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** parser_language
*/

#include "../../include/include.h"

char *get_name(char *content)
{
    char *name = strstr(content, "name");
    name += 8;
    name = strndup(name, my_strlen_til_c(name, '\"'));
    return name;
}

int longest_word_in_array(char **array)
{
    long unsigned int longest = 0;

    for (int i = 0; array[i]; i++)
        if (strlen(array[i]) > longest)
            longest = strlen(array[i]);
    return longest;
}

char *get_sentence(char *content, int nb_word)
{
    char *words = strstr(content, "[");
    char **word_array = my_str_to_word_array(words, " ,[]]}\n\"\t");
    int length = my_arrlen(word_array) - 1;
    int random = rand() % length;
    char *sentence = strdup(word_array[random]);
    char *temp;
    char *temp_word = malloc(sizeof(char) * (longest_word_in_array(word_array) + 1));

    for (int i = 0; i < nb_word; i++) {
        temp = sentence;
        sentence = my_strcat(sentence, " ");
        free(temp);
        random = rand() % length;
        temp = sentence;
        temp_word = my_strcpy(temp_word, word_array[random]);
        sentence = my_strcat(sentence, temp_word);
        memset(temp_word, 0, strlen(temp_word));
        free(temp);
    }
    free(temp_word);
    free_array(word_array);
    return sentence;
}

parser_t *parser_language(char *path, int nb_word)
{
    parser_t *parser = malloc(sizeof(parser_t));
    int fd = open(path, O_RDONLY);
    struct stat s;

    if (fd == -1)
        exit_with_message("file not found", 84);
    stat(path, &s);

    char content[s.st_size + 1];
    parser->nb_word = nb_word;
    read(fd, content, s.st_size);
    content[s.st_size] = 0;
    parser->name = get_name(content);
    parser->sentence = get_sentence(content, nb_word);
    close(fd);
    return parser;
}

