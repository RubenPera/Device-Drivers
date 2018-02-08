# Research

## How will a finite-state machine be build

In this sub-chapter will be explained how a finite-state machine will be build.

### How will a finite-state machine save its transition-table, sensitivity-list and alphabet

In this section will be explained how a finite-state machine saves its information.

#### How will a finite-state machine save its transition-table

A transition-table stores the information that is needed for a finite-state machine to make transitions, determine if it can execute an action and what the next state will be after executing a certain action from a certain state.

Because the application that will be build in this paper is supposed to be real-time, and therefore execution time is limited, the transition-table will have the following requirements:

- Store the states.
- Store the actions.
- Can be used to determine the next state given the current state and the to be executed action.
- Relative fast lookup time.

This leads to the following design:
The transition-table will consist of a two-dimensional array, where the index of the first array is the current state, and the index of the second array is the to be executed action.  
The result will be in range of -1 to the maximum value of an integer. Is the result -1 then the to be executed action is not a valid action from the current state, any other value is the new state the finite-state machine will be in after executing the action.  
The size of the outer array, the array using state as index, will be the sum of the total amount of states in the fsp.
The size of the inner arrays, the arrays using actions as indexes, will be the sum of the total amount of actions in the fsp.

This design has the following benefits:

- $O (1)$ lookup time, because indexes in arrays are used, this means that the time to determine the next state and if an action can be executed is relative short.
- The sensitivity-list can be quickly derived from the transition-table. TODO: add ref to sensitivity-list

This design has one disadvantage, an amount of data is not used, while still being allocated, and therefore wasted.
In a more advanced language a hash table would have been used, and this disadvantage would not apply.

#### How will a finite-state machine save its sensitivity-list

The sensitivity-list is used to determine if a finite-state machine can execute an action from the current state and contains all the actions that can be executed from the current state the finite-state machine is in.  
The sensitivity-list will be derived from the transition-table.

The sensitivity-list has the following requirements:

- Store the actions that can be executed in the current state.
- Relative fast lookup time.

This leads to the following design:
The sensitivity-list will consist of an one-dimensional array where the index is the to be executed action and the result will determine if the finite-state machine can execute the action.  
The result will be in range of -1 to the maximum value of an integer. Is the result -1 then the to be executed action is not a valid action from the current state, any other value means that the action can be executed.

The design of the sensitivity-list is similar to that of the inner arrays of the transition-table, and has therefore the same advantages and disadvantages as the transition-table.

#### How will a finite-state machine save its alphabet

The alphabet is used to determine if a finite-state machine can ever execute an action and should contain all of the actions that a finite-state machine could ever execute.  
The alphabet will be derived from the transition-table.

The alphabet has the following requirements:

- Store the actions that the finite-state machine is ever capable of executing.
- Relative fast lookup time.

This leads to the following design:
The alphabet will consist of an one-dimensional array where the index is the to be executed action and the result will determine if the finite-state machine can execute the action.  
The result will be in range of -1 to the maximum value of an integer. Is the result -1 then the to be executed action is not a valid action cannot ever be executed, any other value means that the action can be executed.

The design of the alphabet is similar to that of the inner arrays of the transition-table, and has therefore the same advantages and disadvantages as the transition-table.

### How will a finite-state machine determine its sensitivity-list and alphabet

As described above the design of the sensitivity-list and alphabet are similar to the inner arrays of the transaction-table.  
All of them return either an -1, not a viable action, or a value in the range from 0 to the maximum value of an integer, is a viable action, when using an action as index.

#### How will a finite-state machine determine its sensitivity-list

The sensitivity-list is equal to the inner array that is returned when inserting the current state in the outer array of the transition-table.  
This is because when using the current state as the index on the outer array of the transition-table, an array is returned that contains all the actions that can be executed from the current state, and this is the sensitivity-list.

The following steps will be taken to determine the sensitivity-list:

- Copy the inner array that is returned when inserting the current state in the outer array of the transition-table into the sensitivity-list.

#### How will a finite-state machine determine its alphabet

The alphabet contains all the actions that a finite-state machine can execute from any state. Each action in the transition-table must be checked if it can ever be executed, and if so, add it to the alphabet.

The following steps will be taken to determine the alphabet:

- Create an alphabet with all values on False.
- Iterate over every action in the transition-table.
- If an action can be executed set that action in the alphabet on True.

#### How will a finite-state machine make transitions

Making a transition is to execute an action, determine a new sensitivity-list and new current state, and setting the new sensitivity-list and current state.

How a action is executed and the new sensitivity-list is determined is dependent on what kind of finite-state machine is making the transition. There are two different kind of transitions, a Thread transition, and a device-driver transition.

**Thread transition:**  
The new sensitivity-list is a direct consequence of the fsp design.

**Device-driver transition:**  
The new sensitivity-list is either direct consequence of the fsp design or a consequence of the hardware or sensor data the device-driver operates upon.

This leads to the following steps of making a transition:

- Determine if the action can be executed, using the transition-table, current state and to be executed action.
- Executing the action, this will return the new sensitivity-list, this could be either the Thread implementation or the device-driver implementation. An empty sensitivity-list could also be returned indicating that the action could not successfully execute.
- Checking if the new sensitivity-list is not empty, if it is empty not proceed.
- Determine the new state of the finite-state machine using its transition-table, current state and executed action.
- Set the finite-state machine its new state and the new sensitivity-list.