/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mu <mu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:41:17 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/10 11:30:17 by mu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	state_log(int p_idx, char *state)
{
	// TODO: calc timestamp in ms
	printf("timestamp_in_ms %d %s\n", p_idx + 1, state);
}

static int	update_meals_x_ph(t_table *tbl)
{
	t_philo	*p_curr;
	int		p_start_id;
	int		tot_meals;

	p_curr = *tbl->philo_turn;
	p_start_id = p_curr->philo_id;
	tot_meals = p_curr->meals;
	while (p_curr->philo_id != p_start_id + 1)
	{
		if (p_curr->meals != tot_meals)
			break ;
		p_curr = p_curr->next;
	}
	if (p_curr->philo_id == p_start_id)
		tbl->meals_x_ph = tot_meals;
	else
		return (PH_ID_ERR);
	return (VALID);
}

// TODO: update according to new structure
static void	eat(t_table *tbl)
{
	t_philo	*p;

	p = *tbl->philo_turn;
	if (tbl->tokens > 0)
	{
		if (p->has_tkn == 0)
			p->has_tkn = 1;
		tbl->tokens--;
		pthread_mutex_lock(&p->r_chopstick);
		pthread_mutex_lock(&p->previous->r_chopstick);
		state_log(p->philo_id, "is sleeping");
		usleep(tbl->args->t_eat * 1000);
		pthread_mutex_unlock(&p->r_chopstick);
		pthread_mutex_unlock(&p->previous->r_chopstick);
		p->has_tkn = 0;
		tbl->tokens++;
		p->meals++;
		tbl->valid = update_meals_x_ph(tbl);
	}
}

static void	busy_wait(t_table *tbl)
{
	if ((*tbl->philo_turn)->philo_id % 2 == 0)
		usleep(tbl->args->t_sleep * 1000);
}

// TODO: update according to new structure
static void	*dinner(void *arg)
{
	t_table	*tbl;

	tbl = (t_table *)arg;
	busy_wait(tbl);
	while (tbl->meals_x_ph != tbl->args->n_eats_x_philo) // TODO: or 1st death
	{
		eat(tbl);
		if (tbl->valid != VALID)
			break ;
		// TODO: check for deaths
		*tbl->philo_turn = (*tbl->philo_turn)->next;
	}
	return (NULL);
}

// TODO: update according to new structure
t_table	*init_philo_threads(t_table *tbl)
{
	t_philo	*p;
	int		p_id_prev;

	if (tbl->valid != VALID)
		return (tbl);
	p = *tbl->philo_turn;
	if (p->philo_id != 1)
	{
		tbl->valid = PH_ID_ERR;
		return (tbl);
	}
	p_id_prev = p->previous->philo_id;
	while (p->philo_id - p_id_prev > 0)
	{
		p->valid = pthread_create(&p->thread_id, 0, &dinner, tbl);
		if (p->valid != VALID)
			return (tbl);
		p_id_prev = p->philo_id;
		p = p->next->next;
	}
	p = (*tbl->philo_turn)->next;
	while (p->philo_id - p_id_prev > 0)
	{
		p->valid = pthread_create(&p->thread_id, 0, &dinner, tbl);
		if (p->valid != VALID)
			return (tbl);
		p_id_prev = p->philo_id;
		p = p->next->next;
	}
	return (tbl);
}

// TODO: update according to new structure
void	run_philo_sim(t_table *table)
{
	table = init_philo_threads(table);
	// TODO: handle thread creation fail
}
