/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** list
*/

#include "ls.h"

void add_element(list_t **head, void *data)
{
    list_t *new = malloc(sizeof(list_t));

    new->data = data;
    new->next = *head ? *head : NULL;
    *head = new;
}

bool delete_element_by_index(list_t **head, size_t i)
{
    list_t *tmp = *head, *prev = NULL;
    size_t j = 0;

    if (!*head) {
        return false;
    }
    if (i == 0) {
        *head = (*head)->next;
        free(tmp);
        return true;
    }
    while (tmp) {
        if (j == i) {
            prev->next = tmp->next ? tmp->next : NULL;
            free(tmp);
            return true;
        }
        prev = tmp;
        tmp = tmp->next;
        j ++;
    }
    return false;
}

size_t get_list_len(list_t *head)
{
    size_t i = 0;
    list_t *tmp = head;

    while (tmp) {
        tmp = tmp->next;
        i ++;
    }
    return i;
}

void free_list(list_t **head)
{
    while (*head) {
        delete_element_by_index(head, 0);
    }
}

void char_displayer(void *data)
{
    char c = (*(char *)(data));
    write(1, &c, 1);
}

void str_displayer(void *data)
{
    char *str = (char *)(data);
    write(1, str, strlen(str));
}

void display_list(list_t *head, void (*displayer) (void *))
{
    list_t *tmp = head;

    while (tmp) {
        displayer(tmp->data);
        write(1, "\n", 1);
        tmp = tmp->next;
    }
}

bool char_equality(void *a_ptr, void *b_ptr)
{
    char a = (*(char *)a_ptr);
    char b = (*(char *)b_ptr);

    return a == b;
}

bool is_in_list(list_t *head, void *data, bool (* equality) (void *, void *))
{
    list_t *tmp = head;

    while (tmp) {
        if (equality(tmp->data, data)) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

void reverse_list(list_t **head)
{
    list_t *prev = NULL, *tmp = *head, *next = NULL;

    if (!(*head)) {
        return;
    }
    while (tmp) {
        next = tmp->next;
        tmp->next = prev;
        prev = tmp;
        tmp = next;
    }
    *head = prev;
}
