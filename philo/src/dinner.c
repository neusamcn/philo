/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 11:30:00 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/14 13:16:44 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdbool.h>

static void	ph_sleep(t_philo *p)
{
	state_log(p, "is sleeping", "");
	usleep_precise((*p->table)->sim->args->t_sleep, *p->table);	
}

static void	finish_meal(t_philo *p)
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

void	*dinner(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->philo_id % 2 == 0)
		usleep(1);
	while (dinner_is_over(*p->table) == false)
	{
		if (order_meal(p) == false)
			break ;
		eat(p);
		finish_meal(p);
		ph_sleep(p);
		state_log(p, "is thinking", "");
	}
	return (NULL);
}
