/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:47:12 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/14 20:49:24 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	discard_chopsticks(t_table *tbl, int max_chopsticks)
{
	int	i;

	if (!tbl->chopsticks)
		return ;
	i = 0;
	while (i < max_chopsticks)
		pthread_mutex_destroy(&tbl->chopsticks[i++]);
	free(tbl->chopsticks);
}

static void	clear_pass(t_pass *pass)
{
	int	i;

	if (!pass)
		return ;
	i = 0;
	while (i < pass->max_chits)
		pthread_mutex_destroy(&pass->rail[i++]);
	free(pass->rail);
	pthread_mutex_destroy(&pass->run_dish);
	free(pass);
}

static void	cleanup_table(t_table *table, int max_chopsticks)
{
	t_philo	*curr_p;
	t_philo	*next_p;
	t_philo	*head_p;
	int		start;

	if (table->philo_head)
	{
		if (*table->philo_head)
		{
			head_p = *table->philo_head;
			curr_p = head_p;
			start = 1;
			while (curr_p && (start || curr_p != head_p))
			{
				start = 0;
				next_p = curr_p->next;
				if (curr_p->thread_id)
					pthread_join(curr_p->thread_id, NULL);
				free(curr_p);
				curr_p = next_p;
			}
		}
		free(table->philo_head);
	}
	discard_chopsticks(table, max_chopsticks);
}

static int64_t	clear_sim(t_sim *sim)
{
	int64_t	t_dinner_start;

	t_dinner_start = -1;
	if (sim)
	{
		if (sim->table)
		{
			t_dinner_start = sim->table->t_dinner_start;
			cleanup_table(sim->table, sim->args->n_philo);
			free(sim->table);
		}
		clear_pass(sim->pass);
		if (sim->args)
			free(sim->args);
		pthread_mutex_destroy(&sim->print_log);
		pthread_mutex_destroy(&sim->end_sim);
		free(sim);
	}
	return (t_dinner_start);
}

int	exit_cleanup(t_sim *sim, char *err_msg, int exit_status)
{
	int64_t	t_dinner_start;

	t_dinner_start = clear_sim(sim);
	if (err_msg)
		ft_putstr_fd(STDERR_FILENO, err_msg);
	if (FLAIR == ON)
	{
		if (t_dinner_start != -1)
			printf("%" PRId64 " ", time_in_ms() - t_dinner_start);
		printf("Dinner simulation ended.\n");
	}
	return (exit_status);
}
