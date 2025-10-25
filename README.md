# CPU Scheduling Algorithms

A collection of CPU scheduling algorithm implementations in C, demonstrating two fundamental process scheduling techniques used in operating systems.

## Table of Contents
- [Overview](#overview)
- [Algorithms Implemented](#algorithms-implemented)
  - [Shortest Job First (SJF)](#shortest-job-first-sjf)
  - [Round Robin (RR)](#round-robin-rr)
- [Repository Structure](#repository-structure)
- [Input File Format](#input-file-format)
- [Compilation](#compilation)
- [Usage](#usage)
- [Example Output](#example-output)
- [Algorithm Details](#algorithm-details)

## Overview

This repository contains implementations of two classic CPU scheduling algorithms:
1. **Shortest Job First (SJF)** - A non-preemptive scheduling algorithm
2. **Round Robin (RR)** - A preemptive scheduling algorithm with time quantum

Both implementations use a linked list data structure to manage tasks and read input from a file named `schedule.txt`.

## Algorithms Implemented

### Shortest Job First (SJF)

The SJF algorithm selects the process with the smallest burst time for execution. This is a non-preemptive algorithm that minimizes average waiting time.

**Features:**
- Non-preemptive scheduling
- Tasks sorted by burst time
- Optimal for minimizing average waiting time
- Implementation file: `sjf.c`

### Round Robin (RR)

Round Robin is a preemptive scheduling algorithm where each process is assigned a fixed time quantum (10 ms in this implementation). If a process doesn't complete within its quantum, it moves to the end of the queue.

**Features:**
- Preemptive scheduling
- Fixed time quantum of 10 ms
- Fair CPU allocation among all processes
- Implementation file: `round_robin.c`

## Repository Structure

```
cpu-scheduling-algorithms/
├── README.md          # This file
├── sjf.c             # Shortest Job First implementation
├── round_robin.c     # Round Robin implementation
└── schedule.txt      # Input file with task definitions (user-created)
```

## Input File Format

Both programs expect an input file named `schedule.txt` in the same directory. The file should contain one task per line with the following comma-separated format:

```
TaskName, Priority, BurstTime
```

**Format Details:**
- **TaskName**: A string identifier for the task (e.g., T1, T2, ProcessA)
- **Priority**: An integer representing the task's priority (currently informational only)
- **BurstTime**: An integer representing the CPU burst time in milliseconds

**Example `schedule.txt`:**
```
T1, 4, 20
T2, 1, 25
T3, 2, 25
T4, 2, 15
T5, 3, 10
```

## Compilation

To compile the programs, you need a C compiler (e.g., GCC). Use the following commands:

```bash
# Compile Shortest Job First
gcc sjf.c -o sjf

# Compile Round Robin
gcc round_robin.c -o round_robin

# Or compile both at once
gcc sjf.c -o sjf && gcc round_robin.c -o round_robin
```

## Usage

1. **Create the input file** `schedule.txt` in the same directory as the executables with your task definitions.

2. **Run the SJF algorithm:**
   ```bash
   ./sjf
   ```

3. **Run the Round Robin algorithm:**
   ```bash
   ./round_robin
   ```

## Example Output

Using the sample `schedule.txt` file shown above:

### SJF Output:
```
Executing Task: T5, Priority: 3, Burst: 10, Time in processor: 10
Executing Task: T4, Priority: 2, Burst: 15, Time in processor: 15
Executing Task: T1, Priority: 4, Burst: 20, Time in processor: 20
Executing Task: T2, Priority: 1, Burst: 25, Time in processor: 25
Executing Task: T3, Priority: 2, Burst: 25, Time in processor: 25
```

Notice how tasks are executed in order of shortest burst time first (T5: 10ms → T4: 15ms → T1: 20ms → T2: 25ms → T3: 25ms).

### Round Robin Output:
```
Executing Task: T1, Priority: 4, Burst Left: 10, Time in Processor: 10 ms
Executing Task: T2, Priority: 1, Burst Left: 15, Time in Processor: 10 ms
Executing Task: T3, Priority: 2, Burst Left: 15, Time in Processor: 10 ms
Executing Task: T4, Priority: 2, Burst Left: 5, Time in Processor: 10 ms
Executing Task: T5, Priority: 3, Burst Left: 0, Time in Processor: 10 ms
Executing Task: T1, Priority: 4, Burst Left: 0, Time in Processor: 10 ms
Executing Task: T2, Priority: 1, Burst Left: 5, Time in Processor: 10 ms
Executing Task: T3, Priority: 2, Burst Left: 5, Time in Processor: 10 ms
Executing Task: T4, Priority: 2, Burst Left: 0, Time in Processor: 5 ms
Executing Task: T2, Priority: 1, Burst Left: 0, Time in Processor: 5 ms
Executing Task: T3, Priority: 2, Burst Left: 0, Time in Processor: 5 ms
```

Notice how each task gets a time slice of 10ms, and tasks rotate in a circular queue until all are completed.

## Algorithm Details

### Shortest Job First (SJF) Implementation

The SJF implementation maintains tasks in a sorted linked list:
- **insertTask()**: Inserts tasks in ascending order of burst time
- **createTask()**: Allocates memory and initializes task structure
- **readFile()**: Parses the input file and creates task nodes
- **executeTasks()**: Executes tasks sequentially in sorted order

**Time Complexity:** O(n) for insertion, O(n) for execution

### Round Robin Implementation

The Round Robin implementation uses a circular linked list approach:
- **appendTask()**: Adds tasks to the end of the linked list
- **createTask()**: Allocates memory and initializes task structure
- **readFile()**: Parses the input file and creates task nodes
- **executeTasks()**: Executes tasks in rotation with time quantum of 10ms
  - Each task runs for min(remainingBurst, quantum) time
  - Completed tasks are removed from the list
  - Incomplete tasks continue in the next cycle

**Time Quantum:** 10 milliseconds (hardcoded)

**Time Complexity:** O(n × average_burst_time/quantum)

## Notes

- Both programs will exit with an error if `schedule.txt` is not found
- Memory is properly allocated and freed in both implementations
- Task names are limited to 10 characters (including null terminator)
- The priority field is currently read but not used in scheduling decisions

## License

This project is open source and available for educational purposes.