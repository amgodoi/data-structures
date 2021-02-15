/**
 * generic_list.h
 */

#ifndef _GENERIC_LIST_H
#define _GENERIC_LIST_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stddef.h>
#include <stdbool.h>

/* List node */
typedef struct generic_list_node_t generic_list_node_t;
struct generic_list_node_t
{
    void *data;
    generic_list_node_t *prev;
    generic_list_node_t *next;
};

/* List */
typedef struct generic_list_t generic_list_t;
struct generic_list_t
{
    generic_list_node_t *head;
    generic_list_node_t *tail;
    size_t size;
};

/* Function to apply to data list.
 * Data node, auxiliary data and a condition to stop the list loop. */
typedef void (*apply_t)(void *data, void *data_aux, bool *stop);

/* Creates a generic list. 
 * Returns NULL if out of memory (errno == ENOMEM). */
extern generic_list_t *generic_list_create(); 

/* Destroys the generic list (frees all nodes).
 * Optional destroy() function to free each previous allocated data memory. 
 * Returns NULL always. */
extern generic_list_t *generic_list_destroy(generic_list_t *list, void(*destroy)(void *)); 

/* Returns list size. */
extern size_t generic_list_size(generic_list_t *list); 

/* Returns true if list is empty. */
extern bool generic_list_is_empty(generic_list_t *list); 

/* Adds data to head. 
 * Returns false if out of memory (errno == ENOMEM). */
extern bool generic_list_push_front(generic_list_t *list, void *data);

/* Returns data from head (does not free node memory). */
extern void *generic_list_get_front(generic_list_t *list);

/* Returns data from head (frees node memory). */
extern void *generic_list_pop_front(generic_list_t *list);

/* Adds data to tail. 
 * Returns false if out of memory (errno == ENOMEM). */
extern bool generic_list_push_back(generic_list_t *list, void *data);

/* Returns data from tail (does not free node memory). */
extern void *generic_list_get_back(generic_list_t *list);

/* Returns data from tail (frees node memory). */
extern void *generic_list_pop_back(generic_list_t *list);

/* Applies function to list from head until tail. */
extern void generic_list_apply(generic_list_t *list, apply_t apply, void *data_aux);

/* Applies function to list from tail until head. */
extern void generic_list_apply_reverse(generic_list_t *list, apply_t apply, void *data_aux);

#endif /* ifndef _GENERIC_LIST_H */

