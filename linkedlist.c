#include "linkedlist.h"

static node_t *node_at(node_t *head, int position)
{
    int current = 0;
    while (head != NULL && current != position) {
        head = head->next;
        current++;
    }
    return head;  // NULL if position is out of range
}

static int position_valid(int position, int size)
{
    if (position < 0 || position > size) {
        return 0;
    }
    return 1;
}

static void list_destroy(linked_list_t *list, int free_data)
{
    node_t *ptr = list->first;
    node_t *before;

    while (ptr != NULL) {
        before = ptr;
        ptr = ptr->next;
        if (free_data) free(before->data);
        free(before);
    }
    list->first = NULL;
    list->last = NULL;
}

node_t *node_init(type_t *data)
{
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        return NULL;
    }
    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    return new;
}

void list_init(linked_list_t *list)
{
    if (list != NULL) {
        list->first = NULL;
        list->last = NULL;
        list->size = 0;
    }
}

int list_size(node_t *head)
{
    int size = 0;
    while (head != NULL)
    {
        size++;
        head = head->next;
    }
    return size;
}

int list_length(linked_list_t list)
{
    return list.size;
}

int list_add_first(linked_list_t *list, type_t *data)
{
    node_t *newNode = node_init(data);

    if(list->first == NULL){
        list->first = newNode;
        list->last = newNode;
    } else {
        newNode->next = list->first;
        newNode->prev = NULL;
        list->first->prev = newNode;
        list->first = newNode;
    }
    list->size++;
    return 1;
}

int list_add_last(linked_list_t *list, type_t *data)
{
    node_t *newNode = node_init(data);

    if(list->first == NULL){
        list->first = newNode;
        list->last = newNode;
    } else {
        list->last->next = newNode;
        newNode->prev = list->last;
        list->last = newNode;
    }
    list->size++;
    return 1;
}

int list_add_middle(linked_list_t *list, type_t *data, int position)
{
    int size = list->size;

    if (!position_valid(position, size)) {
        return 0;
    }

    if(position == 0){
        return list_add_first(list, data);
    } if (position == size){
        return list_add_last(list, data);
    }

    node_t *newNode = node_init(data);

    if(newNode != NULL){
        node_t *prevNode = node_at(list->first, position - 1);
        newNode->next = prevNode->next;
        newNode->prev = prevNode;
        if (prevNode->next != NULL){
            prevNode->next->prev = newNode;
        }
        prevNode->next = newNode;
    }
    list->size++;
    return 1;
}

int list_delete_first(linked_list_t *list)
{
    if(list->first == NULL){
        return 0;
    } else {
        node_t *temp = list->first;
        list->first = list->first->next;
        if (list->first != NULL) {
            list->first->prev = NULL;
        } else {
            list->last = NULL;
        }
        free(temp);
        list->size--;
    }
    return 1;
}

int list_delete_last(linked_list_t *list)
{
    node_t *temp = NULL;

    if(list->first == NULL){
        return 0;
    } else if (list->first == list->last){
        temp = list->first;
        list->first = NULL;
        list->last = NULL;
    } else {
        temp = list->last;
        list->last = list->last->prev;
        list->last->next = NULL;
    }
    free(temp);
    list->size--;
    return 1;
}
int  list_delete_middle(linked_list_t *list, int position)
{
    int size = list->size;

    if (!position_valid(position, size)) {
        return 0;
    }

    if(position == 0){
        return list_delete_first(list);
    } else if (position == size){
        return list_delete_last(list);
    } else if ((position < size) && (position > 0)) {
        node_t *prevNode = node_at(list->first, position - 1);
        node_t *target = prevNode->next;
        prevNode->next = target->next;
        if (target->next != NULL) {
            target->next->prev = prevNode;
        } else {
            list->last = prevNode;
        }
        free(target);
        list->size--;
    }
    return 1;
}

int  list_modify(node_t *modify, type_t *newData)
{
    type_t *tmp = modify->data;
    modify->data = newData;
    free(tmp);
    return 1;
}

int list_found(linked_list_t list, type_t *data,
                int (*compare)(type_t *a, type_t *b))
{
    return list_find_position(list, data, compare) != -1;
}

int list_find_position(linked_list_t list, type_t *data,
                        int (*compare)(type_t *a, type_t *b))
{
    if (compare == NULL) {
        return -1;
    }

    node_t *head = list.first;
    int position = 0;

    while (head != NULL) {
        if (compare(head->data, data) == 0) {
            return position;
        }
        position++;
        head = head->next;
    }
    return -1;
}

void list_display(linked_list_t list, void (*print_data)(type_t *data))
{
    node_t *ptr = list.first;

    while (ptr != NULL) 
    {
        print_data(ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

void list_clean(linked_list_t *list)
{
    list_destroy(list, 0);
}

void list_free_all(linked_list_t *list)
{
    list_destroy(list, 1);
}

int  list_is_empty(linked_list_t list)
{
    return list.first == NULL;
}

type_t *list_get(linked_list_t list, int position)
{
    if (!position_valid(position, list.size)) {
        return NULL;
    }
    node_t *node = node_at(list.first, position);
    return (node != NULL) ? node->data : NULL;
}

int list_sort(linked_list_t *list, int (*compare)(type_t *a, type_t *b))
{
    if (compare == NULL) {
        return 0;
    }

    if (list->size < 2) {
        return 1; // Already sorted
    }

    int swapped;
    do {
        swapped = 0;
        node_t *current = list->first;

        while (current != NULL && current->next != NULL) {
            if (compare(current->data, current->next->data) > 0) {
                // Swap data
                type_t *temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);

    return 1; // Successfully sorted
}