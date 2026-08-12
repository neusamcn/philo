/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:41:17 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/12 15:00:41 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	dinner_is_over(t_table *tbl)
{
	bool	end_dinner;

	pthread_mutex_lock(&(*tbl->sim)->end_sim);
	end_dinner = tbl->end_dinner;
	pthread_mutex_unlock(&(*tbl->sim)->end_sim);
	return (end_dinner);
}

static void	state_log(t_philo *p, char *state)
{
	int64_t	t_dinner_start;

	pthread_mutex_lock(&(*(*p->table)->sim)->print_log);
	t_dinner_start = (*p->table)->t_dinner_start;
	if (dinner_is_over(*p->table) == false)
		printf("%" PRId64 " %d %s\n",
			time_in_ms() - t_dinner_start, p->philo_id, state);
	pthread_mutex_unlock(&(*(*p->table)->sim)->print_log);
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
	if (p->call_server == 1)
	{
		pthread_mutex_lock(&p->r_chopstick);
		state_log(p, "has taken a fork");
		pthread_mutex_lock(&p->previous->r_chopstick);
		state_log(p, "has taken a fork");
		state_log(p, "is eating");
		usleep(p->t_eat * 1000);
		pthread_mutex_unlock(&p->r_chopstick);
		pthread_mutex_unlock(&p->previous->r_chopstick);
		p->call_server = 0;
		p->meals++;
	}
	else if (p->call_server == 0)
	{
		state_log(p, "is sleeping");
		usleep(p->t_sleep * 1000);
		state_log(p, "is thinking");
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

static void	ph_sleep(t_philo *p)
{
	state_log(p, "is sleeping");
	usleep_precise();	
}

static void	take_plate(t_philo *p)
{
	
}

static void	eat(t_philo *p)
{
	// TODO: should i (un)lock tkns here?
	p->t_last_meal = time_in_ms();
	state_log(p, "is eating");
	p->meals++;
}

static void	order_meal(t_philo *p)
{
	pthread_mutex_lock(&*p->call_server); // TODO: rethink how this works ?
	if (p->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&*p->l_chopstick);
		state_log(p, "has taken a fork");
		pthread_mutex_lock(&*p->r_chopstick);
	}
	else
	{
		pthread_mutex_lock(&*p->r_chopstick);
		state_log(p, "has taken a fork");
		pthread_mutex_lock(&*p->l_chopstick);
	}
	state_log(p, "has taken a fork");
}

static void	*dinner(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->philo_id % 2 == 0)
		usleep(1);
	// TODO: REMOVE TESTER
	// while (!g_stop && p->alive == 1)
	// 	eat_or_wait(p);
	while (dinner_is_over(*p->table) == false) // all ph are alive and if max meals for all haven't been reached
	{
		order_meal(p);
		eat(p);
		take_plate(p);
		ph_sleep(p);
		state_log(p, "is thinking");
	}
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
		pthread_mutex_lock(&tbl->rail[i++]);
		p->call_server = 1;
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
		p->call_server = 1;
		pthread_mutex_lock(&tbl->rail[i++]);
		tbl->philo_turn[p->philo_id - 1] = 1;
		p_id_prev = p->philo_id;
		p = p->next->next;
	}
	return (tbl);
}

t_err	start_dinner(t_sim *sim)
{
	int		start;
	t_philo	*curr_p;

	start = 1;
	curr_p = *sim->table->philo_head;
	while (start && curr_p != *sim->table->philo_head)
	{
		start = 0;
		curr_p->valid = pthread_create(&curr_p->thread_id, 0, &dinner, curr_p);
		if (curr_p->valid != VALID)
			return (curr_p->valid);
		curr_p = curr_p->next;
	}
	// sim = init_philo_threads(sim);
	return (VALID);
}
