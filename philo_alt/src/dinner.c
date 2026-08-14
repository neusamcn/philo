/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 11:30:00 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/14 11:51:46 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ph_sleep(t_philo *p)
{
	state_log(p, "is sleeping", "");
	usleep_precise((*p->table)->sim->args->t_sleep, *p->table);	
}

static void	switch_ph_turn(t_philo *p)
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
	pass_token(p);
}

static void	eat(t_philo *p)
{
	pthread_mutex_lock(&(*p->table)->sim->pass->run_dish);
	p->t_last_meal = time_in_ms();
	state_log(p, "is eating", "");
	p->meals++;
	pthread_mutex_unlock(&(*p->table)->sim->pass->run_dish);
	usleep_precise((*p->table)->sim->args->t_eat, *p->table);
}

static bool	ph_new_eating_turn(t_philo *p)
{
	if (wait_for_token(p) == false)
		return (false);
	if (p->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&*p->l_chopstick);
		state_log(p, "has taken a", UTENSIL);
		pthread_mutex_lock(&*p->r_chopstick);
	}
	else
	{
		pthread_mutex_lock(&*p->r_chopstick);
		state_log(p, "has taken a", UTENSIL);
		pthread_mutex_lock(&*p->l_chopstick);
	}
	state_log(p, "has taken a", UTENSIL);
	return (true);
}

void	*dinner(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->philo_id % 2 == 0)
		usleep(1);
	while (dinner_is_over(*p->table) == false)
	{
		if (ph_new_eating_turn(p) == false)
			break ;
		eat(p);
		switch_ph_turn(p);
		ph_sleep(p);
		state_log(p, "is thinking", "");
	}
	return (NULL);
}
