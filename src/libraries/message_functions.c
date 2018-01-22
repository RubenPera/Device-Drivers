#ifndef MESSAGE_FUNCTIONS
#define MESSAGE_FUNCTIONS

#include "../libraries/libraries.h"

void send_grant_and_block(
    int sender,
    int receiver,
    void *data,
    int size,
    int cpf_value)
{
#ifdef IS_MINIX
    message m;
    cp_grant_id_t grand;

    grand = gcpf_grant_direct(receiver, (vir_bytes)data, sizeof(name),
                              CPF_WRITE);
    m.m_type = 9;
    m.m_source = sender;
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
    m.m_l2 = action;

    send(receiver, &m);

#endif
}

#endif
