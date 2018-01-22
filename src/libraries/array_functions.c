#ifndef ARRAY_FUNCTIONS
#define ARRAY_FUNCTIONS

#include "models.h"

void array_copy(int list_to[ACTIONS], int list_from[ACTIONS])
{
    int i = 0;

    for (i = 0; i < ACTIONS; i++)
    {
        list_to[i] = list_from[i];
    }
}

#endif
