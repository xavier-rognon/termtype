/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** parser_quote
*/

#include "../../include/include.h"

int *find_length_delta(const nx_json *json, int length)
{
    const nx_json *array = nx_json_get(json, "groups");
    const nx_json *delta_json = nx_json_item(array, length);
    int *delta_int = malloc(sizeof(int) * 2);

    for (int i = 0; i < 2; i++) {
        delta_int[i] = nx_json_item(delta_json, i)->num.s_value;
    }
    return delta_int;
}

void clean_quote(parser_t *parser)
{
    char *clean = malloc(sizeof(char *) * (strlen(parser->sentence)));
    int diff = 0;
    int i;

    for (i = 0; parser->sentence[i] != 0; i++)
        if (parser->sentence[i] == '\\') {
            i++;
            diff++;
            if (parser->sentence[i] == 't')
                clean[i - diff] = '\t';
            if (parser->sentence[i] == 'n')
                clean[i - diff] = '\n';
        } else {
            clean[i - diff] = parser->sentence[i];
        }
    clean[i] = 0;
    free(parser->sentence);
    parser->sentence = clean;
}

void find_quote(const nx_json *json, parser_t *parser, int *length_delta)
{
    const nx_json *quote_array = nx_json_get(json, "quotes");
    const nx_json *quote;
    int length = quote_array->children.length;
    int quote_length;
    int random_value;

    while (1) {
        random_value = rand() % length;
        quote = nx_json_item(quote_array, random_value);
        quote_length = nx_json_get(quote, "length")->num.s_value;
        if (quote_length >= length_delta[0] && quote_length <= length_delta[1]){
            parser->sentence = strdup(nx_json_get(quote, "text")->text_value);
            parser->name = strdup(nx_json_get(quote, "source")->text_value);
            parser->nb_word = count_word(parser->sentence, " ");
            return;
        }
    }
}

parser_t *parser_quote(char *path, int length)
{
    parser_t *parser = malloc(sizeof(parser_t));
    int fd = open(path, O_RDONLY);
    char *content;
    int *length_delta;
    const nx_json *json;
    struct stat s;

    if (fd == -1)
        exit_with_message("file not found", 84);
    stat(path, &s);

    content = malloc(sizeof(char) * (s.st_size + 1));
    read(fd, content, s.st_size);
    content[s.st_size] = 0;
    json = nx_json_parse(content, 0);
    length_delta = find_length_delta(json, length);
    find_quote(json, parser, length_delta);
    clean_quote(parser);
    nx_json_free(json);
    free(length_delta);
    close(fd);
    return parser;
}

