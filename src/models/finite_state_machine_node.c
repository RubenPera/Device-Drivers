#ifndef FINITE_STATE_MACHINE_NODE
#define FINITE_STATE_MACHINE_NODE

#include "../models/models.h"
#include "../libraries/libraries.h"
#include "../libraries/array_functions.c"
#include "../libraries/message_functions.c"

#include "../models/finite_state_machine.c"
#include "../models/finite_state_machine_node_status.c"

finite_state_machine_node_t *finite_state_machine_node_init(
    int rec_action_endpoint,
    int send_status_endpoint,
    int transition_table[STATES][ACTIONS],
    int begin_state)
{
    finite_state_machine_node_t *self;

    self = (finite_state_machine_node_t *)malloc(sizeof(finite_state_machine_node_t));

    self->index = NO_ACTION;
    self->rec_action_endpoint = rec_action_endpoint;
    self->send_status_endpoint = send_status_endpoint;
    self->fsm = finite_state_machine_init(transition_table, begin_state);

    return self;
}

void node_send_status(finite_state_machine_node_t *self)
{
    finite_state_machine_node_status_t *status;

    status = finite_state_machine_node_status_init(self);


}

void receive_status_request(finite_state_machine_node_t *self)
{
}

int main()
{
    int begin_state = 0;

    int transition_table[STATES][ACTIONS] = {
        {NO_ACTION, 1},
        {0, NO_ACTION}};

    finite_state_machine_node_t *fsm;

    fsm = finite_state_machine_node_init(0, transition_table, begin_state);

    return 0;
}

#endif