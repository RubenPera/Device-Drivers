

#include "../models/models.h"

typedef struct
{
    int endpoint;
    finite_state_machine_node_derivative_t *derivatives[DERIVATIVES]
} synchronization_server_t;

synchronization_server_t *synchronization_server_init(int endpoint)
{
    synchronization_server_t *self;
    self = (synchronization_server_t *)malloc(sizeof(synchronization_server_t));

    self->endpoint = endpoint;
}

void synchronization_server_receive_status(
    synchronization_server_t *self,
    finite_state_machine_node_status_t *status)
{
    finite_state_machine_node_derivative_t *derivative;
    int index = NO_ACTION;

    derivative = synchronization_server_status_to_derivative();

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
