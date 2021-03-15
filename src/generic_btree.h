/**
 * generic_btree.h
 */

#ifndef _GENERIC_BTREE_H
#define _GENERIC_BTREE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stddef.h>
#include <stdbool.h>

/* Tree node */
typedef struct generic_btree_node_t generic_btree_node_t;
struct generic_btree_node_t
{
    void *data;
    generic_btree_node_t *left;
    generic_btree_node_t *right;
};

/* Compare function */
typedef int (*generic_btree_compare_t)(const void *data1, const void *data2);

/* Tree */
typedef struct generic_btree_t generic_btree_t;
struct generic_btree_t
{
    generic_btree_node_t *root;
    generic_btree_compare_t compare;
    size_t size;
};

/* Destroy function */
typedef void (*generic_btree_destroy_t)(void *data);

/* Apply function */
typedef void (*generic_btree_apply_t)(void *data, void *data_aux, bool *stop);

/**/
extern generic_btree_t *generic_btree_create(generic_btree_compare_t compare);

/**/
extern generic_btree_t *generic_btree_destroy(generic_btree_t *btree, generic_btree_destroy_t destroy);

/**/
extern size_t generic_btree_size(generic_btree_t *btree);

/**/
extern bool generic_btree_is_empty(generic_btree_t *btree);

/**/
extern bool generic_btree_add(generic_btree_t *btree, void *data);

/**/
extern void *generic_btree_remove(generic_btree_t *btree, void *data);

/**/
extern void *generic_btree_lookup(generic_btree_t *btree, void *data);

/**/
extern void generic_btree_apply(generic_btree_t *btree, generic_btree_apply_t apply, void *data_aux);

/**/
extern void generic_btree_apply_reverse(generic_btree_t *btree, generic_btree_apply_t apply, void *data_aux);

#endif /* ifndef _GENERIC_BTREE_H */

