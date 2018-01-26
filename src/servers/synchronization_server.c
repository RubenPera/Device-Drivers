#include "../models/models.h"
#include "../libraries/libraries.h"

#include "../libraries/array_functions.c"

synchronization_server_t *synchronization_server_init(
    int endpoint)
{
    synchronization_server_t *self;
    self = (synchronization_server_t *)malloc(sizeof(synchronization_server_t));

    self->endpoint = endpoint;

    return self;
}

void synchronization_server_receive_status(
    synchronization_server_t *self,
    finite_state_machine_node_status_t *status)
{
    finite_state_machine_node_derivative_t *derivative;
    int index = NO_ACTION;

    derivative = synchronization_server_status_to_derivative(status);

    if (derivative->index == NO_INDEX)
    {
        index = synchronization_server_add_derivative(self, derivative);
        derivative_send_index(derivative, self->endpoint, index);
    }
    else
    {
        synchronization_server_set_derivative(self, derivative);
    }
}

finite_state_machine_node_derivative_t *synchronization_server_status_to_derivative(
    finite_state_machine_node_status_t *status)
{
    return finite_state_machine_node_derivative_init(status);
}

int synchronization_server_add_derivative(
    synchronization_server_t *self,
    finite_state_machine_node_derivative_t *status)
{
    int i = 0, index = NO_INDEX;
    finite_state_machine_node_derivative_t *derivative;

    for (i = 0; i < DERIVATIVES; i++)
    {
        if (self->derivatives[i] == NULL)
        {
            index = i;
            break;
        }
    }

    derivative = synchronization_server_status_to_derivative(status);
    self->derivatives[index] = derivative;

    return index;
}

int synchronization_server_set_derivative(
    synchronization_server_t *self,
    finite_state_machine_node_derivative_t *derivative)
{
    self->derivatives[derivative->index] = derivative;

    return derivative->index;
}

action_derivatives_t *executable_action_derivatives(
    synchronization_server_t *self)
{
    int action = next_action(self);
}

int next_action(
    synchronization_server_t *self)
{
    int combined_action[ACTIONS] = {NO_ACTION};
    int valid_actions[ACTIONS] = {NO_ACTION};

    array_copy(combined_action, combined_actions(self));
    array_copy(valid_actions, valid_actions(self, combined_action));
}

int random_action_from_actions(
    int actions[ACTIONS])
{
    
}

int *valid_actions(
    synchronization_server_t *self,
    int actions[ACTIONS])
{
    int a = 0, d = 0;

    int actions_to_remove[ACTIONS] = {HAS_ACTION};

    for (a = 0; a < ACTIONS; a++)
    {
        for (d = 0; d < DERIVATIVES; d++)
        {
            if (self->derivatives[d]->alphabet[a] != NO_ACTION &&
                self->derivatives[d]->sensitivity_list[a] == NO_ACTION)
            {
                actions_to_remove[a] = NO_ACTION;
            }
        }
    }

    for (a = 0; a < ACTIONS; a++)
    {
        if (actions_to_remove[a] == NO_ACTION)
        {
            actions[a] = NO_ACTION;
        }
    }

    return actions;
}

int *combined_actions(
    synchronization_server_t *self)
{
    int combined_actions[ACTIONS] = {NO_ACTION};
    int d = 0, a = 0;

    for (d = 0; d < DERIVATIVES; d++)
    {
        for (a = 0; a < ACTIONS; a++)
        {
            if (self->derivatives[d]->sensitivity_list[a] != NO_ACTION &&
                combined_actions[a] == NO_ACTION)
            {
                combined_actions[a] = HAS_ACTION;
            }
        }
    }

    return combined_actions;
}