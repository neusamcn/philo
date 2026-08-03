/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:47:12 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/03 19:35:59 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// TODO: update according to new structure
static void	cleanup_table(t_table *table)
{
	t_philo	*curr_p;
	// TODO: table frees order: head_philos, args
	// TODO: head_philos frees order: r_chopstick, thread_id, next (REPEAT)
	if (table)
	{
		curr_p = table->head_philos;
		while (curr_p)
		{
			pthread_mutex_destroy(&curr_p->r_chopstick);
			pthread_join(curr_p->thread_id, NULL);
			table->head_philos = table->head_philos->next;
			free(curr_p);
			curr_p = table->head_philos;
		}
		if (table->args)
			free(table->args);
		free(table);
	}
}

int	exit_cleanup(t_table *table, char *err_msg, int exit_status)
{
	if (table)
		cleanup_table(table);
	if (err_msg)
		ft_putstr_fd(STDERR_FILENO, err_msg);
	return (exit_status);
}

int	exit_msg(char *out_msg, char *err_msg, t_table *table, int exit_status)
{
	printf(ERR"%s\nSee "CLR_RST, out_msg);
	printf("<project root>/README.md");
	printf(ERR" for instructions.\n"CLR_RST);
	return (exit_cleanup(table, err_msg, exit_status));
}
