# Research

## How will the communication between a finite-state machine and the synchronization-server take place under Minix

In this sub-question will be discussed how the communication between finite-state machines and synchronization-server will take place under Minix

### What is a finite-state machine status and how will it be communicated with the synchronization-server

In this sub-question will be discussed what a finite-state machine status is and how it will be communicated with the synchronization-server.

#### What is a finite-state machine status and how will it be stored

To determine how a finite-state machine will send its status first needs to be determined what the status of a finite-state machine is.  
The status of a finite-state machine is all the information needed by synchronization-server to determine the next action and send the determined action.

The status will consist of the following finite-state machine attributes:

- Endpoint
- Sensitivity-list
- Alphabet
- Index, this is the index the finite-state machine its corresponding derivative in the list of derivatives held by the synchronization-server.

These attributes are the only attributes the synchronization-server needs to determine the next action.

#### How will a finite-state machine status be communicated with the synchronization-server

The steps of sending a finite-state machine its status are as following:

- Create new finite-state machine status object.
- Copy the attributes mentioned below into the finite-state machine status element.
- Create a memory grant that will share the finite-state machine status with the synchronization server.
- A new message is created containing the memory grant.
- The message containing the memory grant is send to the synchronization-server.

When the finite-state machine status message has been send the synchronization-server will do the following:

- Receive the finite-state machine status.
- Copy the granted memory into a new finite-state machine status object.
- Find the corresponding finite-state machine derivative using the index of the finite-state machine status.
- Copy the attributes from the finite-state machine status into the finite-state machine derivative.

### How will the synchronization-server communicate actions to the finite-state machines

After the synchronization-server determines the next action the finite-state machines will execute this action will be send to the finite-state machines.

The steps of sending the action to the finite-state machines is as following, this assumes the list of finite-state derivatives that will execute the action and the action that will be executed is already determined:

- The list of derivatives that will execute the action is iterated.
- A new message is created containing the to be executed action.
- The message is send using the derivative its endpoint, as this endpoint is equal to the finite-state machine its endpoint that will execute the action.

When a action message has been send the receiving finite-state machine will do the following:

- Receive the action message.
- Make a transition based upon the received action.

After making a finite-state machine makes a transition the finite-state machine will send its status to the synchronization-server and the process starts over.