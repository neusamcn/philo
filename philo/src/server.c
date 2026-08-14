/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 11:15:58 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/14 15:54:06 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	pass_server(t_philo *p)
{
	while (dinner_is_over(*p->table) == false)
	{
		pthread_mutex_lock(&(*p->table)->sim->pass->run_dish);
		if (p->call_server != NULL && p->next->call_server == NULL)
		{
			p->next->call_server = p->call_server;
			p->call_server = NULL;
			pthread_mutex_unlock(&(*p->table)->sim->pass->run_dish);
			return ;
		}
		pthread_mutex_unlock(&(*p->table)->sim->pass->run_dish);
		usleep(100);
	}	
}

bool	wait_for_server(t_philo *p)
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
