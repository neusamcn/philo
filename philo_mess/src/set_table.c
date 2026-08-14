/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 23:03:03 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/14 14:01:23 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static t_philo	*arrange_seats(t_philo *p, t_philo *prev, t_sim *sim)
{
	p->previous = prev;
	p->next = NULL;
	if (prev)
		prev->next = p;
	else
		*sim->table->philo_head = p;
	p->valid = VALID;
	prev = p;
	return (prev);
}

static void	sit_philo(t_philo *p, int i, t_sim *sim)
{
	int	n_philo;

	n_philo = sim->args->n_philo;
	p->philo_id = i + 1;
	p->alive = true;
	p->call_server = &sim->pass->server;
	p->l_chopstick = &sim->table->chopsticks[i];
	p->r_chopstick = &sim->table->chopsticks[(i + 1) % n_philo];
	p->t_last_meal = sim->table->t_dinner_start;
	p->meals = 0;
	p->table = &sim->table;
}

static int	sit_philos(t_sim *sim)
{
	int		i;
	int		n_philo;
	t_philo	*p;
	t_philo	*prev;

	i = 0;
	n_philo = sim->args->n_philo;
	*sim->table->philo_head = NULL;
	prev = NULL;
	while (i < n_philo)
	{
		p = ft_calloc(1, sizeof(t_philo));
		if (!p)
			return (CALLOC_ERR);
		sit_philo(p, i, sim);
		prev = arrange_seats(p, prev, sim);
		i++;
	}
	if (prev && *sim->table->philo_head)
	{
		prev->next = *sim->table->philo_head;
		(*sim->table->philo_head)->previous = prev;
	}
	return (VALID);
}

static int	place_chopsticks(t_sim *sim)
{
	int	max_chopsticks;
	int	i;

	max_chopsticks = sim->args->n_philo;
	sim->table->chopsticks = ft_calloc(max_chopsticks, sizeof(pthread_mutex_t));
	if (!sim->table->chopsticks)
		return (CALLOC_ERR);
	i = 0;
	while (i < max_chopsticks)
	{
		pthread_mutex_init(&sim->table->chopsticks[i], NULL);
		i++;
	}
	return (VALID);
}

t_err	set_table(t_sim *sim)
{
	sim->table = ft_calloc(1, sizeof(t_table));
	if (!sim->table)
		return (CALLOC_ERR);
	sim->table->valid = place_chopsticks(sim);
	if (sim->table->valid != VALID)
		return (sim->table->valid);
	sim->table->t_dinner_start = time_in_ms();
	if (sim->table->t_dinner_start == TIME_ERR)
		return (sim->table->t_dinner_start);
	sim->table->end_dinner = false;
	sim->table->philo_head = ft_calloc(1, sizeof(t_philo *));
	if (!sim->table->philo_head)
		return (CALLOC_ERR);
	sim->table->sim = sim;
	sim->table->valid = sit_philos(sim);
	return (sim->table->valid);
}
