/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** main
*/

#include "ls.h"

int main([[maybe_unused]] int ac, char **av)
{
    core_t *core = init_core(av);

    if (!core) {
        return 84;
    }
    display_list(core->flags, &char_displayer);
    return 0;
}
