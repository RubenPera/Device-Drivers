# Introduction

In year 4 of the study Applied computer science at InHolland University of applied science students will do a project called Realtime & Embedded systems. For this project students will build a realtime system that is based upon an FSP design.

A FSP design means that the system will consist of multiple threads that have the following attributes:

- The current state
- A set of states, Transition-table
- A set of action it can execute, Alphabet
- A set of actions it can execute from the current state, Sensitivity-list

When an action is executed by this thread a state transition occurs. The threads are synchronized based upon their action, synchronization is done by the synchronization-server.

This paper focuses on designing and implementing this system in the programming language C.