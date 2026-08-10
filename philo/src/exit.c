/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mu <mu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:47:12 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/10 11:26:18 by mu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// TODO: update according to new structure
static void	cleanup_table(t_table *table)
{
	t_philo	*curr_p;
	t_philo	*next_p;
	t_philo	*head_p;
	int		start;
	// TODO: table frees order: philo_turn, args
	// TODO: philo_turn frees order: r_chopstick, thread_id, next (REPEAT)
	if (!table)
		return ;
	if (table->philo_turn && *table->philo_turn)
	{
		head_p = *table->philo_turn;
		curr_p = head_p;
		start = 1;
		while (curr_p && (start || curr_p != head_p))
		{
			start = 0;
			next_p = curr_p->next;
			if (curr_p->thread_id)
				pthread_join(curr_p->thread_id, NULL);
			pthread_mutex_destroy(&curr_p->r_chopstick);
			free(curr_p);
			curr_p = next_p;
		}
		free(table->philo_turn);
	}
	if (table->args)
		free(table->args);
	free(table);
	return ;
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
