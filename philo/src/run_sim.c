/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:41:17 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/07/15 22:52:42 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	eat(t_philo *philo, int ph_idx)
{
	int	last_idx;

	last_idx = philo->args->n_philo - 1;

	pthread_mutex_lock(&philo->chopsticks[ph_idx]);
	if (ph_idx == 0)
		pthread_mutex_lock(&philo->chopsticks[last_idx]);
	else
		pthread_mutex_unlock(&philo->chopsticks[ph_idx - 1]);
	usleep(philo->args->t_eat * 1000);
	if (ph_idx == 0)
		pthread_mutex_unlock(&philo->chopsticks[last_idx]);
	else
		pthread_mutex_unlock(&philo->chopsticks[ph_idx - 1]);
	philo->meals_x_ph[ph_idx]++;

}

void	run_philo_sim(t_philo *philo)
{
	int	ph_idx;

	ph_idx = 0;
	while (philo->tokens > 0)
	{
		eat(philo, ph_idx);
		philo->tokens--;
	}
}
