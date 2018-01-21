
#include "models.h"

finite_state_machine_derivative_t *fsm_derivative_init(finite_state_machine_t *fsm, int endpoint)
{
    finite_state_machine_derivative_t *self;

    self = (finite_state_machine_derivative_t *)malloc(sizeof(finite_state_machine_derivative_t));

    self->endpoint = endpoint;

    return self;
}