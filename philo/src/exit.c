/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:47:12 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/07/14 00:08:56 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	cleanup_philo(t_philo *philo)
{
	int	i;

	if (philo->args)
	{
		if (philo->pt_ids)
		{
			if (philo->valid == VALID)
			{
				i = 0;
				while (i < philo->args->n_philo)
					pthread_join(philo->pt_ids[i++], NULL);
			}
			free(philo->pt_ids);
		}
		if (philo->chopsticks)
		{
			i = 0;
			while (i < philo->args->n_philo)
				pthread_mutex_destroy(&philo->chopsticks[i++]);
			free(philo->chopsticks);
		}
		free(philo->args);
	}
	free(philo);
}

int	exit_cleanup(t_philo *philo, char *err_msg, int exit_status)
{
	if (philo)
		cleanup_philo(philo);
	if (err_msg)
		ft_putstr_fd(STDERR_FILENO, err_msg);
	return (exit_status);
}

int	exit_msg(char *out_msg, char *err_msg, t_philo *philo, int exit_status)
{
	printf(ERR"%s\nSee "COLOR_RESET, out_msg);
	printf("<project root>/README.md");
	printf(ERR" for instructions.\n"COLOR_RESET);
	return (exit_cleanup(philo, err_msg, exit_status));
}
