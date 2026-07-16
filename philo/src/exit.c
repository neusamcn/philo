/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:47:12 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/07/16 23:55:18 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// TODO: update according to new structure
static void	cleanup_table(t_table *table)
{
	int	i;

	if (table->args)
	{
		if (table->pt_ids)
		{
			if (table->valid == VALID)
			{
				i = 0;
				while (i < table->args->n_philo)
					pthread_join(table->pt_ids[i++], NULL);
			}
			free(table->pt_ids);
		}
		if (table->chopsticks)
		{
			i = 0;
			while (i < table->args->n_philo)
				pthread_mutex_destroy(&table->chopsticks[i++]);
			free(table->chopsticks);
		}
		free(table->args);
	}
	free(table);
}

int	exit_cleanup(t_table *table, char *err_msg, int exit_status)
{
	if (table)
		cleanup_table(table);
	if (err_msg)
		ft_putstr_fd(STDERR_FILENO, err_msg);
	return (exit_status);
}

int	exit_msg(char *out_msg, char *err_msg, t_philo *philo, int exit_status)
{
	printf(ERR"%s\nSee "CLR_RST, out_msg);
	printf("<project root>/README.md");
	printf(ERR" for instructions.\n"CLR_RST);
	return (exit_cleanup(philo, err_msg, exit_status));
}
