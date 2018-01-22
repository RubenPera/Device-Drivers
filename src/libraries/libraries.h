#ifndef LIBRARIES_H
#define LIBRARIES_H

#include "../const.h"

//          array_functions
void array_copy(
    int list_to[ACTIONS],
    int list_from[ACTIONS]);

//          message_functions
void send_grant_and_block(
    int sender,
    int receiver,
    void *data,
    int size,
    int cpf_value);
void send_action(
    int sender,
    int receiver,
    int action);
#endif
