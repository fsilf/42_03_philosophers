# 42 Rank03 Philosophers
Implement the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) with threads and mutexes (madatory part) or with processes and semaphores (bonus part)
## Global rules:
- Global variables are forbidden
- Arguments for the programs:
    + `number_of_philosophers`: number of philosophers/forks
    + `time_to_die`: milliseconds for a philosopher to die (**if he has not started eating**)
        + since the beginning of the last meal of a philosopher, or
        + since the begginnig of the simulation.
    + `time_to_eat`: milliseconds that takes a philosopher to eat. A philosopher will need two forks during this time.
    + `time_to_spleep`: milliseconds that a philosopher spends sleeping.
    + `nummer_of_time_each_philosopher_must_eat` (optional): number of iterations to stop the simulation. If a philosopher eats this number of times the simulation stops.
- Each philosopher has a number (from 1 to `number_of_philosophers`)
- Sitting arrangements:
    + Philosopher number 1 and philosopher number `number_of_philosophers` sit next to each other.
    + For any other philosopher: philosopher number `n` sits between philosopher number `n - 1` and philosopher number `n + 1`
- Philosophers should avoid dying...
- Data races are NOT allowed.
- Shared allowed functions: `memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `pthread_create`, `pthread_detach`, `pthread_join`, `gettimeofday`

## Madatory part
Implement the [dinning philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) with threads and mutexes
- Each philosopher is a thread
- Each fork is shared by two philosophers sitting next to each other (always the philosopher to the right or always the philosopher to the left). If there is only one philosopher there is only one fork (and the philosopher will die).
- The state of each fork must be protected with a mutex to prevent philosophers from duplicating forks. 
- Allowed functions: `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`

## Bonus part
Implement the [dinning philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) with processes and semaphores
- All the forks are shared by all philosophers (they are in the middle of the table).
- The number of available forks is represented by a semaphore(a fork do not have a state in memory)
- Each philosopher should be a process.
- The main process should not be a philosopher.
- Allowed functions: `fork`, `kill`, `exit`, `waitpid`, `sem_open`, `sem_close`, `sem_post`, `sem_wait`, `sem_unlink`.
