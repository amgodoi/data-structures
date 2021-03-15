#ifndef _TEST_DATA_H
#define _TEST_DATA_H

/**
 * test_data.h
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdbool.h>

/* bool to string */
#define btoa(x) ((x)?"true":"false")

typedef struct data_t data_t;
struct data_t
{
    char *desc;
    int value;
};

extern void print_data(void *param, void *, bool *);
extern void print_data_count(void *param, void *param_aux, bool *);
extern void print_data_count_stop(void *param, void *param_aux, bool *stop);
extern void free_data(void *param);
extern int compare_data(const void *param1, const void *param2);

#endif /* ifndef _TEST_DATA_H */

