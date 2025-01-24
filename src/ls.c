/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** ls
*/

#include "ls.h"

static bool get_path([[maybe_unused]]char *path, const char *asked_path)
{
    if (!asked_path) {
        return false;
    }
    if (asked_path[0] != '/') {
        strcat(path, "/");
        strcat(path, asked_path);
        return true;
    }
    strcpy(path, asked_path);
    return true;
}

static list_t *get_files(char *path)
{
    DIR *dir = opendir(path);
    struct dirent *d = NULL;
    list_t *files = NULL;

    if (!dir) {
        return NULL;
    }
    while ((d = readdir(dir))) {
        add_element(&files, (void *)(d));
    }
    return files;
}

static void basic_ls(list_t *files)
{
    list_t *tmp = files;

    while (tmp) {
        struct dirent *d = (struct dirent *)(tmp->data);
        printf("%s%c", d->d_name, tmp->next ? ' ' : '\n');
        tmp = tmp->next;
    }
}

static void delete_hidden_files(list_t **files)
{
    list_t *tmp = *files;
    size_t i = 0;

    while (tmp) {
        struct dirent *d = (struct dirent *)(tmp->data);
        if (d->d_name[0] == '.') {
            tmp = tmp->next;
            delete_element_by_index(files, i);
            continue;
        }
        tmp = tmp->next;
        i ++;
    }
}

static bool flag_asked(char c, list_t *flags)
{
    return is_in_list(flags, (void *)&c, &char_equality);
}

static bool files_sorted(list_t *files)
{
    list_t *tmp = files;

    while (tmp) {
        if (!tmp->next) {
            break;
        }
        struct dirent *d1 = (struct dirent *)(tmp->data);
        struct dirent *d2 = (struct dirent *)(tmp->next->data);
        if (strcmp(d1->d_name, d2->d_name) > 0) {
            return false;
        }
        tmp = tmp->next;
    }
    return true;
}

static void sort_files(list_t **files)
{
    list_t *tmp = NULL;

    while (!files_sorted(*files)) {
        tmp = *files;
        while (tmp) {
            if (!tmp->next) {
                break;
            }
            struct dirent *d1 = (struct dirent *)(tmp->data);
            struct dirent *d2 = (struct dirent *)(tmp->next->data);
            if (strcmp(d1->d_name, d2->d_name) > 0) {
                void *data_tmp = tmp->data;
                tmp->data = tmp->next->data;
                tmp->next->data = data_tmp;
            }
            tmp = tmp->next;
        }
    }
}

void ls(const char *asked_path, [[maybe_unused]]list_t *flags)
{
    char path[PATH_MAX];
    list_t *files = NULL;

    if (!getcwd(path, PATH_MAX) || !get_path(path, asked_path)) {
        return;
    }
    files = get_files(path);
    if (!flag_asked('a', flags)) {
        delete_hidden_files(&files);
    }
    sort_files(&files);
    if (flag_asked('r', flags)) {
        reverse_list(&files);
    }
    basic_ls(files);
}
