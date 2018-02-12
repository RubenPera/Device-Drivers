#ifndef MESSAGE_FUNCTIONS
#define MESSAGE_FUNCTIONS

#include <sys/socket.h>
#include "../libraries/libraries.h"
#include "../models/models.h"

void send_grant_and_block(
    int sender,
    int receiver,
    void *data,
    int size)
{
#ifdef IS_MINIX
    message m;
    cp_grant_id_t grand;

    grand = gcpf_grant_direct(receiver, (vir_bytes)data, sizeof(name),
                              CPF_WRITE);
    m.m_type = 9;
    m.m_source = sender;

    m.m9_l1 = size;
    m.m9_l2 = grand;

    sendrec(receiver, &m);
#endif
}

void send_action(
    int sender,
    int receiver,
    int action)
{
#ifdef IS_MINIX
    message m;

    m.m_type = 9;
    m.m_source = sender;
    m.m9_l2 = action;

    send(receiver, &m);

#endif
}

int minix_get_pid()
{
#ifdef IS_MINIX
    return getpid();
#endif
    return 0;
}
int minix_get_pid_synchronization_server()
{
    int synchronization_server_endpoint;

#ifdef IS_MINIX
    _pm_findproc("synchronization_server", &synchronization_server_endpoint);
    return synchronization_server_endpoint;
#endif
    return 0;
}

finite_state_machine_node_status_t * receive_status()
{

    finite_state_machine_node_status_t * status;

#ifdef  IS_MINIX
    message m;
    int s;
    int caller;
    int size;
    int grant;

    receive(ANY, &m, s);

    caller = m.m_source;
    size = m.m9_l1;
    grant = m.m9_l2;

    sys_safecopyfrom(
            caller,
            (vir_bytes)grant,
            0,
            (vir_bytes)status,
            size,
            D);
#endif

    return status;
}


int receive_index()
{
    return receive_action();
}

int receice_action()
{

    int action = 0;
#ifdef IS_MINX
    int sender;
    int s;
    message m;

    receive(ANY, &m, s);

    action =  m.m9_l2;
#endif
    return action;

}

#endif
