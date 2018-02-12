#ifndef LIBRARIES_H
#define LIBRARIES_H

#include "../const.h"

//          array_functions
void array_copy(
    void list_to[ACTIONS],
    void list_from[ACTIONS]);

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
int receive_index();
int receive_action();

int minix_get_pid();
int minix_get_pid_synchronization_server();
finite_state_machine_node_status_t * receive_status();
#endif
