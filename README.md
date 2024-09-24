
# Philosopher - Dining Philosophers Problem

## Description

The *Philosopher* project is part of 42 school's curriculum and involves solving the well-known "Dining Philosophers Problem." This project focuses on multi-threading, synchronization, and avoiding deadlocks. The goal is to manage multiple philosophers who alternate between eating, thinking, and sleeping, while ensuring that they don't encounter race conditions or deadlocks when accessing shared resources (forks).

## Project Objectives

- Implement a solution to the Dining Philosophers Problem.
- Learn to manage threads and synchronization in C.
- Understand how to avoid deadlocks and race conditions.
- Gain experience with mutexes and semaphores.

## Problem Overview

The problem involves several philosophers sitting at a circular table. Between each philosopher, there is a fork. A philosopher must pick up two forks (one from the left and one from the right) to eat. The challenge is to manage the philosophers' behavior (thinking, eating, sleeping) while ensuring that no two philosophers pick up the same fork at the same time, avoiding deadlocks and ensuring all philosophers eventually get to eat.

## Features

1. Each philosopher follows this routine:
   - **Thinking**: The philosopher thinks about life.
   - **Eating**: The philosopher picks up two forks and eats.
   - **Sleeping**: After eating, the philosopher sleeps for a while.

2. You must manage forks as shared resources to ensure no two philosophers use the same fork at the same time. Proper synchronization is required.

3. Philosophers need to alternate between their tasks in a way that prevents deadlocks and ensures fairness (i.e., no philosopher starves).

## Implementation Requirements

- Use **threads** to represent philosophers.
- Use **mutexes** or **semaphores** to handle shared resources (forks).
- Ensure that no deadlock occurs, and that all philosophers get a chance to eat.

## System Calls and Functions

Key functions and system calls used:

- `pthread_create()`: Creates a new thread.
- `pthread_join()`: Waits for a thread to terminate.
- `pthread_mutex_init()`: Initializes a mutex.
- `pthread_mutex_lock()`: Locks a mutex (fork).
- `pthread_mutex_unlock()`: Unlocks a mutex (fork).
- `usleep()`: Suspends execution for a given time (used for sleeping or thinking).

## Installation

To compile and run the *Philosopher* project, follow these steps:

```bash
git clone https://github.com/your-repo/philosopher.git
cd philosopher
make
```

Run the program with the following format:

```bash
./philosopher number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

For example:

```bash
./philosopher 5 800 200 200
```

## Usage

- `number_of_philosophers`: The number of philosophers (and forks).
- `time_to_die`: Time (in milliseconds) after which a philosopher dies if they haven’t eaten.
- `time_to_eat`: Time (in milliseconds) it takes for a philosopher to eat.
- `time_to_sleep`: Time (in milliseconds) a philosopher spends sleeping.
- `[number_of_times_each_philosopher_must_eat]`: Optional. If all philosophers have eaten this number of times, the simulation ends.

## Error Handling

The program should handle:

- Invalid arguments.
- Synchronization issues, ensuring no two philosophers hold the same fork simultaneously.
- Philosophers dying if they don't eat within the allowed time.

## Testing

Test different philosopher counts and scenarios to ensure deadlock-free and starvation-free behavior.

```bash
./philosopher 4 410 200 200
```

Check if all philosophers can eat without one starving or the simulation freezing.

## Author

- **Louis** - 42 Lausanne Student
