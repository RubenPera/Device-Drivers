# Implementation

## How will a synchronization-server be build

In this section the implementation of the synchronization-server will be given.

### How will the synchronization-server save the data of the finite-state machines

For storing the finite-state machine and finite-state machine derivative and their attributes structs will be used:

``` C
typedef struct
{
    int sensitivity_list[ACTIONS];
    int alphabet[ACTIONS];
    int endpoint;
    int index;
} finite_state_machine_node_derivative_t;

typedef struct
{
    int endpoint;
    finite_state_machine_node_derivative_t *derivatives[DERIVATIVES];
} synchronization_server_t;
```

### How will the synchronization-server determine the next action for the finite-state machines

For determining the next action that the finite-state machines will execute the following code snippet is used:

``` C
int next_action(
    synchronization_server_t *self)
{
    int combined_action[ACTIONS] = {NO_ACTION};
    int valid_actions[ACTIONS] = {NO_ACTION};

    array_copy(combined_action, combined_actions(self));
    array_copy(valid_actions, valid_actions(self, combined_action));

    return random_action_from_actions(valid_actions);
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

int combined_actions(
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
```

### How will the synchronization-server determine the finite-state machines that will execute an action

For determining the finite-state machines will execute an action the following code snippet is used:

``` C
void get_executable_derivatives(
    synchronization_server_t *self,
    int derivatives[DERIVATIVES),
    int action
{
    int i = 0;

    for (i = 0; i < ACTIONS; i++)
    {
        if (self->derivatives[i].alphabet != NO_ACTION &&
            self->derivatives[i].sensitivity_list != NO_ACTION)
        {
            derivatives[i] = HAS_ACTION;
        }
    }
}
```