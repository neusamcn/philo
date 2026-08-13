/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:41:17 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/13 13:48:34 by ncruz-ne         ###   ########.fr       */
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

void	state_log(t_philo *p, char *state)
{
	int64_t	t_dinner_start;

	pthread_mutex_lock(&(*p->table)->sim->print_log);
	t_dinner_start = (*p->table)->t_dinner_start;
	if (dinner_is_over(*p->table) == false)
		printf("%" PRId64 " %d %s\n",
			time_in_ms() - t_dinner_start, p->philo_id, state);
	pthread_mutex_unlock(&(*p->table)->sim->print_log);
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
//
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

static void	ph_sleep(t_philo *p)
{
	state_log(p, "is sleeping");
	usleep_precise((*p->table)->sim->args->t_sleep, *p->table);	
}

static void	take_plate(t_philo *p)
{
	if (p->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(&*p->l_chopstick);
		pthread_mutex_unlock(&*p->r_chopstick);
	}
	else
	{
		pthread_mutex_unlock(&*p->r_chopstick);
		pthread_mutex_unlock(&*p->l_chopstick);
	}
	pthread_mutex_unlock(&*p->call_server); // TODO: rethink how this works ?
}

static void	eat(t_philo *p)
{
	// TODO: should i (un)lock tkns here?
	pthread_mutex_lock(&(*p->table)->sim->pass->run_dish);
	p->t_last_meal = time_in_ms();
	state_log(p, "is eating");
	p->meals++;
	pthread_mutex_unlock(&(*p->table)->sim->pass->run_dish);
	usleep_precise((*p->table)->sim->args->t_eat, *p->table);
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

t_err	start_dinner(t_sim *sim)
{
	int		start;
	t_philo	*curr_p;

	start = 1;
	curr_p = *sim->table->philo_head;
	while (curr_p && (start || curr_p != *sim->table->philo_head))
	{
		start = 0;
		curr_p->valid = pthread_create(&curr_p->thread_id, 0, &dinner, curr_p);
		if (curr_p->valid != VALID)
			return (curr_p->valid);
		curr_p = curr_p->next;
	}
	return (VALID);
}

void	update_end_dinner_status(t_table *tbl, bool new_status)
{
	pthread_mutex_lock(&tbl->sim->end_sim);
	tbl->end_dinner = new_status;
	pthread_mutex_unlock(&tbl->sim->end_sim);
}
