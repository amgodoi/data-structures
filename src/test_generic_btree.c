/**
 * test_generic_btree.c
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "generic_btree.h"
#include "test_generic_btree.h"
#include "test_data.h"

/**/
void test_generic_btree()
{
    generic_btree_t *btree = NULL;
    data_t *data = NULL;
    data_t *data1 = NULL;
    data_t *data2 = NULL;
    data_t *data3 = NULL;
    data_t *data4 = NULL;
    data_t *data5 = NULL;
    size_t count = 0;
 
    data1 = malloc(sizeof(data_t));
    data1->desc = "AAA";
    data1->value = 1;
    
    data2 = malloc(sizeof(data_t));
    data2->desc = "BBB";
    data2->value = 2;
    
    data3 = malloc(sizeof(data_t));
    data3->desc = "CCC";
    data3->value = 3;
    
    data4 = malloc(sizeof(data_t));
    data4->desc = "DDD";
    data4->value = 4;
    
    data5 = malloc(sizeof(data_t));
    data5->desc = "EEE";
    data5->value = 5;
    
    /******************************************************************************************************************/
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    printf("-> Creating btree...\n");
    btree = generic_btree_create(compare_data); 
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... AAA,1\n");
    generic_btree_add(btree, data1);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));

    printf("-> Adding... BBB,2\n");
    generic_btree_add(btree, data2);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));

    printf("-> Adding... CCC,3\n");
    generic_btree_add(btree, data3);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... DDD,4\n");
    generic_btree_add(btree, data4);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... EEE,5\n");
    generic_btree_add(btree, data5);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... AAA,1\n");
    printf("-> errno: %d\n", errno);
    generic_btree_add(btree, data1);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Applying all (print)...\n");
    generic_btree_apply(btree, print_data, NULL);
    
    printf("-> Applying all (print count)...\n");
    count = 0;
    generic_btree_apply(btree, print_data_count, &count);
    
    printf("-> Applying all (print count stop before 2)...\n");
    count = 0;
    generic_btree_apply(btree, print_data_count_stop, &count);
    
    printf("-> Applying all reverse (print)...\n");
    generic_btree_apply_reverse(btree, print_data, NULL);
    
    printf("-> Applying all reverse (print count)...\n");
    count = 0;
    generic_btree_apply_reverse(btree, print_data_count, &count);
    
    printf("-> Applying all reverse (print count stop before 2)...\n");
    count = 0;
    generic_btree_apply_reverse(btree, print_data_count_stop, &count);
    
    printf("-> Destroying btree...\n");
    btree = generic_btree_destroy(btree, NULL); 
    //btree = generic_btree_destroy(btree, free_data); 
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    /******************************************************************************************************************/
    printf("-> Creating btree...\n");
    btree = generic_btree_create(compare_data); 
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... EEE,5\n");
    generic_btree_add(btree, data5);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... DDD,4\n");
    generic_btree_add(btree, data4);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... CCC,3\n");
    generic_btree_add(btree, data3);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... BBB,2\n");
    generic_btree_add(btree, data2);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... AAA,1\n");
    generic_btree_add(btree, data1);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Applying all (print)...\n");
    generic_btree_apply(btree, print_data, NULL);
    
    printf("-> Applying all (print count)...\n");
    count = 0;
    generic_btree_apply(btree, print_data_count, &count);
    
    printf("-> Applying all (print count stop before 2)...\n");
    count = 0;
    generic_btree_apply(btree, print_data_count_stop, &count);
    
    printf("-> Applying all reverse (print)...\n");
    generic_btree_apply_reverse(btree, print_data, NULL);
    
    printf("-> Applying all reverse (print count)...\n");
    count = 0;
    generic_btree_apply_reverse(btree, print_data_count, &count);
    
    printf("-> Applying all reverse (print count stop before 2)...\n");
    count = 0;
    generic_btree_apply_reverse(btree, print_data_count_stop, &count);
    
    printf("-> Destroying btree...\n");
    btree = generic_btree_destroy(btree, NULL); 
    //btree = generic_btree_destroy(btree, free_data); 
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    /******************************************************************************************************************/
    printf("-> Creating btree...\n");
    btree = generic_btree_create(compare_data); 
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... CCC,3\n");
    generic_btree_add(btree, data3);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... AAA,1\n");
    generic_btree_add(btree, data1);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... EEE,5\n");
    generic_btree_add(btree, data5);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... BBB,2\n");
    generic_btree_add(btree, data2);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... DDD,4\n");
    generic_btree_add(btree, data4);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Applying all (print)...\n");
    generic_btree_apply(btree, print_data, NULL);
    
    printf("-> Applying all (print count)...\n");
    count = 0;
    generic_btree_apply(btree, print_data_count, &count);
    
    printf("-> Applying all (print count stop before 2)...\n");
    count = 0;
    generic_btree_apply(btree, print_data_count_stop, &count);
    
    printf("-> Applying all reverse (print)...\n");
    generic_btree_apply_reverse(btree, print_data, NULL);
    
    printf("-> Applying all reverse (print count)...\n");
    count = 0;
    generic_btree_apply_reverse(btree, print_data_count, &count);
    
    printf("-> Applying all reverse (print count stop before 2)...\n");
    count = 0;
    generic_btree_apply_reverse(btree, print_data_count_stop, &count);
    
    printf("-> Destroying btree...\n");
    //btree = generic_btree_destroy(btree, NULL); 
    btree = generic_btree_destroy(btree, free_data); 
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    /******************************************************************************************************************/
    data1 = malloc(sizeof(data_t));
    data1->desc = "AAA";
    data1->value = 1;
    
    data2 = malloc(sizeof(data_t));
    data2->desc = "BBB";
    data2->value = 2;
    
    data3 = malloc(sizeof(data_t));
    data3->desc = "CCC";
    data3->value = 3;
    
    data4 = malloc(sizeof(data_t));
    data4->desc = "DDD";
    data4->value = 4;
    
    data5 = malloc(sizeof(data_t));
    data5->desc = "EEE";
    data5->value = 5;
    
    /******************************************************************************************************************/
    printf("-> Creating btree...\n");
    btree = generic_btree_create(compare_data); 
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... AAA,1\n");
    generic_btree_add(btree, data1);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));

    printf("-> Adding... BBB,2\n");
    generic_btree_add(btree, data2);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));

    printf("-> Adding... CCC,3\n");
    generic_btree_add(btree, data3);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... DDD,4\n");
    generic_btree_add(btree, data4);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Adding... EEE,5\n");
    generic_btree_add(btree, data5);
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));

    printf("-> Applying all (print)...\n");
    generic_btree_apply(btree, print_data, NULL);
    
    printf("-> Applying all reverse (print)...\n");
    generic_btree_apply_reverse(btree, print_data, NULL);
    
    printf("-> Lookup and print DDD...\n");
    data_t data_search_1 = {"DDD", 0};
    data = generic_btree_lookup(btree, &data_search_1);
    print_data(data, NULL, NULL);
    
    printf("-> Lookup and print AAA...\n");
    data_t data_search_2 = {"AAA", 0};
    data = generic_btree_lookup(btree, &data_search_2);
    print_data(data, NULL, NULL);
    
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Applying all (print)...\n");
    generic_btree_apply(btree, print_data, NULL);
    
    printf("-> Applying all reverse (print)...\n");
    generic_btree_apply_reverse(btree, print_data, NULL);
    
    printf("-> Remove and print DDD...\n");
    data_t data_search_3 = {"DDD", 0};
    data = generic_btree_remove(btree, &data_search_3);
    print_data(data, NULL, NULL);
    free(data);
    
    printf("-> Remove and print AAA...\n");
    data_t data_search_4 = {"AAA", 0};
    data = generic_btree_remove(btree, &data_search_4);
    print_data(data, NULL, NULL);
    free(data);
    
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
    
    printf("-> Applying all (print)...\n");
    generic_btree_apply(btree, print_data, NULL);
    
    printf("-> Applying all reverse (print)...\n");
    generic_btree_apply_reverse(btree, print_data, NULL);
    
    printf("-> Destroying btree...\n");
    //btree = generic_btree_destroy(btree, NULL); 
    btree = generic_btree_destroy(btree, free_data); 
    printf("-> Is tree empty? %s, size: %lu\n", btoa(generic_btree_is_empty(btree)), generic_btree_size(btree));
}

