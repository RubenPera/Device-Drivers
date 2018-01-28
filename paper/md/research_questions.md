# Research Questions

In this chapter the research questions and the underlying sub-questions will defined.

## Research question

This paper has as aim to design and implement a generic synchronization server. This leads to the following research question:

- How can a synchronization server be build that synchronizes an unbeknownst number of threads, where every thread is based on a design.

## Sub-questions

This research question is divided into sub-questions:

- How will the communication between processes take place under Minix?
  - How can messages be send between processes under Minix?
    - What is an endpoint?
    - How can messages be send?
    - How can messages be received?
  - How can memory be shared between processes under Minix?

- How will a finite-state machine be build?
  - How will a finite-state machine save its transition-table, sensitivity-list and alphabet?
    - How will a finite-state machine save its transition-table?
    - How will a finite-state machine save its sensitivity-list?
    - How will a finite-state machine save its alphabet?
  - How will a finite-state machine determine its sensitivity-list and alphabet?
    - How will a finite-state machine determine its sensitivity-list?
    - How will a finite-state machine determine its alphabet?
  - How will a finite-state machine make transitions?

- How will a synchronization-server be build?
  - How will the synchronization-server save the data of the finite-state machines?
  - How will the synchronization-server determine the next action for the finite-state machines?
  - How will the synchronization-server determine the finite-state machines that will execute an action?

- How will the communication between a finite-state machine and the synchronization-server take place?
  - How will a finite-state machine send their status to the synchronization-server?
  - How will the synchronization-server send an action to a finite-state machine?

- How will the functionalities of the device-drivers be implemented?
  - How can the functionality of device-driver0 be implemented?
  - How can the functionality of device-driver1 be implemented?