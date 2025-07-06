# Philosophers

## 📌 Overview

This project solves a version of [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

The problem involves philosophers sitting around a table, alternating between eating, sleeping, and thinking. Each philosopher has one fork, meaning forks are shared between adjacent philosophers. To eat, a philosopher needs two forks (left and right). If a philosopher doesn't eat within the time limit, they die.

This project introduces multithreading and mutexes. Each philosopher runs on a separate thread, and mutexes prevent race conditions when accessing shared forks.

<img src="imgs/philo.png" width="60%">

## 🌟 Rules for simulation

- There are as many fork on the table as philosophers
- Philosophers don't communicate with each other
- In order to eat philosopher must pick both forks from left and right
- Philosophers take turns eating, sleeping and thinking in that order
- Philosophers must avoid dying
- Simulation ends if
	- All philosophers have eaten at least required amount of times
	- One philosopher dies from starvation

## ▶️ How to run

### Compilation
```bash
git clone https://github.com/vallucodes/philosophers.git
cd philosophers
make
```
### Run examples
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]

./philo 4 800 200 200 6

./philo 3 500 200 100
0 2 has taken a fork
0 2 has taken a fork
0 2 is eating
0 3 is thinking
0 1 is thinking
110 3 has taken a fork
200 2 is sleeping
200 3 has taken a fork
200 3 is eating
200 1 has taken a fork
300 2 is thinking
400 3 is sleeping
400 1 has taken a fork
400 1 is eating
500 2 died
```

## 🛠️ Technical Implementation

| Component | Details |
|-----|----------|
| Thread Management | `pthread_create()` for philosopher threads and observer thread |
| Mutex System | Individual fork mutexes plus specialized locks: `msg_lock`, `death_lock`, `meal_lock`, `start_lock` |
| Fork Management | Array of mutexes representing forks with deadlock prevention ordering |
| Timing System | `gettimeofday()` for precise timestamp tracking and death time calculation |
| Death Monitoring | Separate monitor thread checking philosopher time passed since last meal and how many meals are eaten |
| Resource Allocation | Dynamic memory allocation for `philos` array and `forks` array using `malloc()` |
| Global Data Management | `t_global_data` structure centralizing simulation parameters and shared resources |
| Simulation Control | Simulation start flag and stop flag. Mandatory initial routine to avoid unnecessary race to forks |
| Synchronization | Multiple mutex locks preventing race conditions in messaging, death detection, and meal counting |
| Error Handling | Comprehensive error checking for thread creation, mutex creation and usage, and memory allocation. Termination in case of error in creation |

