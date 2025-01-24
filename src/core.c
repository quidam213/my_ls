/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** core
*/

#include "ls.h"

static void parse_flag(const char *str, list_t **head)
{
    for (size_t i = 0; str[i]; i ++) {
        if (!is_in_list(*head, (void *)(&str[i]), &char_equality)) {
            add_element(head, (void *)(&str[i]));
        }
    }
}

core_t *init_core(char **av)
{
    core_t *core = malloc(sizeof(core_t));

    core->flags = NULL;
    core->path = NULL;
    for (size_t i = 1; av[i]; i ++) {
        if (av[i][0] == '-') {
            parse_flag(&av[i][1], &core->flags);
        } else {
            //! path
        }
    }
    return core;
}

void free_core(core_t **core)
{
    free_list(&(*core)->flags);
    if (*core) {
        free(*core);
    }
}
