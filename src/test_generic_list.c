/**
 * test_generic_list.c
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include "generic_list.h"
#include "test_generic_list.h"
#include "test_data.h"

/**/
void test_generic_list_queue()
{
    generic_list_t *list = NULL;
    data_t *data = NULL;
    data_t *data1 = NULL;
    data_t *data2 = NULL;
    data_t *data3 = NULL;
    data_t *data_ret1 = NULL;
    data_t *data_ret2 = NULL;
    data_t *data_ret3 = NULL;
    size_t count = 0;
    bool stop = false;
    
    printf("Is list empty? %s, size: %lu\n", btoa(generic_list_is_empty(list)), generic_list_size(list));
    printf("Creating list...\n");
    list = generic_list_create(); 

    printf("Is list empty? %s, size: %lu\n", btoa(generic_list_is_empty(list)), generic_list_size(list));
    
    printf("Pushing back... AAA,1\n");
    data1 = malloc(sizeof(data_t));
    data1->desc = "AAA";
    data1->value = 1;
    generic_list_push_back(list, data1);

    printf("Pushing back... BBB,2\n");
    data2 = malloc(sizeof(data_t));
    data2->desc = "BBB";
    data2->value = 2;
    generic_list_push_back(list, data2);

    printf("Pushing back... CCC,3\n");
    data3 = malloc(sizeof(data_t));
    data3->desc = "CCC";
    data3->value = 3;
    generic_list_push_back(list, data3);
   
    printf("Is list empty? %s, size: %lu\n", btoa(generic_list_is_empty(list)), generic_list_size(list));

    printf("Applying all (print)...\n");
    generic_list_apply(list, print_data, NULL, NULL);
    
    printf("Applying all (print count)...\n");
    count = 0;
    stop = false;
    generic_list_apply(list, print_data_count, &count, NULL);
    
    printf("Applying all (print count stop)...\n");
    count = 0;
    stop = false;
    generic_list_apply(list, print_data_count_stop, &count, &stop);
    
    printf("Applying all reverse (print)...\n");
    generic_list_apply_reverse(list, print_data, NULL, NULL);
    
    printf("Applying all reverse (print count)...\n");
    count = 0;
    stop = false;
    generic_list_apply_reverse(list, print_data_count, &count, NULL);
    
    printf("Applying all reverse (print count stop)...\n");
    count = 0;
    stop = false;
    generic_list_apply_reverse(list, print_data_count_stop, &count, &stop);

    printf("Getting front...\n");
    data = generic_list_get_front(list);
    printf("Prints data from get_front:\n");
    print_data(data, NULL, NULL);
    
    printf("Getting back...\n");
    data = generic_list_get_back(list);
    printf("Prints data from get_back:\n");
    print_data(data, NULL, NULL);
    
    printf("Is list empty? %s, size: %lu\n", btoa(generic_list_is_empty(list)), generic_list_size(list));
        
    printf("Popping front...\n");
    data_ret1 = generic_list_pop_front(list);
    print_data(data_ret1, NULL, NULL);

    printf("Popping front...\n");
    data_ret2 = generic_list_pop_front(list);
    print_data(data_ret2, NULL, NULL);

    printf("Popping front...\n");
    data_ret3 = generic_list_pop_front(list);
    print_data(data_ret3, NULL, NULL);
        
    free(data_ret1);
    free(data_ret2);
    free(data_ret3);
    
    printf("Is list empty? %s, size: %lu\n", btoa(generic_list_is_empty(list)), generic_list_size(list));
   
    printf("Destroying list...\n");;
    list = generic_list_destroy(list, NULL); 
    
    printf("Is list empty? %s, size: %lu\n", btoa(generic_list_is_empty(list)), generic_list_size(list));
    
    printf("Creating list...\n");
    list = generic_list_create(); 
    
    printf("Pushing back 3 times... AAA,1 BBB,2 CCC,3\n");
    data1 = malloc(sizeof(data_t));
    data1->desc = "AAA";
    data1->value = 1;
    generic_list_push_back(list, data1);
    data2 = malloc(sizeof(data_t));
    data2->desc = "BBB";
    data2->value = 2;
    generic_list_push_back(list, data2);
    data3 = malloc(sizeof(data_t));
    data3->desc = "CCC";
    data3->value = 3;
    generic_list_push_back(list, data3);
    
    printf("Is list empty? %s, size: %lu\n", btoa(generic_list_is_empty(list)), generic_list_size(list));
    
    printf("Destroying list (all)...\n");
    list = generic_list_destroy(list, free_data); 

    printf("Is list empty? %s, size: %lu\n", btoa(generic_list_is_empty(list)), generic_list_size(list));
}

/**/
void test_generic_list_stack()
{
    generic_list_t *list = NULL;
    data_t *data = NULL;
    data_t *data1 = NULL;
    data_t *data2 = NULL;
    data_t *data3 = NULL;
    data_t *data_ret1 = NULL;
    data_t *data_ret2 = NULL;
    data_t *data_ret3 = NULL;
    size_t count = 0;
    bool stop = false;
    
    printf("Is list empty? %s, size: %lu\n", btoa(generic_list_is_empty(list)), generic_list_size(list));
    printf("Creating list...\n");
    list = generic_list_create(); 

    printf("Is list empty? %s, size: %lu\n", btoa(generic_list_is_empty(list)), generic_list_size(list));
    
    printf("Pushing front... AAA,1\n");
    data1 = malloc(sizeof(data_t));
    data1->desc = "AAA";
    data1->value = 1;
    generic_list_push_front(list, data1);

    printf("Pushing front... BBB,2\n");
    data2 = malloc(sizeof(data_t));
    data2->desc = "BBB";
    data2->value = 2;
    generic_list_push_front(list, data2);

    printf("Pushing front... CCC,3\n");
    data3 = malloc(sizeof(data_t));
    data3->desc = "CCC";
    data3->value = 3;
    generic_list_push_front(list, data3);
   
    printf("Is list empty? %s, size: %lu\n", btoa(generic_list_is_empty(list)), generic_list_size(list));

    printf("Applying all (print)...\n");
    generic_list_apply(list, print_data, NULL, NULL);
    
    printf("Applying all (print count)...\n");
    count = 0;
    stop = false;
    generic_list_apply(list, print_data_count, &count, NULL);
    
    printf("Applying all (print count stop)...\n");
    count = 0;
    stop = false;
    generic_list_apply(list, print_data_count_stop, &count, &stop);
    
    printf("Applying all reverse (print)...\n");
    generic_list_apply_reverse(list, print_data, NULL, NULL);
    
    printf("Applying all reverse (print count)...\n");
    count = 0;
    stop = false;
    generic_list_apply_reverse(list, print_data_count, &count, NULL);
    
    printf("Applying all reverse (print count stop)...\n");
    count = 0;
    stop = false;
    generic_list_apply_reverse(list, print_data_count_stop, &count, &stop);

    printf("Getting front...\n");
    data = generic_list_get_front(list);
    printf("Prints data from get_front:\n");
    print_data(data, NULL, NULL);
    
    printf("Getting back...\n");
    data = generic_list_get_back(list);
    printf("Prints data from get_back:\n");
    print_data(data, NULL, NULL);
    
    printf("Is list empty? %s, size: %lu\n", btoa(generic_list_is_empty(list)), generic_list_size(list));
        
    printf("Popping front...\n");
    data_ret1 = generic_list_pop_front(list);
    print_data(data_ret1, NULL, NULL);

    printf("Popping front...\n");
    data_ret2 = generic_list_pop_front(list);
    print_data(data_ret2, NULL, NULL);

    printf("Popping front...\n");
    data_ret3 = generic_list_pop_front(list);
    print_data(data_ret3, NULL, NULL);
        
    free(data_ret1);
    free(data_ret2);
    free(data_ret3);
    
    printf("Is list empty? %s, size: %lu\n", btoa(generic_list_is_empty(list)), generic_list_size(list));
   
    printf("Destroying list...\n");;
    list = generic_list_destroy(list, NULL); 
    
    printf("Is list empty? %s, size: %lu\n", btoa(generic_list_is_empty(list)), generic_list_size(list));
    
    printf("Creating list...\n");
    list = generic_list_create(); 
    
    printf("Pushing front 3 times... AAA,1 BBB,2 CCC,3\n");
    data1 = malloc(sizeof(data_t));
    data1->desc = "AAA";
    data1->value = 1;
    generic_list_push_front(list, data1);
    data2 = malloc(sizeof(data_t));
    data2->desc = "BBB";
    data2->value = 2;
    generic_list_push_front(list, data2);
    data3 = malloc(sizeof(data_t));
    data3->desc = "CCC";
    data3->value = 3;
    generic_list_push_front(list, data3);
    
    printf("Is list empty? %s, size: %lu\n", btoa(generic_list_is_empty(list)), generic_list_size(list));
    
    printf("Destroying list (all)...\n");
    list = generic_list_destroy(list, free_data); 

    printf("Is list empty? %s, size: %lu\n", btoa(generic_list_is_empty(list)), generic_list_size(list));
}

