/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** my_find_digits
*/

int my_find_digits(int nb)
{
    int digits = 0;

    while (nb > 0) {
        digits++;
        nb /= 10;
    }
    return digits;
}
