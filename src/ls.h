/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** ls
*/

#ifndef LS_H_
#define LS_H_

//? INCLUDES
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

//? DEFINES
#define FLAGS_LIST "larRt"
#define FLAG_DOESNT_EXIST "Unknown flag entered.\n"
#define TIME_SIZE 13
#define PERMS_SIZE 11

//? STRUCTURES
typedef struct list_s {
    void *data;
    struct list_s *next;
    void (* freer) (struct list_s *);
} list_t;

typedef struct core_s {
    struct list_s *path;
    struct list_s *flags;
} core_t;

typedef struct file_s {
    struct dirent d;
    struct stat st;
    char path[PATH_MAX];
} file_t;

//? FILES
//* main.c
int main(int ac, char **av);

//* list.c
void add_element(list_t **head, void *data, void (* node_freer) (struct list_s *));
bool delete_element_by_index(list_t **head, size_t i);
size_t get_list_len(list_t *head);
void free_list(list_t **head);
void char_displayer(void *data);
void str_displayer(void *data);
void display_list(list_t *head, void (*displayer) (void *));
bool char_equality(void *a_ptr, void *b_ptr);
bool is_in_list(list_t *head, void *data, bool (* equality) (void *, void *));
void reverse_list(list_t **head);
void sort_list(list_t **head, bool (* sort_checker) (list_t *), void (* operation) (list_t **));
void base_free_node(list_t *node);

//* core.c
core_t *init_core(char **av);
void free_core(core_t **core);
void execute_core(core_t **core);

//* ls.c
bool flag_asked(char c, list_t *flags);
void ls(const char *asked_path, list_t *flags);

#endif /* !LS_H_ */
