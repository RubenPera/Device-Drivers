# Implementation

## How will the communication between a finite-state machine and the synchronization-server take place

In this section the implementation of the communication between finite-state machine and synchronization-server will be given.

### How will a finite-state machine send their status to the synchronization-server

In this section the implementation of the finite-state machine sending its status to the synchronization-server be given.

#### What is a finite-state machine status and how will it be stored

For storing the finite-state machine status and its attributes a struct will be used:

``` C
typedef struct
{
    int endpoint;
    int index;
    int sensitivity_list[ACTIONS];
    int alphabet[ACTIONS];

} finite_state_machine_node_status_t;
```

#### How will a finite-state machine status be communicated with the synchronization-server

The finite-state machine node will use the following code snippet for sending its finite-state machine node status to the synchronization-server.

``` C
void node_send_status(finite_state_machine_node_t *self)
{
    finite_state_machine_node_status_t *status;

    status = finite_state_machine_node_status_init(self);

    send_grant_and_block(
        self->endpoint,
        self->send_status_endpoint,
        status,
        sizeof(status))
}
```

The send_grant_and_block is an abstraction method written for creating and sending grants and is included in the appendix.

The synchronization-server will use the following code snippet for receiving a finite-state machine node status.

``` C
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
```

### How will the synchronization-server communicate actions to the finite-state machines

The synchronization-server uses the following code snippet for sending the determined action to the derivatives.

``` C
void send_action_to_derivatives(synchronization_server_t *self,
    int derivatives[DERIVATIVES),
    int action )
{
    int i = 0;

    for (i = 0; i < ACTIONS; i++)
    {
        if (derivatives[i] != NO_ACTION)
        {
            derivative_send_action(self->derivatives[i], self->endpoint, action);
        }
    }
}

void derivative_send_action(
    finite_state_machine_node_derivative_t *self,
    int sender,
    int action)
{
    send_action(sender, self->endpoint, action);
}
```

The finite-state machine node uses the following code snippet for receiving the action.

``` C
void driver_receive_action(
    finite_state_machine_node_t *self)
{
    int action;

    action = receive_action();
    make_transition(self->fsm, action);
    node_send_status(self);
}
```