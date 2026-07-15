*This project has been created as part of the 42 curriculum by ncruz-ne.*

## Description

These silly philosophers say that they'll die if they only have 1 fork to eat spaghetti... That seems a bit dramatic... So let's give them chopsticks and noodles instead so they can truly worry about their mortal coil :) [*gleeful witchy cackle*]
i.e. the subject refers to 'forks' and 'spaghetti', we will be talking about 'chopsticks' and 'noodles' here.

...

Our philosophers and chopsticks are listed in arrays in a way that:
```
P = philosopher;
C = chopstick;
N = total number of philosophers and chopsticks;

P[index] can use C[index] and C[index - 1];
Exception: P[0] can use C[0] and C[N - 1];

C[index] can be used by P[index] and P[index + 1].
Exception: C[N - 1] can be used by P[N - 1] and P[0];
```

## Instructions

1. Compile the project with `make` or `make all`.
2. Run the project with `make run` or
	```
	./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
	```
3. Use `make clean` to remove object files.
4. Use `make fclean` to remove all generated files.
5. Use `make re` to rebuild the project from scratch.
6. Testing rules — using `ARGS` in `Makefile`:
	1. `make valg` runs `valgrind`;
	2. `make db` starts debugging session `gdbtui`;
	3. `make test` runs first `valgrind` and after initiates a `gdbtui` session.
7. `make tclean` will remove only testing files and directories.
8. Use `make norm` to download the most updated version of 42 Norm.

Introducing invalid arguments to run the program will cause it to return with `EXIT_FAILURE` and an error message will be printed in **standard ouput** so that the user knows what is the issue.

`philo` will only run successfully if there are **4** or **5** arguments, with all of them being **positive integers** (from `1` to `INT_MAX` = **2147483647** for 32-bit integers), except for `number_of_times_each_philosopher_must_eat` that can be set to `0` — which will mean it will not be considered for the simulation.

When using `make run`, user must update the `ARGS` variable in `Makefile` directly or the individual variables that compose `ARGS`:
```
N_PHILO			= 1
T_DIE			= 800
T_EAT			= 200
T_SLEEP			= 200
N_EATS_X_PHILO	= 0
ARGS			= $(N_PHILO) $(T_DIE) $(T_EAT) $(T_SLEEP) $(N_EATS_X_PHILO)
```

Note that though all positive integer values are valid, the program shouldn't be tested during evaluation with `number_of_philosophers > 200`, `time_to_die < 60`, `time_to_eat < 60` or `time_to_sleep < 60`. A warning message will be displayed in standard output when user submits any parameter under these conditions.

`EXIT_FAILURE` is also the return status when any error occurs during program execution. Information will be added to **standard error** regarding the error that triggered the program's exit.

Testing output will be available in the directory defined in `Makefile` as `TEST_DIR`.


## Resources

### Allowed functions
memset: https://www.man7.org/linux/man-pages/man3/memset.3.html

printf: https://man7.org/linux/man-pages/man3/printf.3.html

malloc, free: https://man7.org/linux/man-pages/man3/malloc.3.html

write: https://man7.org/linux/man-pages/man2/write.2.html

usleep: https://man7.org/linux/man-pages/man3/usleep.3.html

gettimeofday: https://man7.org/linux/man-pages/man3/gettimeofday.3p.html

https://www.man7.org/linux/man-pages/man7/pthreads.7.html
cancellation points and how write() and printf() relate
nice value
NPTL: resource limits, interval timers, alternate signal stack, stack size soft resource limit, RLIMIT_STACK, ulimit -s, getconf GNU_LIBPTHREAD_VERSION, LD_ASSUME_KERNEL

pthread_create: https://www.man7.org/linux/man-pages/man3/pthread_create.3.html

pthread_detach: https://www.man7.org/linux/man-pages/man3/pthread_detach.3.html

pthread_join: https://www.man7.org/linux/man-pages/man3/pthread_join.3.html


### Important concepts

Multithreading in C: https://www.geeksforgeeks.org/c/multithreading-in-c/

Thread Management Functions in C: https://www.geeksforgeeks.org/c/thread-functions-in-c-c/

Inter-Process Communication (IPC): https://www.geeksforgeeks.org/operating-systems/inter-process-communication-ipc/

Introduction to Process Synchronization: https://www.geeksforgeeks.org/operating-systems/introduction-of-process-synchronization/

Mutual Exclusion in Synchronization: https://www.geeksforgeeks.org/operating-systems/mutual-exclusion-in-synchronization/

Priority Inversion in Operating Systems: https://www.geeksforgeeks.org/operating-systems/priority-inversion/

Introduction of Deadlock in Operating System: https://www.geeksforgeeks.org/operating-systems/introduction-of-deadlock-in-operating-system/

Semaphores in Process Synchronization: https://www.geeksforgeeks.org/operating-systems/semaphores-in-process-synchronization/

Mutex vs Semaphore: https://www.geeksforgeeks.org/operating-systems/mutex-vs-semaphore/

Spinlock: https://en.wikipedia.org/wiki/Spinlock


Operations on mutexes:

pthread_mutex_init, pthread_mutex_destroy,
pthread_mutex_lock, pthread_mutex_unlock:
https://www.man7.org/linux/man-pages/man3/pthread_mutex_init.3.html


Gold!: https://diningphilosophers.eu/
The implementation used in this project is the Multiple Token Solution: https://diningphilosophers.eu/token/#:~:text=Global%20Animation-,Multiple%20Token%20Solution,-The%20Global%20Token


Helgrind: a thread error detector: https://valgrind.org/docs/manual/hg-manual.html


TODO: https://pt.wikipedia.org/wiki/Exclus%C3%A3o_m%C3%BAtua
https://stackoverflow.com/questions/34524/what-is-a-mutex


### Interesting rabbit holes I went through while working on this project...

Learning from Wikipedia on a tight schedule is always a gamble... I knew about The Year 2000 Problem, but learning about Epochs opened a whole new can of shiny worms for me. Wanna take your chance? Click here. https://en.wikipedia.org/wiki/Epoch_(computing)

Though related to the main concepts explored during this project, microkernels aren't an essential read. However, this is very interesting and useful to understand. Have a look here to start your journey: Microkernel in Operating Systems: https://www.geeksforgeeks.org/operating-systems/microkernel-in-operating-systems/


### AI Usage

AI (LLMs) was used as a study and research support, to find more information on the various concepts I needed to learn and to assist in interpretation of texts.


Disorganised notes:
monitor threads for deaths
mutex prints can have some delay depending on how usleep is used
will have to calculate microseconds to miliseconds from gettimeofday()

before printing need to lock and unlock

use algorithm that determines how chopsticks are used depending on left or right chopstick

data types: pthread_mutex_t uint64_t
main() is also a thread