*This project has been created as part of the 42 curriculum by ncruz-ne.*

# 42 Lisboa Common Core | Milestone 3: Philosophers

## Description

These silly philosophers say that they'll die if they only have 1 fork to eat spaghetti... That seems a bit dramatic... So let's give them chopsticks and noodles instead so they can truly worry about their mortal coil :) [*gleeful witchy cackle*]
i.e. the subject refers to 'forks' and 'spaghetti', we will be talking about 'chopsticks' and 'noodles' here.

### Setting the room...
One or more philosophers are sitting in a round table, there's a large bowl of noodles in the middle of the tabble, there is only 1 chopstick between each philosopher (meaning that we have as many chopsticks as philosophers).

### What's going to happen?
These philosophers can only do 1 thing at a time and are very specific with their routine:
So each and every philosopher will eat -> sleep -> think -> eat ... This goes on until philosophers are all satisfied or until one of them dies from starvation.

### What's the catch?
It's very impractical to eat with only 1 chopstick, so for a philosopher to be able to eat, they'll need to pick up 2 chopsticks, and the only ones available for a philosopher are the ones to the right and left of each one of them.

If you want a further and more detailed description of the rules, read the subject for this project.

### How did I set up *my* room?
In this simulation, our philosophers are organised in a circular linked list and our chopsticks are listed in an array in a way that:
- For a simulation with `N` philosophers, `Philosopher 1` will be at the head of the linked list, followed by consecutive philosophers and `Philosopher N` will be at the tail.
- For a `Philosopher i` in a simulation with `N` philosophers, its node will have a pointer next that points to `Philosopher i + 1` (with the exception for `Philosopher N`) and a pointer previous that points to `Philosopher i - 1` (with the exception of `Philosopher 1`).
- Considering an array of chopsticks with indexes `0` to `N - 1`, for a `Philosopher i` their left chopstick will have `index i - 1` and their right chopstick will have index `i`. Again we have exceptions for Philosopher 1 and Philosopher N, following the same logic as before: `Philosopher 1` will have their left chopstick in `Chopstick[N - 1]` and `Philosopher N` will have their right chopstick in `Chopstick[0]`.

### How did I work this through?
I considered mainly the [Multiple Token Solution](https://diningphilosophers.eu/token/#:~:text=Multiple%20Token%20Solution) and thought of it as a way to decide who the server in this philosophers' restautant would allow to eat at any given time.


## Instructions

This project can be compiled with the exact requirements or with additional flair. For an improved experience, I recommend the following changes in `flair.h`:
- `FLAIR` to `ON`
- `UTENSIL` to `" chopstick"`

1. Compile the project with `make` or `make all`.
2. Run the project with `make run`, `make print` if you want the simulation log in a file, or
	```
	./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
	```
3. Use `make clean` to remove object files.
4. Use `make fclean` to remove all generated files.
5. Use `make re` to rebuild the project from scratch.
6. Testing rules — using `ARGS` in `Makefile`:
	1. `make valg` runs `valgrind`;
	2. `make hel` runs `helgrind`;
	3. `make db` starts `gdbtui` debugging session;
	4. `make test` runs first `valgrind`, followed by `helgrind` and lastly initiates a `gdbtui` session.
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

Testing output will be available in the directory defined in `Makefile` as `TEST_DIR`, under the filenames set in `VALG_LOG` and `HELG_LOG`.
The simulation log filename can also be defined in `Makefile` under `SIM_LOG`.


## Resources

### Allowed functions
- [memset](https://www.man7.org/linux/man-pages/man3/memset.3.html)
- [printf](https://man7.org/linux/man-pages/man3/printf.3.html)
- [malloc, free](https://man7.org/linux/man-pages/man3/malloc.3.html)
- [write](https://man7.org/linux/man-pages/man2/write.2.html)
- [usleep](https://man7.org/linux/man-pages/man3/usleep.3.html)
- [gettimeofday](https://man7.org/linux/man-pages/man3/gettimeofday.3p.html)
- [pthread_create](https://www.man7.org/linux/man-pages/man3/pthread_create.3.html)
- [pthread_detach](https://www.man7.org/linux/man-pages/man3/pthread_detach.3.html)
- [pthread_join](https://www.man7.org/linux/man-pages/man3/pthread_join.3.html)
- [pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock](https://www.man7.org/linux/man-pages/man3/pthread_mutex_init.3.html)


### Important concepts

- [Multithreading in C](https://www.geeksforgeeks.org/c/multithreading-in-c/)
- [Thread Management Functions in C](https://www.geeksforgeeks.org/c/thread-functions-in-c-c/)
- [Inter-Process Communication (IPC)](https://www.geeksforgeeks.org/operating-systems/inter-process-communication-ipc/)
- [Introduction to Process Synchronization](https://www.geeksforgeeks.org/operating-systems/introduction-of-process-synchronization/)
- [Mutual Exclusion in Synchronization](https://www.geeksforgeeks.org/operating-systems/mutual-exclusion-in-synchronization/)
- [Priority Inversion in Operating Systems](https://www.geeksforgeeks.org/operating-systems/priority-inversion/)
- [Introduction of Deadlock in Operating System](https://www.geeksforgeeks.org/operating-systems/introduction-of-deadlock-in-operating-system/)
- [Semaphores in Process Synchronization](https://www.geeksforgeeks.org/operating-systems/semaphores-in-process-synchronization/)
- [Mutex vs Semaphore](https://www.geeksforgeeks.org/operating-systems/mutex-vs-semaphore/)
- [Spinlock](https://en.wikipedia.org/wiki/Spinlock)


### Additional great resources

- [MVP](https://diningphilosophers.eu/)
- [Helgrind: a thread error detector](https://valgrind.org/docs/manual/hg-manual.html)


### Interesting rabbit holes I went through while working on this project...

Learning from Wikipedia on a tight schedule is always a gamble... I knew about The Year 2000 Problem, but learning about Epochs opened a whole new can of shiny worms for me. Wanna take your chance? [Click here](https://en.wikipedia.org/wiki/Epoch_(computing)).

Though related to the main concepts explored during this project, microkernels aren't an essential read. However, this is very interesting and useful to understand. Have a look here to start your journey: [Microkernel in Operating Systems](https://www.geeksforgeeks.org/operating-systems/microkernel-in-operating-systems/)

Professional kitchen lingo was a fun and useful way to help me organise this project and name my variables:
- [Webstaurant's article: Kitchen Slang Phrases](https://www.webstaurantstore.com/article/511/kitchen-slang-phrases.html?srsltid=AfmBOop-4NBlJYLfwhyFTRSqtXx04c-K_S0arZ36thQ8fB62ycA93oMd)
- [Reddit post @ r/KitchenConfidential by u/MNGrrl: Made a list of slang for new staff, looking for feedback](https://www.reddit.com/r/KitchenConfidential/comments/eytwy6/made_a_list_of_slang_for_new_staff_looking_for/)

If you haven't worked in a kitchen but watched *The Bear*, these terms will be familiar.

Bonus rabbit hole / fun fact (just because this was on my mind a lot for some reason...):
- [Democracy Manifest @ Wikipedia](https://en.wikipedia.org/wiki/Democracy_Manifest)
- [Democracy Manifest @ YouTube](https://youtu.be/PeihcfYft9w?si=xeRVQsNubFrNYeZ3)


### AI Usage

AI (LLMs) was used as a study and research support, to find more information on the various concepts I needed to learn and to assist in interpretation of technical texts.