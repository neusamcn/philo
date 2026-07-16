/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:57:31 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/07/16 23:52:08 by ncruz-ne         ###   ########.fr       */
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

typedef struct s_philo
{
	int				index;
	pthread_t		thread_id;
	pthread_mutex_t	chopstick;
	int				meals;
	t_philo			*previous;
	t_philo			*next;
	int				valid;
}	t_philo;

typedef struct s_table
{
	t_philo_args	*args;
	int				tokens;
	t_philo			*head_philos;
	int				meals_x_ph;
	int				valid;
}	t_table;

/* Enums */
typedef enum e_pt_valid
{
	VALID = 0,
	CALLOC_ERR = -1
}	t_pt_valid;

/* Main functions */
t_table	*set_table(t_table *table, char **av);
t_philo	*init_philo(t_philo *philo, char **av);
int		exit_cleanup(t_table *table, char *err_msg, int exit_status);
int		exit_msg(char *out_msg, char *err_msg, t_philo *philo, int exit_status);
void	run_philo_sim(t_philo *philo);

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