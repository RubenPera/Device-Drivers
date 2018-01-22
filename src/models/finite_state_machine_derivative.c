
#include "models.h"
#include "../libraries/libraries.h"

#include "../libraries/array_functions.c"
#include "../libraries/message_functions.c"

finite_state_machine_node_derivative_t *finite_state_machine_node_derivative_init(
    finite_state_machine_node_status_t *status)
{
    finite_state_machine_node_derivative_t *self;

    self = (finite_state_machine_node_derivative_t *)malloc(sizeof(finite_state_machine_node_derivative_t));

    self->endpoint = status->endpoint;

    array_copy(self->alphabet, status->alphabet);
    array_copy(self->sensitivity_list, status->sensitivity_list);

    return self;
}

void derivative_send_index(
    finite_state_machine_node_derivative_t *self,
    int sender,
    int index)
{
    send_action(sender, self->endpoint, index);
}

void derivative_send_action(
    finite_state_machine_node_derivative_t *self,
    int sender,
    int action)
{
    send_action(sender, self->endpoint, action);
}