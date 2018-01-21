

#include "models.h"

typedef struct
{
    int endpoint;
    finite_state_machine_derivative_t *derivative[DERIVATIVES]
} synchronization_server_t;

synchronization_server_t *synchronization_server_init(int endpoint)
{
    synchronization_server_t *self;
    self = (synchronization_server_t *)malloc(sizeof(synchronization_server_t));

    self->endpoint = endpoint;
}
