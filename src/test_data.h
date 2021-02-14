#ifndef _TEST_DATA_H
#define _TEST_DATA_H

/**
 * test_data.h
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* bool to string */
#define btoa(x) ((x)?"true":"false")

typedef struct data_t data_t;
struct data_t
{
    char *desc;
    int value;
};

void print_data(void *param);
void free_data(void *param);

#endif /* ifndef _TEST_DATA_H */

