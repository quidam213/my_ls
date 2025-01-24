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
            add_element(head, (void *)(&str[i]), &base_free_node);
        }
    }
}

static bool char_in_str(char c, char *str)
{
    if (!str) {
        return false;
    }
    for (size_t i = 0; str[i]; i ++) {
        if (str[i] == c) {
            return true;
        }
    }
    return false;
}

static bool flags_exist(list_t *flags)
{
    list_t *tmp = flags;

    while (tmp) {
        if (!char_in_str(*(char *)(tmp->data), FLAGS_LIST)) {
            return false;
        }
        tmp = tmp->next;
    }
    return true;
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
            add_element(&core->path, (void *)(av[i]), &base_free_node);
        }
    }
    if (!flags_exist(core->flags)) {
        free_core(&core);
        write(2, FLAG_DOESNT_EXIST, strlen(FLAG_DOESNT_EXIST));
        return NULL;
    }
    if (!core->path) {
        add_element(&core->path, (void *)("."), &base_free_node);
    }
    reverse_list(&core->path);
    return core;
}

void free_core(core_t **core)
{
    free_list(&(*core)->flags);
    free_list(&(*core)->path);
    if (*core) {
        free(*core);
    }
}

void execute_core(core_t **core)
{
    list_t *tmp = (*core)->path;
    bool name_cond = (get_list_len(tmp) || flag_asked('R', (*core)->flags));

    while (tmp) {
        if (name_cond) {
            printf("%s:\n", (char *)tmp->data);
        }
        ls((char *)(tmp->data), (*core)->flags);
        if (name_cond && tmp->next) {
            printf("\n");
        }
        tmp = tmp->next;
    }
}
