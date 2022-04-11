#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "utils.h"

linked_list_t*
ll_create(unsigned int data_size)
{
    linked_list_t *list = calloc(1, sizeof(linked_list_t));
    DIE(!list, ALLOC_ERR);
    list->data_size = data_size;
    return list;
}

ll_node_t*
ll_make_node(ll_node_t *next, const void *data, unsigned int data_size) {
    ll_node_t *node = calloc(1, sizeof(ll_node_t));
    DIE(!node, ALLOC_ERR);

    node->next = next;
    node->data = calloc(1, data_size);
    DIE(!node->data, ALLOC_ERR);

    memcpy(node->data, data, data_size);

    return node;
}

void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
    if (list == NULL)
        return;

    ll_node_t *prev, *node;

    if (n > list->size)
        n = list->size;

    if (n == 0) {
        prev = list->head;
        node = ll_make_node(prev, new_data, list->data_size);
        list->head = node;
        list->size++;
        return;
    }

    prev = list->head;

    for (unsigned int i = 1; i < n; i++) {
        prev = prev->next;
    }

    node = ll_make_node(prev->next, new_data, list->data_size);
    prev->next = node;

    list->size++;
}

ll_node_t*
ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
    if (list->size == 0)
        return NULL;
    if (n > list->size)
        n = list->size - 1;
    ll_node_t *prev = list->head;
    ll_node_t *elim = prev->next;
    if (n == 0) {
        elim = list->head;
        list->head = elim->next;
        list->size--;
        return elim;
    }

    unsigned int i = 0;
    while (prev->next) {
        i++;
        if (i == n) {
            elim = prev->next;
            prev->next = elim->next;
            list->size--;
            return elim;
        }
        prev = prev->next;
    }

    return elim;
}

unsigned int
ll_get_size(linked_list_t* list)
{
    if (!list->head)
        return 0;
    unsigned int i = 1;
    ll_node_t *node = list->head;
    while (node->next) {
        i++;
        node = node->next;
    }
    return i;
}

void
ll_free(linked_list_t* list)
{
    ll_node_t *node = list->head;
    for (unsigned int i = 0; i < list->size; i++) {
        ll_node_t *tmp = node;
        node = node->next;
        free(tmp->data);
        free(tmp);
    }
    free(list);
}

void
ll_print(linked_list_t* list, void *print_func(void *))
{
    ll_node_t *node = list->head;
    for (unsigned int i = 0; i < list->size; i++) {
        print_func(node->data);
        node = node->next;
    }

    printf("\n");
}
