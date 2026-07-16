/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:41:17 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/07/16 23:57:05 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	state_log(int p_idx, char *state)
{
	// TODO: calc timestamp in ms
	printf("timestamp_in_ms %d %s\n", p_idx + 1, state);
}

// TODO: update according to new structure
static void	eat(t_philo *philo, int ph_idx)
{
	int	last_idx;

	last_idx = philo->args->n_philo - 1;
	if (philo->tokens > 0)
	{
		philo->tokens--;
		pthread_mutex_lock(&philo->chopsticks[ph_idx]);
		if (ph_idx == 0)
			pthread_mutex_lock(&philo->chopsticks[last_idx]);
		else
			pthread_mutex_lock(&philo->chopsticks[ph_idx - 1]);
		state_log(ph_idx, "is sleeping");
		usleep(philo->args->t_eat * 1000);
		if (ph_idx == 0)
			pthread_mutex_unlock(&philo->chopsticks[last_idx]);
		else
			pthread_mutex_unlock(&philo->chopsticks[ph_idx - 1]);
		philo->tokens++;
		philo->meals_x_ph[ph_idx]++;
	}
}

// TODO: update according to new structure
static void	*dinner(void *arg)
{
	t_philo	*philo;
	int		ph_idx;

	philo = (t_philo *)arg;
	ph_idx = 0;
	while (philo->tokens > 0)
	{
		eat(philo, ph_idx);
		philo->tokens--;
	}
	return (NULL);
}

// TODO: update according to new structure
static t_philo	*init_philo_threads(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->args->n_philo)
	{
		p->valid = pthread_create(&p->pt_ids[i], 0, &dinner, p);
		if (p->valid != VALID)
			return (p);
		i += 2;
	}
	i = 1;
	while (i < p->args->n_philo)
	{
		p->valid = pthread_create(&p->pt_ids[i], 0, dinner, p);
		if (p->valid != VALID)
			return (p);
		i += 2;
	}
	return (p);
}

// TODO: update according to new structure
void	run_philo_sim(t_philo *philo)
{
	philo = init_philo_threads(philo);
	// TODO: handle thread creation fail
}
