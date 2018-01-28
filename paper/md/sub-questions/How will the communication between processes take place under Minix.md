# Research

## How will the communication between processes take place under Minix

In this sub-chapter will be explained how a communication between processes takes place under Minix.

### How can messages be send between processes under Minix

In this sub-question will be explained how messages can be send under Minix.

#### What is an endpoint and how can it be determined under Minix

The following quote from the minix3 wikipedia explains what an endpoint is and why it is used in Minix:

> A endpoint identifies a process uniquely among the operating system. It is composed of the process slot number concatenated with a generation number.  
The reason behind this generation number is that a process slot may be recycled when a process dies, so unrelated processes may sequentially share the same process slot number, which would cause problems when delivering messages to a process which happened to share the same process slot than a unrelated predecessor.

The endpoint of a process can be determined in multiple ways, they are:
| Name | Explanation | Input arguments | Return value |
|------|-------------|-----------------|--------------|
| getpid | Determines the endpoint of the process calling the function | None | Endpoint |
| _pm_findproc | Determines the endpoint of the requested process | Process name, Endpoint(endpoint of process will be inserted into this parameter) | Status |


#### How can messages be send and received under Minix

First will be discussed what types of message sending and receiving Minix supports and then how these can be used.

In Minix there are three basic primitives used to send messages, these are:

| Name | Explanation | Input arguments | Return value |
|------|-------------|-----------------|--------------|
| Send | A message is sent, the sender is blocked until the message is delivered | Receiver endpoint, Message | Status |
| Receive | The process is blocked until a message is delivered to them | Sender endpoint, Message, Status | Status |
| Sendrec | A message is sent, the sender is blocked until it receives a reply from the receiver | Receiver endpoint, Message | Status |

Besides the endpoint of processes there are three special endpoints that can be used for sending and receiving messages:

| Name | Explanation | Usage, there can be more usages than mentioned below as these are examples|
|------|-------------|--------|
| Any | The sender or receiver of the message can be any process | Can be used for broadcasting a message |
| None | The sender or receiver of the message can be no process | This endpoint will not be used and the usage is unknown at the time of writing |
| Self | The sender or receiver of the message is the same process | Can be used to simulate messages that would normally be send from other processes |
