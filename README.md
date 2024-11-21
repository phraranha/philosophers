# Dijkstra's Dining Philosophers Problem

This project is an implementation of the Dining Philosophers problem using multithreading in C, which simulates philosophers sitting at a table, thinking, eating, and sleeping, while managing limited resources (forks) to avoid deadlock. 

## Table of Contents
- [Overview](#overview)
- [Setup](#setup)
- [Usage](#usage)
- [Code Structure](#code-structure)
- [Key Functions](#key-functions)
- [Compilation and Execution](#compilation-and-execution)
- [Error Handling](#error-handling)
- [License](#license)

## Overview
The Dining Philosophers problem is a classic concurrency problem that illustrates challenges in resource allocation and synchronization. In this simulation:
- Philosophers alternate between thinking, eating, and sleeping.
- Each philosopher needs two forks to eat, but there is only one fork between each pair of philosophers.
- The solution aims to prevent deadlock (where philosophers indefinitely wait for each other) and starvation (where a philosopher never gets to eat).

## Setup
This project requires a POSIX-compliant system with `pthread` support, as it uses the `pthread` library for thread management and mutexes for synchronization.

## Usage
Run the program with the following command-line arguments:
```
./philo <num_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [num_times_each_philosopher_must_eat]
```
- `num_philosophers`: Number of philosophers (and forks).
- `time_to_die`: Maximum time (in milliseconds) a philosopher can survive without eating.
- `time_to_eat`: Time (in milliseconds) a philosopher takes to eat.
- `time_to_sleep`: Time (in milliseconds) a philosopher takes to sleep.
- `[num_times_each_philosopher_must_eat]`: Optional argument to specify the number of times each philosopher must eat before stopping the simulation.

## Code Structure
The main components of this implementation are:
- **`philo.h`**: Contains the structure definitions and constants.
- **`philo.c`**: Implements the simulation logic, handling initialization, thread creation, and synchronization.
- **Additional helper functions** are implemented for timing, printing, error handling, and argument validation.

## Key Functions
- **`eating()`**: Manages the eating phase, where a philosopher picks up forks, eats, and updates their last meal time.
- **`sleeping()`**: Manages the sleeping phase by calling `precise_usleep`.
- **`thinking()`**: Handles the thinking phase and adjusts thinking duration based on other parameters.
- **`print_status()`**: Prints the current status of each philosopher (thinking, eating, sleeping, or dead).
- **`create_threads()`**: Creates philosopher threads and the overseer thread.
- **`overseer()`**: Monitors each philosopher's status, checking if they are dead or have met the required number of meals.

## Compilation and Execution
1. Compile the program:
   ```bash
   gcc -pthread -o philo philo.c
   ```
2. Run the executable with appropriate arguments:
   ```bash
   ./philo <num_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [num_times_each_philosopher_must_eat]
   ```
3. Example:
   ```bash
   ./philo 5 800 200 200 3
   ```

## Error Handling
The program includes error handling for incorrect arguments:
- If an argument is invalid, an error message is printed, and the program exits.
- Invalid values include non-numeric input, or values outside expected ranges.

Error messages include:
- "Error: Invalid number of philosophers"
- "Error: Invalid time to die"
- "Error: Invalid time to eat"
- "Error: Invalid time to sleep"
- "Error: Invalid number of meals"

## License
This project is open-source under the MIT License. You are free to use, modify, and distribute this code.
