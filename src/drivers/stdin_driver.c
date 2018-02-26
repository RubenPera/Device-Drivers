#include "../models/models.h"
#include "../libraries/libraries.h"

void run(finite_state_machine_node_t *self);
void make_transition(
    finite_state_machine_t *self,
    int action);

const int ALLOWED_KEYS[KEYS] = {'w', 'a', 's', 'd'} const int KEY_ACTIONS[KEYS] = {KEY_W, KEY_A, KEY_S, KEY_D}

void
stdin_driver_init()
{
    finite_state_machine_node_t *self;
    int endpoint = 0;
    int synchronization_server_endpoint = 0;
    int transition_table[STATES][ACTIONS] = {
        {1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,0,0,0,0,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
    };
    int begin_state = NO_ACTION;

    endpoint = minix_get_pid();
    synchronization_server_endpoint = minix_get_pid_synchronization_server();

    self = finite_state_machine_node_init(
        endpoint,
        synchronization_server_endpoint,
        transition_table,
        begin_state);

    run(self);
}

void run(finite_state_machine_node_t *self)
{
    while (1)
    {
        if (self->index == NO_ACTION)
        {
            node_send_presence_announcement(self);
            node_receive_index(self);
        }
        else
        {
            driver_receive_action(self);
        }
    }
}

void driver_receive_action(
    finite_state_machine_node_t *self)
{
    int action;

    action = receive_action();
    make_transition(self->fsm, action);
    node_send_status(self);
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

void execute_action(
    finite_state_machine_t *self,
    int action,
    int sensitivity_list[ACTIONS])
{

    fsm_set_sensitivity_list_empty(sensitivity_list);

    switch (action)
    {
    case CHECK_STDIN_VALUE:
        action_check_stdin_value(sensitivity_list);
        break;

    default:
        break;
    }
}

void action_check_stdin_value(int sensitivity_list[ACTIONS])
{
    int key = KEY_S;
    int input = 0;
    int i = 0;

    input = getchar();

    for (i = 0; i < KEYS; i++)
    {
        if (input == ALLOWED_KEYS[i])
        {
            key = KEY_ACTIONS[i];
        }
    }

    sensitivity_list[key] = HAS_ACTION;
}

//int main() {
//    driver0_init();
//}