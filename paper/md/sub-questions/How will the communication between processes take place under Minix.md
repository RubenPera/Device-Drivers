<!-- # Research -->

## How will the communication between processes take place under Minix

In this sub-chapter will be explained how a communication between processes takes place under Minix.

### What are messages and how can they be used to communicate between processes under Minix

In this sub-question will be explained what messages are and how they can be send and received under Minix.

#### What are messages in Minix

Minix uses their own message type as payload for sending and receiving messages. A message are a fixed length of 64 bytes of data, they are composed of:

- Name ; Explanation
- Endpoint sender ; 4-byte identifier of who sent the message
- Message type ; 4-byte message type identifier
- Payload ; 56 bytes of data 

To give further explanation about the message type, each message type has a different structure of its data.

#### What is an endpoint and how can it be determined under Minix

The following quote from the minix3 wikipedia explains what an endpoint is and why it is used in Minix:

> A endpoint identifies a process uniquely among the operating system. It is composed of the process slot number concatenated with a generation number.  
The reason behind this generation number is that a process slot may be recycled when a process dies, so unrelated processes may sequentially share the same process slot number, which would cause problems when delivering messages to a process which happened to share the same process slot than a unrelated predecessor.

//TODO add reference

The endpoint of a process can be determined in multiple ways, they are:

- Name ; Explanation ; Input arguments ; Return value
- getpid ; Determines the endpoint of the process calling the function ; None ; Endpoint l
- _pm_findproc ; Determines the endpoint of the requested process ; Process name, Endpoint (endpoint of process will be inserted into this parameter) ; Status ;

Besides process specific endpoints there are three special endpoints:

- Name ; Explanation ; Usage, there can be more usages than mentioned below as these are examples
- Any ; The sender or receiver of the message can be any process ; Can be used for broadcasting a message
- None ; The sender or receiver of the message can be no process ; This endpoint will not be used and the usage is unknown to the writer at the time of writing
- Self ; The sender or receiver of the message is the same process ; Can be used to simulate messages that would normally be send from other processes

#### How can messages be send and received under Minix

First will be discussed what types of message sending and receiving Minix supports and then how these can be used.

In Minix there are three basic primitives used to send messages, these are:

- Name ; Explanation ; Input arguments ; Return value
- Send ; A message is sent, the sender is blocked until the message is delivered ; Receiver endpoint, Message ; Status ;
- Receive ; The process is blocked until a message is delivered to them ; Sender endpoint, Message, Status ; Status ;
- Sendrec ; A message is sent, the sender is blocked until it receives a reply from the receiver ; Receiver endpoint, Message ; Status ;

### How can memory be shared between processes under Minix

In this sub-question will be discusses how data can be communicated between processes using memory grants under Minix.

#### What is a memory grant under Minix

Memory grants allow processes to share large amount of data, data that would be inefficient to send with messages as messages only allow a 56 byte payload.

Every type of memory grant share the same three attributes:

- Permitted access mode may be set to read, write or read-write
- Grants are created by an endpoint for an endpoint
- The memory region is a continuous range with byte granularity

The granter is the process that created and owns the grant whereas the grantee is the process to which the memory grant was granted.

Minix supports three types of memory grants:

- Name ; Explanation
- Direct grants ; A memory region of the granter is accessible by the grantee. The data is not transferred from the granter to the grantee, the data is only accessible to the grantee and the granter is still the owner of the data. This grant is direct because there is no middleman
- Indirect grants ; Indirect grants are grants that have been transferred by a grantee : the grantee delegates its grant to another process. The grantee becomes a granter and then passes a newly created memory grant credential to the new grantee. The memory grant thus forms a linked list of indirect grants, with a direct grant at the start. Indirect grant can themselves be transferred to another grantee by creating a new indirect grant.
- Magic grants ; Magic grants are grants that are made by one process for memory in another process. The only service that may create magic grants, is VFS. VFS uses magic grants to give other services, direct access to memory in user application processes.

In this paper only the direct grants will be used.

#### How can memory grants be used to share data under Minix

As only direct grants will be used in this paper only this type of memory granting will be further discussed.

In Minix two main function will be used to share data using memory grants:

- Name ; Explanation ; Input arguments ; Return value
- cpf_setgrant_direct ; Grants memory to a specific endpoint and returns the grant id ; Endpoint grantee, Memory address of data to grant, Memory size in bytes, Access type ; Grant id
- sys_safecopyfrom ; Copies granted memory from a specific endpoint to a memory address ; Endpoint granter, Grant id, Grant offset, Memory address to copy data into, Memory size in bytes, Segment ; Status

The Access type specifies what kind of access the grantee has over the memory, either read, write or map.

These two functions combined with sending and receiving messages allow for sharing data between processes under Minix.