/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 11:23:27 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/14 14:40:21 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	dinner_is_over(t_table *tbl)
{
	bool	end_dinner;

	pthread_mutex_lock(&tbl->sim->end_sim);
	end_dinner = tbl->end_dinner;
	pthread_mutex_unlock(&tbl->sim->end_sim);
	return (end_dinner);
}

static bool	philo_dead(t_sim *sim)
{
	t_philo	*curr_p;
	int		start;
	int64_t	t_since_last_meal;

	curr_p = *sim->table->philo_head;
	start = 1;
	while (curr_p && (start || curr_p != *sim->table->philo_head))
	{
		start = 0;
		t_since_last_meal = time_in_ms() - curr_p->t_last_meal;
		if (t_since_last_meal >= sim->args->t_die)
		{
			state_log(curr_p, "died", "");
			update_end_dinner_status(sim->table, true);
			return (true);
		}
		curr_p = curr_p->next;
	}
	return (false);
}

void	update_end_dinner_status(t_table *tbl, bool new_status)
{
	pthread_mutex_lock(&tbl->sim->end_sim);
	tbl->end_dinner = new_status;
	pthread_mutex_unlock(&tbl->sim->end_sim);
}

static bool	philos_sated(t_sim *sim)
{
	t_philo	*curr_p;
	int		start;

	if (sim->args->n_eats_x_philo == 0)
		return (false);
	curr_p = *sim->table->philo_head;
	start = 1;
	while (curr_p && (start || curr_p != *sim->table->philo_head))
	{
		start = 0;
		if (curr_p->meals < sim->args->n_eats_x_philo)
			return (false);
		curr_p = curr_p->next;
	}
	update_end_dinner_status(sim->table, true);
	return (true);
}

void	monitor_dinner(t_sim *sim)
{
	bool	dinner_ended;

	dinner_ended = false;
	while (dinner_ended == false)
	{
		pthread_mutex_lock(&sim->pass->run_dish);
		if (philo_dead(sim) == true || philos_sated(sim) == true)
			dinner_ended = true;
		pthread_mutex_unlock(&sim->pass->run_dish);
		usleep(1);
	}
}
