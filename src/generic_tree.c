/**
 * generic_tree.c
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>

#include "generic_tree.h"

static void _generic_tree_node_destroy(generic_tree_node_t *node, generic_tree_destroy_t destroy);
static generic_tree_node_t *_generic_tree_node_add(generic_tree_node_t *node, void *data, 
                                                   generic_tree_compare_t compare, bool *success);
static void _generic_tree_node_apply(generic_tree_node_t *node, generic_tree_apply_t apply, void *data_aux, 
                                     bool *stop);
static void _generic_tree_node_apply_reverse(generic_tree_node_t *node, generic_tree_apply_t apply, void *data_aux, 
                                             bool *stop); 
static generic_tree_node_t *_generic_tree_node_remove(generic_tree_node_t *node, void *data, 
                                                      generic_tree_compare_t compare, void **data_ret);
static generic_tree_node_t *_min_value_tree_node(generic_tree_node_t *node);
static generic_tree_node_t *_generic_tree_node_lookup(generic_tree_node_t *node, void *data, 
                                                      generic_tree_compare_t compare);

/**/
generic_tree_t *generic_tree_create(generic_tree_compare_t compare)
{
    generic_tree_t *tree = malloc(sizeof(generic_tree_t));
    
    if (tree != NULL) {
        tree->root = NULL;
        tree->compare = compare;
        tree->size = 0;
    }

    return tree;
}

/**/
generic_tree_t *generic_tree_destroy(generic_tree_t *tree, generic_tree_destroy_t destroy)
{
    _generic_tree_node_destroy(tree->root, destroy);
    free(tree);

    return NULL;
}

/**/
static void _generic_tree_node_destroy(generic_tree_node_t *node, generic_tree_destroy_t destroy)
{
    if (node != NULL) {
        _generic_tree_node_destroy(node->left, destroy);
        _generic_tree_node_destroy(node->right, destroy);
        if (destroy != NULL) {
            destroy(node->data);
        }
        free(node);
    }
}

/**/
size_t generic_tree_size(generic_tree_t *tree)
{
    return (tree == NULL) ? 0 : tree->size;
}

/**/
extern bool generic_tree_is_empty(generic_tree_t *tree)
{
    return (tree == NULL) ? true : (tree->size == 0);
}

/**/
bool generic_tree_add(generic_tree_t *tree, void *data)
{
    bool success;

    tree->root = _generic_tree_node_add(tree->root, data, tree->compare, &success);

    if (success) {
        tree->size++;
    }

    return success;
}

/**/
static generic_tree_node_t *_generic_tree_node_add(generic_tree_node_t *node, void *data, 
                                                   generic_tree_compare_t compare, bool *success)
{
    int cond;
    
    if (node == NULL) {
        node = malloc(sizeof(generic_tree_node_t));
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
        node->left = _generic_tree_node_add(node->left, data, compare, success);
    } else {
        node->right = _generic_tree_node_add(node->right, data, compare, success);
    }

    return node;
}

/**/
void *generic_tree_remove(generic_tree_t *tree, void *data)
{
    void *data_ret;
    generic_tree_node_t *node = _generic_tree_node_remove(tree->root, data, tree->compare, &data_ret);

    tree->root = node;
    tree->size--;

    return data_ret;
}

/**/
static generic_tree_node_t *_generic_tree_node_remove(generic_tree_node_t *node, void *data, 
                                                      generic_tree_compare_t compare, void **data_ret)
{
    if (node == NULL) {
        return NULL;
    }

    // Remove left
    else if (compare(data, node->data) < 0) {
        node->left = _generic_tree_node_remove(node->left, data, compare, data_ret);
    }

    // Remove right
    else if (compare(data, node->data) > 0) {
        node->right = _generic_tree_node_remove(node->right, data, compare, data_ret);
    }

    // Found
    else {
        // Return found data as parameter
        if (data_ret) {
            *data_ret = node->data;
        }
        
        // Node with only one child or no child
        if (node->left == NULL) {
            generic_tree_node_t *temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL) {
            generic_tree_node_t* temp = node->left;
            free(node);
            return temp;
        }

        // Node with two children: get the inorder successor
        generic_tree_node_t *temp = _min_value_tree_node(node->right);

        // Copy the inorder successor's content to this node
        node->data = temp->data;
 
        // Delete the inorder successor
        node->right = _generic_tree_node_remove(node->right, temp->data, compare, NULL);
    }

    return node;
}

/**/
static generic_tree_node_t *_min_value_tree_node(generic_tree_node_t *node)
{
    generic_tree_node_t *current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

/**/
void *generic_tree_lookup(generic_tree_t *tree, void *data)
{
    generic_tree_node_t *node = _generic_tree_node_lookup(tree->root, data, tree->compare);

    return node != NULL ? node->data : NULL;
}

/**/
static generic_tree_node_t *_generic_tree_node_lookup(generic_tree_node_t *node, void *data, 
                                                      generic_tree_compare_t compare)
{
    int cond;
    
    if (node == NULL) {
        return NULL;
    } else if ((cond = compare(data, node->data)) == 0) {
        return node;
    } else if (cond < 0) {
        return _generic_tree_node_lookup(node->left, data, compare);
    } else {
        return _generic_tree_node_lookup(node->right, data, compare);
    }
}

/**/
void generic_tree_apply(generic_tree_t *tree, generic_tree_apply_t apply, void *data_aux) 
{
    bool stop = false;
    
    _generic_tree_node_apply(tree->root, apply, data_aux, &stop);
}

/**/
static void _generic_tree_node_apply(generic_tree_node_t *node, generic_tree_apply_t apply, void *data_aux, 
                                     bool *stop) 
{
    if (node != NULL && !(*stop)) {
        _generic_tree_node_apply(node->left, apply, data_aux, stop);
        if (!(*stop)) {
            apply(node->data, data_aux, stop);
            _generic_tree_node_apply(node->right, apply, data_aux, stop);
        }
    }
}


/**/
void generic_tree_apply_reverse(generic_tree_t *tree, generic_tree_apply_t apply, void *data_aux)
{
    bool stop = false;
    
    _generic_tree_node_apply_reverse(tree->root, apply, data_aux, &stop);
}

#include <stdio.h>

/**/
static void _generic_tree_node_apply_reverse(generic_tree_node_t *node, generic_tree_apply_t apply, void *data_aux, 
                                             bool *stop) 
{
    if (node != NULL && !(*stop)) {
        _generic_tree_node_apply_reverse(node->right, apply, data_aux, stop);
        if (!(*stop)) {
            apply(node->data, data_aux, stop);
            _generic_tree_node_apply_reverse(node->left, apply, data_aux, stop);
        }
    }
}

