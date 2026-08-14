/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:41:17 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/14 11:40:15 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
