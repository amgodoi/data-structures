/**
 * main.c
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include "test_generic_list.h"

int main(int argc, char *argv[])
{
    printf("***** Testing list as queue *****\n");
    test_generic_list_queue();
    printf("\n");
    
    printf("***** Testing list as stack *****\n");
    test_generic_list_stack();
    printf("\n");
}

