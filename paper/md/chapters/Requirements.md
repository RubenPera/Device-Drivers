# Requirements

The Requirements will be discussed using a use-case diagram and the MoSCoW method.

## Requirements per element that will be implemented

Per element that will be implemented will be discussed what their requirements are.

### The synchronization-server

The synchronization-server has the following requirements:

- Synchronize an unknown amount of threads.
- Determine a new action when all threads are able to execute a new action and broadcast this new action to all threads that are able to execute this action.

### Multiple threads that will follow from the FSP design

A thread or finite-state machine has the following requirements:

- Follow from a FSP design.
- Announce their presence to the synchronization-server.
- Only execute an action when this action is communicated to the thread by the finite-state machine.
- Communicate their status to the synchronization-server.

### Two device-drivers that will operate upon the outside world

The two device-drivers that will operate upon the outside world:

- Device-driver0, continuously read from the stdin.
- Device-driver1, be able to write to stdout.

### One control thread that will have its actions synchronized

The control thread will have the following requirements:

- Based upon the control thread its actions make decisions about the behaviour of the system.