<!-- # Implementation -->

## How will a synchronization-server be build

In this section the implementation of the synchronization-server will be given.

### How will the synchronization-server save the data of the finite-state machines

For storing the finite-state machine and finite-state machine derivative and their attributes structs will be used:

```{.c}
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

For determining the next action that the finite-state machines will execute, the following code snippet is used:

```{.c}
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
```

In *get_combined_actions* an array of all the actions is determined. In *get_valid_actions* the actions that are able to be executed by the current derivates is determined. In *random_action_from_actions* a random action is chosen from the array of actions, this action will be executed.

### How will the synchronization-server determine the finite-state machines that will execute an action

For determining the derivatives that will execute an action the following code snippet is used:

```{.c}
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
```

The array of derivatives is iterated and only the derivatives that have the action in their alphabet and sensitivity_list will execute the action.