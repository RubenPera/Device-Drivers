#ifndef ARRAY_FUNCTIONS
#define ARRAY_FUNCTIONS

#include "../models/models.h"

void array_copy(void list_to[ACTIONS], void list_from[ACTIONS])
{
    int i = 0;

    for (i = 0; i < ACTIONS; i++)
    {
        list_to[i] = list_from[i];
    }
}

#endif
