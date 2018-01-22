#include "../models/models.h"

#include "../libraries/libraries.h"
#include "../libraries/array_functions.c"

finite_state_machine_node_status_t *finite_state_machine_node_status_init(
    finite_state_machine_node_t *node)
{
    finite_state_machine_node_status_t *self;

    self = (finite_state_machine_node_status_t *)malloc(sizeof(finite_state_machine_node_status_t));

    self->endpoint = node->rec_action_endpoint;
    self->index = node->index;
    
    array_copy(self->alphabet, node->fsm->alphabet);
    array_copy(self->sensitivity_list, node->fsm->sensitivity_list);

    return self;
}

