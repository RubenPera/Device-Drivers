#ifndef MODELS_H
#define MODELS_H

#include <stdio.h>
#include <stdlib.h>

//          headers
#include "../const.h"

//          code
// #include "../models/finite_state_machine.c"
// #include "../models/array_functions.c"
// #include "../nodes/finite_state_machine_node.c"

typedef struct
{
    int transition_table[STATES][ACTIONS];
    int sensitivity_list[ACTIONS];
    int alphabet[ACTIONS];
    int cur_state;

} finite_state_machine_t;

typedef struct
{
    int sensitivity_list[ACTIONS];
    int alphabet[ACTIONS];
    int endpoint;
} finite_state_machine_derivative_t;

//          finite_state_machine
finite_state_machine_t *finite_state_machine_init(
    int transition_table[STATES][ACTIONS],
    int begin_state);
void fsm_set_transition_table(
    finite_state_machine_t *self,
    int transition_table[STATES][ACTIONS]);
void fsm_set_alphabet(
    finite_state_machine_t *self);
void fsm_set_sensitivity_list_from_cur_state(
    finite_state_machine_t *self);
void fsm_set_sensitivity_list(
    finite_state_machine_t *self,
    int sensitivity_list[ACTIONS]);

//          finite_state_machine_node_derivative
finite_state_machine_derivative_t *fsm_derivative_init(
    finite_state_machine_t *fsm,
    int endpoint);

//          array_functions
void array_copy(
    int list_to[ACTIONS],
    int list_from[ACTIONS]);

#endif