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
    execute_core(&core);
    free_core(&core);
    return 0;
}
