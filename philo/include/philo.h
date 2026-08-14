/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:57:31 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/14 16:03:47 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// # define _GNU_SOURCE // TODO: keep?
/* Standard libraries */
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>
// # include <bits/pthreadtypes.h> // TODO: DELETE ?
// # include <bits/types/struct_timeval.h> // TODO: DELETE ?
# include <limits.h>
# include <errno.h>
# include <inttypes.h>

/* My libraries */
# include "flair.h"

/* Enums */
typedef enum e_err
{
	VALID = 0,
	ARGS_ERR = -1,
	CALLOC_ERR = -2,
	PH_ID_ERR = -3,
	TIME_ERR = -4
}	t_err;

/* Structs */
typedef struct s_sim	t_sim;
typedef struct s_sim_args	t_sim_args;
typedef struct s_pass	t_pass;
typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

typedef struct s_sim
{
	t_sim_args		*args;
	t_pass			*pass;
	t_table			*table;
	pthread_mutex_t	print_log;
	pthread_mutex_t	end_sim;
	t_err			valid;
}	t_sim;

typedef struct s_sim_args
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_eats_x_philo;
}	t_sim_args;

typedef struct s_pass
{
	int				max_chits;
	pthread_mutex_t	*rail;
	pthread_mutex_t	run_dish;
	t_err			valid;
}	t_pass;

typedef struct s_table
{
	pthread_mutex_t	*chopsticks;
	t_philo			**philo_head;
	int64_t			t_dinner_start;
	bool			end_dinner;
	t_sim			*sim;
	t_err			valid;
}	t_table;

typedef struct s_philo
{
	int				philo_id;
	pthread_t		thread_id;
	bool			alive;
	pthread_mutex_t	*call_server;
	pthread_mutex_t	*l_chopstick;
	pthread_mutex_t	*r_chopstick;
	int64_t			t_last_meal;
	int				meals;
	t_philo			*previous;
	t_philo			*next;
	t_table			**table;
	t_err			valid;
}	t_philo;

/* Main simulation functions */
t_err	set_table(t_sim *sim);
int		exit_cleanup(t_sim *sim, char *err_msg, int exit_status);
void	state_log(t_philo *p, char *state, char *utensil);
t_err	start_dinner(t_sim *sim);
void	*dinner(void *arg);
bool	wait_for_server(t_philo *p);
void	serve_next_ph(t_philo *p);
void	monitor_dinner(t_sim *sim);
bool	dinner_is_over(t_table *tbl);
void	update_end_dinner_status(t_table *tbl, bool new_status);

/* Utils */
int		ft_isspace(char c);
int		ft_isdigit(char c);
int		isdigit_str(char *s);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_putchar_fd(int fd, char c);
void	ft_putstr_fd(int fd, char *s);
int64_t time_in_ms(void);
void    usleep_precise(int64_t t_ms, t_table *tbl);

/* Flair */
void	print_philos(t_sim_args *sim_args);
int		exit_msg(char *out_msg, char *err_msg, t_sim *sim, int exit_status);

#endif