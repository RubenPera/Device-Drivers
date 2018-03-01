
<!-- # Research -->

## How will a synchronization-server be build

In this sub-chapter will be explained how a synchronization-server will be build.

### How will the synchronization-server save the data of the finite-state machines

A synchronization-server will hold the finite-state machine data in a new container, this container will be called finite-state machine derivative, or derivative in short.  
This derivative will contain the necessary information the synchronization-server needs to determine the next action that will be executed by the system.

This information will be:

- Sensitivity-list, the sensitivity-list of the finite-state machine
- Alphabet, the alphabet of the finite-state machine
- Endpoint, the Minix endpoint used for sending messages
- Index, this index of this derivative

This information is enough for the synchronization-server to determine the next action.

These derivatives will be stored in an array, an array is used because when using indexes it has a $O(1)$ lookup time.

### How will the synchronization-server determine the next action for the finite-state machines

For an action to be eligible for execution the following must be true:  
When an action is present in a finite-state machine its alphabet it must also be present in the finite-state machine its sensitivity-list. This is true for every finite-state machine controlled by the synchronization-server.

This means that when one or more finite-state machines have an action in their alphabet but not their sensitivity-list this action cannot be executed.

The following steps will be taken to determine which action can be executed:

- A set will be filled with every action that is currently present in the sensitivity-lists.
- A new set will be filled with every action that cannot be executed.
- The second set, containing the actions that cannot be executed, will be subtracted from the first set.
- The result set will contain only the actions that can currently be executed.
- A random action will be chosen from the remaining set, this will be the action that will be executed.

Now the action that the finite-state machines will execute has been determined.

### How will the synchronization-server determine the finite-state machines that will execute an action

In the previous sub-question the action that will be executed was determined, in this sub-question the finite-state machines that will execute this action will be determined:

- A new set is created, this set will hold the derivatives that will execute the selected action.
- The array of derivatives will be iterated.
- If the sensitivity-list and alphabet of the derivative contains the selected action the derivative can execute the action and is added to the designated set.
- After iterating every element in the array of derivatives the result set contains all derivatives that can execute the action.

Now a set of derivatives that can execute an action have been determined, and because the derivatives represent a finite-state machine, it is also determined which finite-state machines can execute the action.