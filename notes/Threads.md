# Threads

A **thread** is a single path of execution inside a process.

A process can have one or multiple threads that can execute tasks concurrently.

## Process vs Thread

```text
                    PROCESS
              ┌─────────────────┐
              │   Shared Memory │
              │   Code / Heap   │
              │   Files / Data  │
              │                 │
              │ ┌─────────────┐ │
              │ │   Thread 1  │ │
              │ ├─────────────┤ │
              │ │   Thread 2  │ │
              │ ├─────────────┤ │
              │ │   Thread 3  │ │
              │ └─────────────┘ │
              └─────────────────┘
```

Threads inside the same process **share resources**, but each thread has its own:

- Stack
- Registers
- Execution state

## Why Use Threads?

Threads allow a program to handle multiple tasks concurrently.

### Without Threads

```text
Client A → Handle A → Finish
                       ↓
Client B → Handle B → Finish
                       ↓
Client C → Handle C → Finish
```

### With Threads

```text
                    Server
                      │
          ┌───────────┼───────────┐
          ↓           ↓           ↓
       Thread 1    Thread 2    Thread 3
          ↓           ↓           ↓
       Client A    Client B    Client C
```

This is especially useful for servers, where many clients may need to be handled at the same time.

## Concurrency vs Parallelism

**Concurrency** means multiple tasks are in progress and the system can switch between them.

```text
Time →
Thread A ███     ███
Thread B    ███     ███
Thread C       ███
```

**Parallelism** means multiple tasks actually execute at the same time on different CPU cores.

```text
CPU Core 1 → Thread A
CPU Core 2 → Thread B
CPU Core 3 → Thread C
```

## Shared Memory

Threads within a process can access the same memory.

```text
             PROCESS
        ┌─────────────────┐
        │  Shared Memory  │
        │                 │
        │  Global Data    │
        │  Heap           │
        │  Files/Sockets  │
        ├─────────────────┤
        │ Thread 1 Stack  │
        │ Thread 2 Stack  │
        │ Thread 3 Stack  │
        └─────────────────┘
```

Sharing memory makes communication between threads easy, but it can also cause problems.

## Race Condition

A **race condition** happens when multiple threads access shared data at the same time and the final result depends on the order of execution.

```text
          Shared counter = 0
                 │
        ┌────────┴────────┐
        ↓                 ↓
    Thread 1          Thread 2
        │                 │
     Read 0            Read 0
        │                 │
     Add 1             Add 1
        │                 │
     Write 1           Write 1
        └────────┬────────┘
                 ↓
            counter = 1 ❌
```

We expected `2`, but both threads read the old value `0`.

## Synchronization

**Synchronization** controls how threads access shared resources.

A common mechanism is a **mutex**.

```text
             Shared Resource
                   │
             ┌─────┴─────┐
             │   Mutex   │
             └─────┬─────┘
                   │
          ┌────────┴────────┐
          ↓                 ↓
       Thread 1          Thread 2
       Access            Wait
       Resource             │
          │                 │
       Release              │
          └────────────────→┘
```

Only one thread can access the protected critical section at a time.

## Threads in a Server

A multithreaded server can create a thread to handle each client.

```text
                     Server
                       │
                    accept()
                       │
          ┌────────────┼────────────┐
          ↓            ↓            ↓
       Client A     Client B     Client C
          │            │            │
       Thread 1      Thread 2      Thread 3
          │            │            │
       Request       Request       Request
          │            │            │
       Response      Response      Response
```

This allows the server to handle multiple clients concurrently.

## Important Concepts

```text
Thread
  ↓
Concurrency
  ↓
Shared Memory
  ↓
Race Conditions
  ↓
Synchronization
  ↓
Mutex / Semaphore / Condition Variable
  ↓
Deadlock / Thread Safety
```

## In Short

> **A thread is an execution unit inside a process that allows multiple tasks to run concurrently while sharing the process's resources.**
