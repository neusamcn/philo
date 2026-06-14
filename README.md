*This project has been created as part of the 42 curriculum by ncruz-ne.*

## Description

...

## Instructions

1. Compile the project with `make` or `make all`.
2. Run the shell with `make run` or
	```
	./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
	```

3. Use `make clean` to remove object files.
4. Use `make fclean` to remove all generated files.
5. Use `make re` to rebuild the project from scratch.
6. Use `make test` for debugging with `gdb` and `valgrind`.
7. `make tclean` will remove only testing files and directories.

Introducing invalid arguments to run the program will cause it to return with `EXIT_FAILURE` and an error message will be printed in **standard ouput** so that the user knows what is the issue.

`philo` will only run successfully if there are **4** or **5** arguments, with all of them being **positive integers** (from `1` to `INT_MAX` = **2147483647** for 32-bit integers), except for `number_of_times_each_philosopher_must_eat` that can be set to `0`, which will mean it will not be considered for the simulation.

When using `make run`, user must update the `ARGS` variables in `Makefile` directly or the individual variables that compose `ARGS`:
```
N_PHILO			= 1
T_DIE			= 2
T_EAT			= 3
T_SLEEP			= 4
N_EATS_X_PHILO	= 5
ARGS			= $(N_PHILO) $(T_DIE) $(T_EAT) $(T_SLEEP) $(N_EATS_X_PHILO)
```

`EXIT_FAILURE` is also the return status when any error occurs during program execution. Information will be added to **standard error** on the error that triggered the program's exit.

Testing output will be available in the directory defined in `Makefile` as `TEST_DIR`.


## Resources

https://www.man7.org/linux/man-pages/man7/pthreads.7.html