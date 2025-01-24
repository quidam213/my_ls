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

//? DEFINES


//? STRUCTURES
typedef struct flag_s {
    char value;
    int (*function) ();
} flag_t;

typedef struct list_s {
    void *data;
    struct list_s *next;
} list_t;

typedef struct core_s {
    char *path;
    struct list_s *flags;
} core_t;

//? FILES
//* main.c
int main(int ac, char **av);

//* list.c
void add_element(list_t **head, void *data);
bool delete_element_by_index(list_t **head, size_t i);
size_t get_list_len(list_t *head);
void free_list(list_t **head);
void char_displayer(void *data);
void display_list(list_t *head, void (*displayer) (void *));
bool char_equality(void *a_ptr, void *b_ptr);
bool is_in_list(list_t *head, void *data, bool (* equality) (void *, void *));

//* core.c
core_t *init_core(char **av);
void free_core(core_t **core);

#endif /* !LS_H_ */
