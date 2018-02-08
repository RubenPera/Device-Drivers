# Design

In this chapter the design of the application will be discussed.

First the class diagram will be discussed, thereafter the sequence diagrams illustrating key operations, and lastly the LTS model for the application that will be build in this paper.

## Class-diagram

![Class diagram](/diagrams/class_diagram.png "test")

- FiniteStateMachine, implementation of the finite-state machine
- FiniteStateMachineNode, implementation of the finite-state machine that can communicate with the synchronization-server
- FiniteStateMachineNodeStatus, container used for sending the status of a finite-state machine to the synchronization-server
- FiniteStateMachineNodeDerivative, container used for storing finite-state machine data by the synchronization-server
- SynchronizationServer, implementation of the synchronization-server that can communicate with the finite-state machines

### Sequence-diagrams:

Two sequence-diagrams will illustrate:

- How will processes announce their presence to the synchronization-server?
- How will the processes be synchronized by the synchronization-server?

### How will processes announce their presence to the synchronization-server

![alt](/diagrams/sequence_announce.png "Finite-state machine announces their presence to the synchronization-server")

### How will the processes be synchronized by the synchronization-server

![alt](/diagrams/sequence_synchronization.png "Synchronization-server synchronizes finite-state machine")


## Concurrent model

In this paper the goal is not to implement an advanced concurrent model, the aim is to implement FSP based design in Minix, therefore a simple FSP and LTS model is used. 

The aim of this concurrent model is to control a simulated car, the input is read from stdin, the corresponding direction is determined and written to stdout.

### FSP model

THe FSP model is as following:

``` FSP
set Keys = {w, a, s, d}
set Directions = {forward, left, back, right} 

                // Drivers
STDIN_DRIVER = (check_stdin_value -> Keys -> STDIN_DRIVER).
STDOUT_DRIVER = (Directions -> write_stdout -> STDOUT_DRIVER).


                // Thread
CONTROLLER = (w -> forward -> CONTROLLER 
                    | a -> left -> CONTROLLER 
                    | s -> back -> CONTROLLER
                    | d -> right -> CONTROLLER).

||DRIVERS = (STDIN_DRIVER || STDOUT_DRIVER).

||THREADS = (CONTROLLER).

||COMBINED = (DRIVERS || THREADS).

```

#### Explanation

The Explanation for each of the FSP elements:

- STDIN_DRIVER, reads from stdin the values that are withing the Keys set.
- STDOUT_DRIVER, writes values from the Direction set to the stdout.
- CONTROLLER, maps the values from the Keys set to the Directions set.

### LTS Model

The LTS models is as following:

![alt](/diagrams/lts.png)
