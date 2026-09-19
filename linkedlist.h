#include <stdio.h>
#include <stdlib.h>

#ifndef _LINKEDLIST_H_
    #define _LINKEDLIST_H_

    #include "datatypes.h"
    
    typedef struct node_t {
        type_t *data;
        struct node_t *prev;
        struct node_t *next;
    }  node_t;

    typedef struct {
        struct node_t *first;
        struct node_t *last;
    } linked_list_t;

    #define LINKEDLISTINIT {NULL,NULL}

    node_t *node_init(type_t *data);
    void list_init(linked_list_t *list);
    int  list_size(node_t *head);
    void list_add_first(linked_list_t *list,type_t *data);
    void list_add_last(linked_list_t *list,type_t *data);
    void list_add_middle(linked_list_t *list,type_t *data, int position);
    void list_delete_first(linked_list_t *list);
    void list_delete_last(linked_list_t *list);
    void list_delete_middle(linked_list_t *list, int position);
    void list_modify(node_t *modify, type_t *data);
    int  list_found(linked_list_t list,type_t *data);
    int  list_find_position(linked_list_t list,type_t *data);
    void list_display(linked_list_t list, void (*print_data)(type_t *data));
    void list_clean(linked_list_t *list);
    int  list_is_empty(linked_list_t list);
    type_t *list_get(linked_list_t list, int position);
    void list_free_all(linked_list_t *list);
#endif
