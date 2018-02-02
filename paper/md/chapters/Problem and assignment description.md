# Problem description and assignment description

In this chapter will the problem description and task description be discussed.

## Problem description

When different processes operate independently and the sequentiality of the actions the processes execute relative to each other is important the processes need to be synchronized. If this sequentiality is not properly followed programs will exhibit behavior that is undesirable.  
For example a payment machine that keeps checking the payment card even though no product has been selected, this will lead to many unneeded operations.

## Assignment description

The assignment for this paper is to design and implement a generic synchronization-server that will synchronize a unknown amount of processes, threads and device drivers. These processes will be able to announce their presence to the synchronization-server and from then on will be synchronized.  
The processes and the synchronization-server will be implemented in the C programming language. The processes will follow from a FSP based design. processes will also be known in this paper as finite-state machines.

The following elements will be implemented and will be further discussed in the Requirements,:

- The synchronization-server.
- Multiple processes that will follow from the FSP design.
- Two device-drivers.
- One threads.