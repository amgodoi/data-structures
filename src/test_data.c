/**
 * test_data.c
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_data.h"

/**/
void print_data(void *param, void *unused1, bool *unused2)
{
    data_t *data = (data_t *) param;
    
    printf("{%d, %s}\n", data->value, data->desc);
}

/**/
void print_data_count(void *param, void *param_aux, bool *unused) 
{
    data_t *data = (data_t *) param;
    size_t *count = (size_t *) param_aux;
    
    if (count) {
        printf("{%d, %s} count: %lu\n", data->value, data->desc, *count);
        (*count)++;
    } else {
        printf("{%d, %s}\n", data->value, data->desc);
    }
}

/**/
void print_data_count_stop(void *param, void *param_aux, bool *stop)
{
    data_t *data = (data_t *) param;
    size_t *count = (size_t *) param_aux;
    
    if (count) {
        printf("{%d, %s} count: %lu\n", data->value, data->desc, *count);
        (*count)++;
        if (*count == 2) {
            printf("Stopping loop!\n");
            *stop = true;
        }
    } else {
        printf("{%d, %s}\n", data->value, data->desc);
    }
}

/**/
void free_data(void *param)
{
    free(param);
}

int compare_data(const void *param1, const void *param2)
{
    data_t *data1 = (data_t *) param1;
    data_t *data2 = (data_t *) param2;

    return strcmp(data1->desc, data2->desc);
}

