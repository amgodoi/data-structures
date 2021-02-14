/**
 * test_data.c
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include "test_data.h"

/**/
void print_data(void *param)
{
    data_t *data = (data_t *) param;
    
    printf("{%d, %s}\n", data->value, data->desc);
}

/**/
void free_data(void *param)
{
    free(param);
}

