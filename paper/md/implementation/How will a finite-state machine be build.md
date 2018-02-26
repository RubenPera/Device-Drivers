# Implementation

## How will a finite-state machine be build

In this section the implementation of the finite-state machine will be given.

### How will a finite-state machine save its transition-table, sensitivity-list and alphabet

For storing the finite-state machine and its attributes a struct will be used:

``` C
typedef struct
{
    int transition_table[STATES][ACTIONS];
    int sensitivity_list[ACTIONS];
    int alphabet[ACTIONS];
    int cur_state;

} finite_state_machine_t;
```

STATES are the total amount of states and ACTIONS are the total amount of actions. As C does not support arrays of undetermined sizes, the total amount of states and actions must be known during compilation, these and other constant values are stored in one shared constant file.

### How will a finite-state machine determine its sensitivity-list and alphabet

In this section the implementation of determining the sensitivity-list and alphabet will be provided.

#### How will a finite-state machine determine its sensitivity-list

For determining the finite-state machine its sensitivity-list the following code snippet is used:

``` C
void fsm_set_sensitivity_list(
    finite_state_machine_t *self,
    int sensitivity_list[ACTIONS])
{
    array_copy((int *)self->sensitivity_list, (int *)self->transition_table[self->cur_state]);
}
```

The used function array_copy copies the values of one array to the other array and will be included in the appendix.

#### How will a finite-state machine determine its alphabet

For determining the finite-state machine its alphabet the following code snippet is used:

``` C
void fsm_set_alphabet(
    finite_state_machine_t *self)
{
    int s = 0, a = 0;

    for (s = 0; s < STATES; s++)
    {
        for (a = 0; a < 0; a++)
        {
            if (self->transition_table[s][a] != NO_ACTION &&
                self->alphabet[a] == NO_ACTION)
            {
                self->alphabet[a] = HAS_ACTION;
            }
        }
    }
}
```

### How will a finite-state machine make transitions

For making transitions the finite-state machine uses the following code snippet.

``` C
void make_transition(
    finite_state_machine_t *self,
    int action)
{
    int sensitivity_list[ACTIONS];

    if (fsm_can_execute_action(self, action))
    {
        execute_action(self, action, sensitivity_list);

        if (sensitivity_list != NULL)
        {
            array_copy(self->sensitivity_list, sensitivity_list);
            self->cur_state = fsm_next_state(self, action);
        }
    }
}

int fsm_can_execute_action(
    finite_state_machine_t *self,
    int action)
{
    return fsm_next_state(self, action) != NO_ACTION;
}

int fsm_next_state(
    finite_state_machine_t *self,
    int action)
{
    return self->transition_table[self->cur_state][action];
}
```

However, the function make_transition has to implemented by each finite-state machine that uses it, as the function execute_action is different for every finite-state machine implementation.