/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 11:15:58 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/14 13:17:08 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	server_takes_order(t_philo *p)
{
	while (dinner_is_over(*p->table) == false)
	{
		pthread_mutex_lock(&(*p->table)->sim->pass->run_dish);
		if (p->call_server != NULL)
		{
			pthread_mutex_unlock(&(*p->table)->sim->pass->run_dish);
			return (true);
		}
		pthread_mutex_unlock(&(*p->table)->sim->pass->run_dish);
		usleep(100);
	}
	return (false);
}

bool	order_meal(t_philo *p)
{
    if (p->r_chopstick == p->l_chopstick)
    {
  		pthread_mutex_lock(&*p->l_chopstick);
		state_log(p, "has taken a", UTENSIL);
        usleep_precise((*p->table)->sim->args->t_die, *p->table);
  		pthread_mutex_unlock(&*p->l_chopstick);
        update_end_dinner_status(*p->table, true);
        return (false);
    }
	if (server_takes_order(p) == false)
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
