/**
 * generic_btree.c
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>

#include "generic_btree.h"

static void _generic_btree_node_destroy(generic_btree_node_t *node, generic_btree_destroy_t destroy);
static generic_btree_node_t *_generic_btree_node_add(generic_btree_node_t *node, void *data, 
                                                     generic_btree_compare_t compare, bool *success);
static void _generic_btree_node_apply(generic_btree_node_t *node, generic_btree_apply_t apply, void *data_aux, 
                                      bool *stop);
static void _generic_btree_node_apply_reverse(generic_btree_node_t *node, generic_btree_apply_t apply, void *data_aux, 
                                              bool *stop); 
static generic_btree_node_t *_generic_btree_node_remove(generic_btree_node_t *node, void *data, 
                                                        generic_btree_compare_t compare, void **data_ret);
static generic_btree_node_t *_min_value_btree_node(generic_btree_node_t *node);
static generic_btree_node_t *_generic_btree_node_lookup(generic_btree_node_t *node, void *data, 
                                                        generic_btree_compare_t compare);

/**/
generic_btree_t *generic_btree_create(generic_btree_compare_t compare)
{
    generic_btree_t *btree = malloc(sizeof(generic_btree_t));
    
    if (btree != NULL) {
        btree->root = NULL;
        btree->compare = compare;
        btree->size = 0;
    }

    return btree;
}

/**/
generic_btree_t *generic_btree_destroy(generic_btree_t *btree, generic_btree_destroy_t destroy)
{
    _generic_btree_node_destroy(btree->root, destroy);
    free(btree);

    return NULL;
}

/**/
static void _generic_btree_node_destroy(generic_btree_node_t *node, generic_btree_destroy_t destroy)
{
    if (node != NULL) {
        _generic_btree_node_destroy(node->left, destroy);
        _generic_btree_node_destroy(node->right, destroy);
        if (destroy != NULL) {
            destroy(node->data);
        }
        free(node);
    }
}

/**/
size_t generic_btree_size(generic_btree_t *btree)
{
    return (btree == NULL) ? 0 : btree->size;
}

/**/
extern bool generic_btree_is_empty(generic_btree_t *btree)
{
    return (btree == NULL) ? true : (btree->size == 0);
}

/**/
bool generic_btree_add(generic_btree_t *btree, void *data)
{
    bool success;

    btree->root = _generic_btree_node_add(btree->root, data, btree->compare, &success);

    if (success) {
        btree->size++;
    }

    return success;
}

/**/
static generic_btree_node_t *_generic_btree_node_add(generic_btree_node_t *node, void *data, 
                                                     generic_btree_compare_t compare, bool *success)
{
    int cond;
    
    if (node == NULL) {
        node = malloc(sizeof(generic_btree_node_t));
        if (node == NULL) {
            // no memory
            *success = false;
            return NULL;
        }
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        *success = true;
    } else if ((cond = compare(data, node->data)) == 0) {
        // data already exist
        *success = false;
    } else if (cond < 0) {
        node->left = _generic_btree_node_add(node->left, data, compare, success);
    } else {
        node->right = _generic_btree_node_add(node->right, data, compare, success);
    }

    return node;
}

/**/
void *generic_btree_remove(generic_btree_t *btree, void *data)
{
    void *data_ret;
    generic_btree_node_t *node = _generic_btree_node_remove(btree->root, data, btree->compare, &data_ret);

    btree->root = node;
    btree->size--;

    return data_ret;
}

/**/
static generic_btree_node_t *_generic_btree_node_remove(generic_btree_node_t *node, void *data, 
                                                        generic_btree_compare_t compare, void **data_ret)
{
    if (node == NULL) {
        return NULL;
    }

    // Remove left
    else if (compare(data, node->data) < 0) {
        node->left = _generic_btree_node_remove(node->left, data, compare, data_ret);
    }

    // Remove right
    else if (compare(data, node->data) > 0) {
        node->right = _generic_btree_node_remove(node->right, data, compare, data_ret);
    }

    // Found
    else {
        // Return found data as parameter
        if (data_ret) {
            *data_ret = node->data;
        }
        
        // Node with only one child or no child
        if (node->left == NULL) {
            generic_btree_node_t *temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL) {
            generic_btree_node_t* temp = node->left;
            free(node);
            return temp;
        }

        // Node with two children: get the inorder successor
        generic_btree_node_t *temp = _min_value_btree_node(node->right);

        // Copy the inorder successor's content to this node
        node->data = temp->data;
 
        // Delete the inorder successor
        node->right = _generic_btree_node_remove(node->right, temp->data, compare, NULL);
    }

    return node;
}

/**/
static generic_btree_node_t *_min_value_btree_node(generic_btree_node_t *node)
{
    generic_btree_node_t *current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

/**/
void *generic_btree_lookup(generic_btree_t *btree, void *data)
{
    generic_btree_node_t *node = _generic_btree_node_lookup(btree->root, data, btree->compare);

    return node != NULL ? node->data : NULL;
}

/**/
static generic_btree_node_t *_generic_btree_node_lookup(generic_btree_node_t *node, void *data, 
                                                        generic_btree_compare_t compare)
{
    int cond;
    
    if (node == NULL) {
        return NULL;
    } else if ((cond = compare(data, node->data)) == 0) {
        return node;
    } else if (cond < 0) {
        return _generic_btree_node_lookup(node->left, data, compare);
    } else {
        return _generic_btree_node_lookup(node->right, data, compare);
    }
}

/**/
void generic_btree_apply(generic_btree_t *btree, generic_btree_apply_t apply, void *data_aux) 
{
    bool stop = false;
    
    _generic_btree_node_apply(btree->root, apply, data_aux, &stop);
}

/**/
static void _generic_btree_node_apply(generic_btree_node_t *node, generic_btree_apply_t apply, void *data_aux, 
                                      bool *stop) 
{
    if (node != NULL && !(*stop)) {
        _generic_btree_node_apply(node->left, apply, data_aux, stop);
        if (!(*stop)) {
            apply(node->data, data_aux, stop);
            _generic_btree_node_apply(node->right, apply, data_aux, stop);
        }
    }
}


/**/
void generic_btree_apply_reverse(generic_btree_t *btree, generic_btree_apply_t apply, void *data_aux)
{
    bool stop = false;
    
    _generic_btree_node_apply_reverse(btree->root, apply, data_aux, &stop);
}

#include <stdio.h>

/**/
static void _generic_btree_node_apply_reverse(generic_btree_node_t *node, generic_btree_apply_t apply, void *data_aux, 
                                              bool *stop) 
{
    if (node != NULL && !(*stop)) {
        _generic_btree_node_apply_reverse(node->right, apply, data_aux, stop);
        if (!(*stop)) {
            apply(node->data, data_aux, stop);
            _generic_btree_node_apply_reverse(node->left, apply, data_aux, stop);
        }
    }
}

