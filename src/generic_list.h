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

/* Destroy function */
typedef void (*generic_list_destroy_t)(void *data);

/* Apply function*/
typedef void (*generic_list_apply_t)(void *data, void *data_aux, bool *stop);

/**/
extern generic_list_t *generic_list_create(void); 

/**/
extern generic_list_t *generic_list_destroy(generic_list_t *list, generic_list_destroy_t destroy); 

/**/
extern size_t generic_list_size(generic_list_t *list); 

/**/
extern bool generic_list_is_empty(generic_list_t *list); 

/**/
extern bool generic_list_push_front(generic_list_t *list, void *data);

/**/
extern void *generic_list_get_front(generic_list_t *list);

/**/
extern void *generic_list_pop_front(generic_list_t *list);

/**/
extern bool generic_list_push_back(generic_list_t *list, void *data);

/**/
extern void *generic_list_get_back(generic_list_t *list);

/**/
extern void *generic_list_pop_back(generic_list_t *list);

/**/
extern void generic_list_apply(generic_list_t *list, generic_list_apply_t apply, void *data_aux);

/**/
extern void generic_list_apply_reverse(generic_list_t *list, generic_list_apply_t apply, void *data_aux);

#endif /* ifndef _GENERIC_LIST_H */

