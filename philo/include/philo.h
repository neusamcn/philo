/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:57:31 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/11 14:38:10 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// # define _GNU_SOURCE
/* Standard libraries */
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>
// # include <signal.h> // TODO: REMOVE TESTER
# include <pthread.h>
# include <bits/pthreadtypes.h> // TODO: DELETE ?
# include <bits/types/struct_timeval.h> // TODO: DELETE ?
# include <limits.h>
# include <errno.h>

/* My libraries */
# include "flair.h"

/* Enums */
typedef enum e_err
{
	VALID = 0,
	CALLOC_ERR = -1,
	PH_ID_ERR = -2,
	TIME_ERR = -3
}	t_err;

typedef enum s_expo_calls
{
	PRINT_LOG,
	RUN_DISH, // == using token
	END_DINNER
}	t_expo_calls;

/* Structs */
typedef struct s_sim_args
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_eats_x_philo;
}	t_sim_args;

typedef struct s_philo
{
	int				philo_id;
	pthread_t		thread_id;
	bool			alive;
	pthread_mutex_t	*call_server; // will point to the called waiter/server == token
	pthread_mutex_t	*l_chopstick;
	pthread_mutex_t	*r_chopstick;
	// int				t_eat; // needed?
	// int				t_sleep; // needed?
	int64_t			t_last_meal; // ms
	int				meals;
	bool			sated;
	struct s_philo	*previous;
	struct s_philo	*next;
	struct s_table	**table;
	t_err			valid;
}	t_philo;

// TODO: var for p_head and var for p_turn?
// TODO: ADD PHILO_HEAD TO EACH PHILO ?
typedef struct s_table
{
	t_sim_args		*args;
	pthread_mutex_t	*chits; // == available tokens
	pthread_mutex_t	*chopsticks;
	t_philo			**philo_head;
	int64_t			t_dinner_start; // ms
	// int				*philo_turn; // TODO: DELETE ?
	int				meals_x_ph;
	pthread_mutex_t	*expo;
	bool			end_dinner;
	t_err			valid;
}	t_table;

/* Main functions */
t_table	*set_table(t_table *table, char **av);
int		exit_cleanup(t_table *table, char *err_msg, int exit_status);
int		exit_msg(char *out_msg, char *err_msg, t_table *table, int exit_status);
t_table	*init_philo_threads(t_table *tbl);
void	run_philo_sim(t_table *table);

/* Utils */
int		ft_isspace(char c);
int		ft_isdigit(char c);
int		isdigit_str(char *s);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_putchar_fd(int fd, char c);
void	ft_putstr_fd(int fd, char *s);
void	ft_puts_fd(int fd, char *s);

int64_t time_in_ms(void);

// extern volatile sig_atomic_t	g_stop; // TODO: REMOVE TESTER

#endif