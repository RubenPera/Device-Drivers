#ifndef MODELS_H
#define MODELS_H

//          libraries
#include <stdio.h>
#include <stdlib.h>

//          headers
#include "../const.h"

typedef struct
{
    int transition_table[STATES][ACTIONS];
    int sensitivity_list[ACTIONS];
    int alphabet[ACTIONS];
    int cur_state;

} finite_state_machine_t;

typedef struct
{
    finite_state_machine_t *fsm;
    int endpoint;
    int send_status_endpoint;
    int index;

} finite_state_machine_node_t;

typedef struct
{
    int endpoint;
    int index;
    int sensitivity_list[ACTIONS];
    int alphabet[ACTIONS];

} finite_state_machine_node_status_t;

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

typedef struct
{
    int action;
    finite_state_machine_node_derivative_t *derivatives[DERIVATIVES];
} action_derivatives_t;
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

//          finite_state_machine_node
finite_state_machine_node_t *finite_state_machine_node_init(
    int rec_action_endpoint,
    int send_status_endpoint,
    int transition_table[STATES][ACTIONS],
    int begin_state);
void node_send_status(finite_state_machine_node_t *self);
void receive_status_request(finite_state_machine_node_t *self);

//          finite_state_machine_node_status
finite_state_machine_node_status_t *finite_state_machine_node_status_init(
    finite_state_machine_node_t *node);

//          finite_state_machine_node_derivative
finite_state_machine_node_derivative_t *finite_state_machine_node_derivative_init(
    finite_state_machine_node_status_t *status);
void derivative_send_index(
    finite_state_machine_node_derivative_t *self,
    int sender,
    int action);
void derivative_send_action(
    finite_state_machine_node_derivative_t *self,
    int sender,
    int action);

//          synchronization_server
synchronization_server_t *synchronization_server_init(
    int endpoint);
void synchronization_server_receive_status(
    synchronization_server_t *self,
    finite_state_machine_node_status_t *status);
finite_state_machine_node_derivative_t *synchronization_server_status_to_derivative(
    finite_state_machine_node_status_t *status);
int synchronization_server_add_derivative(
    synchronization_server_t *self,
    finite_state_machine_node_derivative_t *status);
int synchronization_server_set_derivative(
    synchronization_server_t *self,
    finite_state_machine_node_derivative_t *derivative);
#endif