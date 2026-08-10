/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:41:17 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/10 20:17:14 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	state_log(int p_id, char *state)
{
	// TODO: calc timestamp in ms - provide as var for time accuracy
	printf("timestamp_in_ms %d %s\n", p_id, state);
}

static int	update_meals_x_ph(t_table *tbl)
{
	t_philo	*p_curr;
	int		p_start_id;
	int		tot_meals;

	p_curr = *tbl->philo_head;
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
// TODO: DELETE TESTER
// static int	lock_fork(pthread_mutex_t *fork)
// {
// 	while (!g_stop)
// 	{
// 		if (pthread_mutex_trylock(fork) == 0)
// 			return (1);
// 		usleep(100);
// 	}
// 	return (0);
// }

// // TODO: DELETE TESTER
// static void	stop_aware_sleep(int ms)
// {
// 	int	elapsed;
//
// 	elapsed = 0;
// 	while (!g_stop && elapsed < ms)
// 	{
// 		usleep(1000);
// 		elapsed++;
// 	}
// }

// static void	busy_wait(t_philo *p)
// {
// 	if (p->philo_id % 2 == 0)
// 	{
// 		state_log((*tbl->philo_head)->philo_id, "is sleeping");
// 		usleep(tbl->args->t_sleep * 1000);
// 	}
// }

static void	eat_or_wait(t_philo *p)
{
	if (p->has_tkn == 1)
	{
		pthread_mutex_lock(&p->r_chopstick);
		state_log(p->philo_id, "has taken a fork");
		pthread_mutex_lock(&p->previous->r_chopstick);
		state_log(p->philo_id, "has taken a fork");
		state_log(p->philo_id, "is eating");
		usleep(p->t_eat * 1000);
		pthread_mutex_unlock(&p->r_chopstick);
		pthread_mutex_unlock(&p->previous->r_chopstick);
		p->has_tkn = 0;
		p->meals++;
	}
	else if (p->has_tkn == 0)
	{
		state_log(p->philo_id, "is sleeping");
		usleep(p->t_sleep * 1000);
		state_log(p->philo_id, "is thinking");
	}
	// TODO: death check? too much time since last meal? new var?
}

// static void	give_token(t_table *tbl)
// {
// 	int		i;
// 	int		max_tkns;
// 	t_philo	*curr_p;
// 	int		start;
//
// 	curr_p = *tbl->philo_head;
// 	if (curr_p->philo_id != 1)
// 	{
// 		tbl->valid = PH_ID_ERR;
// 		return ;
// 	}
// 	start = 1;
// 	while (curr_p->has_tkn == 1 && (start || curr_p != *tbl->philo_head))
// 	{
// 		start = 0;
// 		curr_p = curr_p->next;
// 	}
// 	if (curr_p->has_tkn == 0)
// 	i = 0;
// 	start = 1;
// 	while (i < max_tkns && (start || curr_p != *tbl->philo_head))
// 	{
// 		if (curr_p->has_tkn == 0)
// 		{
// 			start = 0;
// 			pthread_mutex_lock(&tbl->tokens[i]);
// 			i++;
// 			curr_p->has_tkn = 1;
// 			curr_p = curr_p->next->next;
// 		}
// 		else
// 		{
// 			start = 0;
// 			curr_p = curr_p->next;
// 		}
// 	}
// }

static void	*dinner(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	// TODO: REMOVE TESTER
	// while (!g_stop && p->alive == 1)
	// 	eat_or_wait(p);
	while (p->alive == 1)
		eat_or_wait(p);
	if (p->alive == 0)
		return (NULL);
	// TODO: Check for max meals? add var?
	return (NULL);
}

// TODO: fix norm
t_table	*init_philo_threads(t_table *tbl)
{
	t_philo	*p;
	int		p_id_prev;
	int		i;
	int		tkns_max;

	if (tbl->valid != VALID)
		return (tbl);
	p = *tbl->philo_head;
	if (p->philo_id != 1)
	{
		tbl->valid = PH_ID_ERR;
		return (tbl);
	}
	p_id_prev = 0;
	i = 0;
	tkns_max = (tbl->args->n_philo / 2) + (tbl->args->n_philo % 2);
	while (p->philo_id - p_id_prev > 0 && i < tkns_max)
	{
		p->valid = pthread_create(&p->thread_id, 0, &dinner, p);
		if (p->valid != VALID)
			return (tbl);
		pthread_mutex_lock(&tbl->tokens[i++]);
		p->has_tkn = 1;
		tbl->philo_turn[p->philo_id - 1] = 1;
		p_id_prev = p->philo_id;
		p = p->next->next;
	}
	// MONITOR CHECKS
	tbl->valid = update_meals_x_ph(tbl);
	if (tbl->meals_x_ph >= tbl->args->n_eats_x_philo)
		return (tbl);
	p = (*tbl->philo_head)->next;
	p_id_prev = 0;
	i = 0;
	while (tbl->philo_turn[0] == 1)
	{
		usleep(10);
		continue ;
	}
	while (p->philo_id - p_id_prev > 0 && i < tkns_max)
	{
		p->valid = pthread_create(&p->thread_id, 0, &dinner, p);
		if (p->valid != VALID)
			return (tbl);
		p->has_tkn = 1;
		pthread_mutex_lock(&tbl->tokens[i++]);
		tbl->philo_turn[p->philo_id - 1] = 1;
		p_id_prev = p->philo_id;
		p = p->next->next;
	}
	return (tbl);
}

void	run_philo_sim(t_table *table)
{
	table = init_philo_threads(table);
	// TODO: handle thread creation fail
}
