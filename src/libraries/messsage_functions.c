#ifndef MESSAGE_FUNCTIONS
#define MESSAGE_FUNCTIONS

#include "../libraries/libraries.h"

void send_grant_and_block(int sender, int receiver, void *date, int size, int cpf_value)
{
#ifdef IS_MINIX
    message m;

    m.m_type = 9;
    m.m_source = sender;

    cp_grant_id_t grand;
    grand = gcpf_grant_direct(receiver, (vir_bytes)data, sizeof(name),
                              CPF_WRITE);

    m.m9_l2 = grand;

    sendrec(receiver, &m);
#endif
}

#endif
