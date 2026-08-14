/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_logs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 11:40:25 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/14 11:40:42 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	state_log(t_philo *p, char *state, char *utensil)
{
	int64_t	t_dinner_start;

	pthread_mutex_lock(&(*p->table)->sim->print_log);
	t_dinner_start = (*p->table)->t_dinner_start;
	if (dinner_is_over(*p->table) == false)
		printf("%" PRId64 " %d %s%s\n",
			time_in_ms() - t_dinner_start, p->philo_id, state, utensil);
	pthread_mutex_unlock(&(*p->table)->sim->print_log);
}
