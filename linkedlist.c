#include "linkedlist.h"

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

void list_add_first(linked_list_t *list, type_t *data)
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
}

void list_add_last(linked_list_t *list, type_t *data)
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
}

void list_add_middle(linked_list_t *list, type_t *data, int position)
{
    node_t *newNode = node_init(data);
    node_t *head = list->first;
    node_t *prevNode;
    int size = list_size(head);
    int current_position = 0;

    if(position == 0){
        list_add_first(list, data);
    } else if (position == size){
        list_add_last(list, data);
    } else if ((position < size) && (position > 0)){
        while (current_position != position-1)
        {
            current_position++;
            head = head->next;
        }
        prevNode = head;
        newNode->next = prevNode->next;
        newNode->prev = prevNode;
        if (prevNode->next != NULL){
            prevNode->next->prev = newNode;
        }
        prevNode->next = newNode;
    } else{
        printf("Error: Position is out of bounds.");
    }
}

void list_delete_first(linked_list_t *list)
{
    if(list->first == NULL){
        return;
    } else {
        node_t *temp = list->first;
        list->first = list->first->next;
        if (list->first != NULL) {
            list->first->prev = NULL;
        } else {
            list->last = NULL;
        }
        free(temp);
    }
}

void list_delete_last(linked_list_t *list)
{
    node_t *temp = NULL;

    if(list->first == NULL){
        return;
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
}
void list_delete_middle(linked_list_t *list, int position)
{
    node_t *head = list->first;
    node_t *prevNode;
    int size = list_size(head);
    int current_position = 0;

    if(position == 0){
        list_delete_first(list);
    } else if (position == size){
        list_delete_last(list);
    } else if ((position < size) && (position > 0)){
        while (current_position != position-1)
        {
            current_position++;
            head = head->next;
        }
        prevNode = head;
        head = head->next;
        prevNode->next = head->next;
        if (head->next != NULL) {
            head->next->prev = prevNode;
        } else {
            list->last = prevNode;
        }
        free(head);
    } else{
        printf("Error: Position is out of bounds.");
    }
}

void list_modify(node_t *modify, type_t *newData)
{
    modify->data = newData;
}

int list_found(linked_list_t list, type_t *data)
{
    node_t *current = list.first;
    
    while (current != NULL) {
        if (current->data == data) {
            return 1;
        }
        current = current->next;
    }
    
    return 0;
}

int list_find_position(linked_list_t list, type_t *data)
{
    node_t *head = list.first;
    int position = 0;

    while (head != NULL) {
        if(head->data == data) {
            return position;
        }
        position++;
        head = head->next;
    }
    return -1;
}

//To do: change display setting
void list_display(linked_list_t list, void (*print_data)(type_t *data))
{
    node_t *ptr = list.first;

    while (ptr != NULL) 
    {
        print_data(ptr->data);
        ptr = ptr->next;
    }
}

void list_clean(linked_list_t *list)
{
    node_t *ptr = list->first;
    node_t *before = list->first;

    while(ptr!=NULL)
    {
        ptr = ptr->next;
        free(before);
        before = ptr;
    }
    list->first = NULL;
    list->last = NULL;
}

int  list_is_empty(linked_list_t list)
{
    return list.first == NULL;
}


type_t *list_get(linked_list_t list, int position)
{
    node_t *ptr = list.first;
    int current_position = 0;

    while (ptr != NULL) {
        if (current_position == position) {
            return ptr->data;
        }
        current_position++;
        ptr = ptr->next;
    }
    return NULL;
}

void list_free_all(linked_list_t *list)
{
    node_t *ptr = list->first;
    node_t *before;

    while(ptr != NULL)
    {
        before = ptr;
        ptr = ptr->next;
        free(before->data);
        free(before);
    }
    list->first = NULL;
    list->last = NULL;
}
