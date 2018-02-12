#ifndef FINITE_STATE_MACHINE_NODE
#define FINITE_STATE_MACHINE_NODE

#include "../models/models.h"
#include "../libraries/libraries.h"
#include "../libraries/array_functions.c"
#include "../libraries/message_functions.c"

#include "../models/finite_state_machine.c"
#include "../models/finite_state_machine_node_status.c"
#include "models.h"




finite_state_machine_node_t *finite_state_machine_node_init(
    int endpoint,
    int send_status_endpoint,
    int transition_table[STATES][ACTIONS],
    int begin_state)
{
    finite_state_machine_node_t *self;

    self = (finite_state_machine_node_t *)malloc(sizeof(finite_state_machine_node_t));

    self->index = NO_ACTION;
    self->endpoint = endpoint;
    self->send_status_endpoint = send_status_endpoint;
    self->fsm = finite_state_machine_init(transition_table, begin_state);

    return self;
}

void node_send_status(
    finite_state_machine_node_t *self)
{
    finite_state_machine_node_status_t *status;

    status = finite_state_machine_node_status_init(self);

    send_grant_and_block(
        self->endpoint,
        self->send_status_endpoint,
        status,
        sizeof(status));
}

void node_receive_action(
    finite_state_machine_node_t *self,
    int action)
{

    make_transition(self->fsm, action);

    node_send_status(self);
}

void node_send_presence_announcement(
        finite_state_machine_node_t * self)
{
    node_send_status(self);
}

void node_receive_index(finite_state_machine_node_t * self)
{

}
void receive_status_request(finite_state_machine_node_t *self)
{
}

#endif
