/**
 * generic_list.c
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>

#include "generic_list.h"

/**/
generic_list_t *generic_list_create() 
{
    generic_list_t *list = malloc(sizeof(generic_list_t));
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }

    return list;
}

/**/
generic_list_t *generic_list_destroy(generic_list_t *list, void(*destroy)(void *)) 
{
    generic_list_node_t *next = NULL;

    for (generic_list_node_t *node = list->head; node != NULL; node = next) {
        next = node->next;
        if (destroy != NULL) {
            destroy(node->data);
        }
        free(node);
    }
    
    free(list);

    return NULL;
}

/**/
size_t generic_list_size(generic_list_t *list) {
    return (list == NULL) ? 0 : list->size;
}

/**/
bool generic_list_is_empty(generic_list_t *list) {
    return (list == NULL) ? true : (list->size == 0);
}

/**/
bool generic_list_push_front(generic_list_t *list, void *data) 
{
    generic_list_node_t *node = malloc(sizeof(generic_list_node_t));
    if (node == NULL) {
        return false;
    }
    
    node->data = data;
    node->prev = NULL;
    node->next = list->head;

    if (list->head == NULL) {
        list->tail = node;
    } else {
        list->head->prev = node;
    }

    list->head = node;
    list->size++;

    return true;
}

/**/
void *generic_list_get_front(generic_list_t *list) 
{
    generic_list_node_t *node = NULL;
    void *data = NULL;
  
    if (list->head == NULL) {
        return NULL;
    }
    
    node = list->head;
    data = node->data;

    return data;
}

/**/
void *generic_list_pop_front(generic_list_t *list) 
{
    generic_list_node_t *node = NULL;
    void *data = NULL;
  
    if (list->head == NULL) {
        return NULL;
    }
    
    node = list->head;
    data = node->data;

    list->head = list->head->next;
    if (list->head == NULL) {
        list->tail = NULL;
    } else {
        list->head->prev = NULL;
    }

    list->size--;
    free(node);

    return data;
}

/**/
bool generic_list_push_back(generic_list_t *list, void *data) {
    generic_list_node_t *node = malloc(sizeof(generic_list_node_t));
    if (node == NULL) {
        return false;
    }
    
    node->data = data;
    node->prev = list->tail;
    node->next = NULL;

    if (list->tail == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    list->tail = node;
    list->size++;

    return true;
}

/**/
void *generic_list_get_back(generic_list_t *list) {
    generic_list_node_t *node = NULL;
    void *data = NULL;
  
    if (list->tail == NULL) {
        return NULL;
    }
    
    node = list->tail;
    data = node->data;

    return data;
}

/**/
void *generic_list_pop_back(generic_list_t *list) {
    generic_list_node_t *node = NULL;
    void *data = NULL;
  
    if (list->tail == NULL) {
        return NULL;
    }
    
    node = list->tail;
    data = node->data;

    list->tail = list->tail->prev;
    if (list->tail == NULL) {
        list->head = NULL;
    } else {
        list->tail->next = NULL;
    }

    list->size--;
    free(node);

    return data;
}

/**/
void generic_list_apply(generic_list_t *list, void(*apply)(void *)) {
    for (generic_list_node_t *node = list->head; node != NULL; node = node->next) {
        apply(node->data);
    }
}

/**/
void generic_list_apply_reverse(generic_list_t *list, void(*apply)(void *)) {
    for (generic_list_node_t *node = list->tail; node != NULL; node = node->prev) {
        apply(node->data);
    }
}

