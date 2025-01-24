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

static void get_filepath(char *filepath, char *path, char *filename)
{
    strcpy(filepath, path);
    if (path[strlen(path) - 1] != '/') {
        strcat(filepath, "/");
    }
    strcat(filepath, filename);
}

static void free_file(list_t *node)
{
    file_t *f = (file_t *)node->data;

    free(f);
}

static void add_file(list_t **files, char *path, struct dirent d)
{
    file_t *f = malloc(sizeof(file_t));

    get_filepath(f->path, path, d.d_name);
    if (stat(f->path, &f->st) < 0) {
        free(f);
        return;
    }
    f->d = d;
    add_element(files, (void *)f, &free_file);
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
        add_file(&files, path, *d);
    }
    closedir(dir);
    return files;
}

static void basic_ls(list_t *files)
{
    list_t *tmp = files;

    while (tmp) {
        file_t *f = (file_t *)(tmp->data);
        printf("%s%c", f->d.d_name, tmp->next ? ' ' : '\n');
        tmp = tmp->next;
    }
}

static void delete_hidden_files(list_t **files)
{
    list_t *tmp = *files;
    size_t i = 0;

    while (tmp) {
        file_t *f = (file_t *)tmp->data;
        if (f->d.d_name[0] == '.') {
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

static bool alpha_sort_checker(list_t *node)
{
    file_t *f1 = (file_t *)(node->data);
    file_t *f2 = (file_t *)(node->next->data);

    if (strcmp(f1->d.d_name, f2->d.d_name) > 0) {
        return false;
    }
    return true;
}

static void alpha_sort_operation(list_t **node)
{
    file_t *f1 = (file_t *)((*node)->data);
    file_t *f2 = (file_t *)((*node)->next->data);

    if (strcmp(f1->d.d_name, f2->d.d_name) > 0) {
        void *data_tmp = (*node)->data;
        (*node)->data = (*node)->next->data;
        (*node)->next->data = data_tmp;
    }
}

static bool time_sort_checker(list_t *node)
{
    file_t *f1 = (file_t *)(node->data);
    file_t *f2 = (file_t *)(node->next->data);

    if (f1->st.st_atime < f2->st.st_atime) {
        return false;
    }
    return true;
}

static void time_sort_operation(list_t **node)
{
    file_t *f1 = (file_t *)((*node)->data);
    file_t *f2 = (file_t *)((*node)->next->data);

    if (f1->st.st_atime < f2->st.st_atime) {
        void *data_tmp = (*node)->data;
        (*node)->data = (*node)->next->data;
        (*node)->next->data = data_tmp;
    }
}

static void list_file(file_t *file)
{
    printf((S_ISDIR(file->st.st_mode)) ? "d" : "-");
    printf((file->st.st_mode & S_IRUSR) ? "r" : "-");
    printf((file->st.st_mode & S_IWUSR) ? "w" : "-");
    printf((file->st.st_mode & S_IXUSR) ? "x" : "-");
    printf((file->st.st_mode & S_IRGRP) ? "r" : "-");
    printf((file->st.st_mode & S_IWGRP) ? "w" : "-");
    printf((file->st.st_mode & S_IXGRP) ? "x" : "-");
    printf((file->st.st_mode & S_IROTH) ? "r" : "-");
    printf((file->st.st_mode & S_IWOTH) ? "w" : "-");
    printf((file->st.st_mode & S_IXOTH) ? "x" : "-");
}

static void list_ls(list_t *files)
{
    list_t *tmp = files;

    while (tmp) {
        list_file((file_t *)tmp->data);
        printf("\n");
        tmp = tmp->next;
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
    if (flag_asked('t', flags)) {
        sort_list(&files, &time_sort_checker, &time_sort_operation);
    } else {
        sort_list(&files, &alpha_sort_checker, &alpha_sort_operation);
    }
    if (flag_asked('r', flags)) {
        reverse_list(&files);
    }
    if (flag_asked('l', flags)) {
        list_ls(files);
    } else {
        basic_ls(files);
    }
    free_list(&files);
}
