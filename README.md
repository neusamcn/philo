*This project has been created as part of the 42 curriculum by ncruz-ne.*

## Description

...

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

`EXIT_FAILURE` is also the return status when any error occurs during program execution. Information will be added to **standard error** on the error that triggered the program's exit.

Testing output will be available in the directory defined in `Makefile` as `TEST_DIR`.


## Resources

https://www.man7.org/linux/man-pages/man7/pthreads.7.html