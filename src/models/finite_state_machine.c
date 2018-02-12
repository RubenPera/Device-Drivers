#ifndef FINITE_STATE_MACHINE
#define FINITE_STATE_MACHINE

#include "models.h"
#include "../libraries/libraries.h"

finite_state_machine_t *finite_state_machine_init(
    int transition_table[STATES][ACTIONS],
    int begin_state)
{
    finite_state_machine_t *self;

    self = (finite_state_machine_t *)malloc(sizeof(finite_state_machine_t));

    self->cur_state = begin_state;

    fsm_set_transition_table(self, transition_table);
    fsm_set_alphabet(self);
    fsm_set_sensitivity_list_from_cur_state(self);

    return self;
}

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

void fsm_set_transition_table(
    finite_state_machine_t *self,
    int transition_table[STATES][ACTIONS])
{
    int s = 0, a = 0;
    for (s = 0; s < STATES; s++)
    {
        for (a = 0; a < ACTIONS; a++)
        {
            self->transition_table[s][a] =
                transition_table[s][a];
        }
    }
}

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

void fsm_set_sensitivity_list_from_cur_state(
    finite_state_machine_t *self)
{
    fsm_set_sensitivity_list(self, self->transition_table[self->cur_state]);
}

void fsm_set_sensitivity_list(
    finite_state_machine_t *self,
    int sensitivity_list[ACTIONS])
{
    array_copy((int *)self->sensitivity_list, (int *)self->transition_table[self->cur_state]);
}

    // int main()
    // {
    //     int begin_state = 0;

    //     int transition_table[STATES][ACTIONS] = {
    //         {NO_ACTION, 1},
    //         {0, NO_ACTION}};

    //     finite_state_machine_t *fsm = finite_state_machine_init(transition_table, begin_state);

    //     return 0;
    // }

#endif
