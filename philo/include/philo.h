/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:57:31 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/10 16:57:24 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// # define _GNU_SOURCE
/* Standard libraries */
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <errno.h>

/* My libraries */
# include "flair.h"

/* Structs */
typedef struct s_philo_args
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_eats_x_philo;
}	t_philo_args;

// TODO: add int doa, doa = 1 => alive and doa = 0 => dead ?
// and state full, full = 1 => yes, full = 0 => No ?
typedef struct s_philo
{
	int				philo_id;
	pthread_t		thread_id;
	int				alive;
	pthread_mutex_t	r_chopstick;
	int				has_tkn;
	int				t_eat;
	int				t_sleep;
	int				meals;
	struct s_philo	*previous;
	struct s_philo	*next;
	int				valid;
}	t_philo;

// TODO: var for p_head and var for p_turn?
typedef struct s_table
{
	t_philo_args	*args;
	pthread_mutex_t	*tokens;
	t_philo			**philo_head;
	int				*philo_turn;
	int				meals_x_ph;
	int				valid;
}	t_table;

/* Enums */
typedef enum e_valid
{
	VALID = 0,
	CALLOC_ERR = -1,
	PH_ID_ERR = -2
}	t_valid;

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

#endif