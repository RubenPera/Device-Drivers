#include <time.h>
#include <stdlib.h>

#include "../models/models.h"
#include "../libraries/libraries.h"

void run(synchronization_server_t *self);

char derivatives_are_ready(synchronization_server_t *self);

void synchronization_server_receive_status(
    synchronization_server_t *self);

finite_state_machine_node_derivative_t *synchronization_server_status_to_derivative(
    finite_state_machine_node_status_t *status);

void derivatives_make_transition(
    synchronization_server_t *self);

int synchronization_server_add_derivative(
    synchronization_server_t *self,
    finite_state_machine_node_derivative_t *status);

int synchronization_server_set_derivative(
    synchronization_server_t *self,
    finite_state_machine_node_derivative_t *derivative);

int next_action(
    synchronization_server_t *self);

void get_executable_derivatives(
    synchronization_server_t *self,
    int derivatives[DERIVATIVES],
    int action);

void send_action_to_derivatives(
    synchronization_server_t *self,
    const int derivatives[DERIVATIVES],
    int action);

void get_combined_actions(
    synchronization_server_t *self,
    int combined_actions[ACTIONS]);

void get_valid_actions(
    synchronization_server_t *self,
    int actions[ACTIONS]);

int random_action_from_actions(
    int actions[ACTIONS]);

synchronization_server_t *synchronization_server_init(
    int endpoint)
{
    synchronization_server_t *self;
    self = (synchronization_server_t *)malloc(sizeof(synchronization_server_t));

    self->endpoint = endpoint;

    srand(time(NULL));

    run(self);
}

void run(synchronization_server_t *self)
{
    while (1)
    {
        if (derivatives_are_ready(self) == IS_READY)
        {
            derivatives_make_transition(self);
        }
        else
        {
            synchronization_server_receive_status(self);
        }
    }
}

char derivatives_are_ready(synchronization_server_t *self)
{
    int d = 0;

    for (d = 0; d < DERIVATIVES; d++)
    {
        if (self->derivatives[d] == NULL ||
            self->derivatives[d]->is_ready == NOT_READY)
        {
            return NOT_READY;
        }
    }

    return IS_READY;
}

void synchronization_server_receive_status(
    synchronization_server_t *self)
{
    finite_state_machine_node_derivative_t *derivative;

    finite_state_machine_node_status_t *status int index = NO_ACTION;

    status = receive_status();

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
    derivative->is_ready = NOT_READY;
    self->derivatives[index] = derivative;

    return index;
}

int synchronization_server_set_derivative(
    synchronization_server_t *self,
    finite_state_machine_node_derivative_t *derivative)
{
    derivative->is_ready = IS_READY;
    self->derivatives[derivative->index] = derivative;

    return derivative->index;
}

void derivatives_make_transition(
    synchronization_server_t *self)
{
    int action = 0;
    int derivatives[DERIVATIVES] = {NO_ACTION};

    action = next_action(self);

    get_executable_derivatives(self, derivatives, action);
    send_action_to_derivatives(self, derivatives, action);

    printf("Send action %d \n", action);
}

void get_executable_derivatives(
    synchronization_server_t *self,
    int derivatives[DERIVATIVES],
    int action)
{
    int d = 0;

    for (d = 0; d < DERIVATIVES; d++)
    {
        if (self->derivatives[d]->alphabet[action] != NO_ACTION &&
            self->derivatives[d]->sensitivity_list[action] != NO_ACTION)
        {
            derivatives[action] = HAS_ACTION;
        }
    }
}

void send_action_to_derivatives(
    synchronization_server_t *self,
    const int derivatives[DERIVATIVES],
    int action)
{
    int i = 0;

    for (i = 0; i < ACTIONS; i++)
    {
        if (derivatives[i] != NO_ACTION)
        {
            derivative_send_action(self->derivatives[i], self->endpoint, action);
            self->derivatives[i]->is_ready = NOT_READY;
        }
    }
}

int next_action(
    synchronization_server_t *self)
{
    int actions[ACTIONS] = {NO_ACTION};

    get_combined_actions(self, actions);

    get_valid_actions(self, actions);

    return random_action_from_actions(actions);
}

void get_valid_actions(
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
}

void get_combined_actions(
    synchronization_server_t *self,
    int combined_actions[ACTIONS])
{
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
}

int random_action_from_actions(
    int actions[ACTIONS])
{
    int i = 0, selected_action = NO_ACTION;

    for (i = rand(); i < ACTIONS; i++)
    {
        if (actions[i] != NO_ACTION)
        {
            selected_action = i;
            break;
        }
    }

    return selected_action == NO_ACTION ? random_action_from_actions(actions) : selected_action;
}