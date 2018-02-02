# Requirements

The Requirements will be discussed using the MoSCoW method.

- Must have:
  - Synchronize server:
    - Synchronize an unknown amount of processes
    - Receive an announcement from a process and from then on   synchronize this process.
  - Processes;
    - Follow from a FSP design
    - Announce their presence to the synchronization-server
    - Be synchronized by the synchronization-server
- Should have:
  - Device-drivers:
    - Device-driver0, read from stdin
    - Device-driver1, write to stdout
  - thread:
    - Control the device-drivers based upon its synchronisable actions