/**
 * generic_tree.h
 */

#ifndef _GENERIC_TREE_H
#define _GENERIC_TREE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stddef.h>
#include <stdbool.h>

/* Tree node */
typedef struct generic_tree_node_t generic_tree_node_t;
struct generic_tree_node_t
{
    void *data;
    generic_tree_node_t *left;
    generic_tree_node_t *right;
};

/* Compare function */
typedef int (*generic_tree_compare_t)(const void *data1, const void *data2);

/* Tree */
typedef struct generic_tree_t generic_tree_t;
struct generic_tree_t
{
    generic_tree_node_t *root;
    generic_tree_compare_t compare;
    size_t size;
};

/* Destroy function */
typedef void (*generic_tree_destroy_t)(void *data);

/* Apply function */
typedef void (*generic_tree_apply_t)(void *data, void *data_aux, bool *stop);

/**/
extern generic_tree_t *generic_tree_create(generic_tree_compare_t compare);

/**/
extern generic_tree_t *generic_tree_destroy(generic_tree_t *tree, generic_tree_destroy_t destroy);

/**/
extern size_t generic_tree_size(generic_tree_t *tree);

/**/
extern bool generic_tree_is_empty(generic_tree_t *tree);

/**/
extern bool generic_tree_add(generic_tree_t *tree, void *data);

/**/
extern void *generic_tree_remove(generic_tree_t *tree, void *data);

/**/
extern void *generic_tree_lookup(generic_tree_t *tree, void *data);

/**/
extern void generic_tree_apply(generic_tree_t *tree, generic_tree_apply_t apply, void *data_aux);

/**/
extern void generic_tree_apply_reverse(generic_tree_t *tree, generic_tree_apply_t apply, void *data_aux);

#endif /* ifndef _GENERIC_TREE_H */

