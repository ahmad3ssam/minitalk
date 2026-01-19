# minitalk

## Description

Minitalk is a small inter-process communication (IPC) project that show how two independent processes can exchange data using POSIX signals only.

The project consists of two programs:

- Server: prints its PID and waits for incoming signals and reconstructs characters bit by bit.

- Client: sends a string to the server by encoding each character into binary and transmitting it using UNIX signals.

The main goal of this project is to:

- Understand how signals (SIGUSR1, SIGUSR2) work at a low level
- Learn how to transmit data bit by bit between processes

No shared memory, pipes, sockets, or files are allowed—signals only
  
---
## Instructions

We will compile server.c & client.c 
```bash 
make
```
Execution

1. run the server
```bash
./server
```

the output of this operation 
```bash
Server PID XXXX
```

2. run the client
```bash
./client XXXX message
```

We check if the PID exists and if we are allowed to send signals to that process.

---
How It Works

- Each character is encoded into 8 bits

- Signals are sent one bit at a time
  - SIGUSR1 → bit 1
  - SIGUSR2 → bit 0

- The server rebuilds characters after receiving 8 signals

- signal is used to handle signals safely and reliably

---
## Resources

- Signals Overview  *https://man7.org/linux/man-pages/man7/signal.7.html*
- kill() system call *https://man7.org/linux/man-pages/man2/kill.2.html*
- Process IDs (getpid) *https://man7.org/linux/man-pages/man2/getpid.2.html*
---
AI tools were used strictly for:
  - Explaining how POSIX signals work
  - Understanding sigaction, signal masks, and handlers
  - Debugging logic related to bit shifting and synchronization




