/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:59:23 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/06/14 18:19:33 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// TODO: add to /utils ?
static int	validate_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if ((i < 5))
		{
			if (av[i][0] == 0 || !(isdigit_str(av[i])) || ft_atoi(av[i]) <= 0)
				return (0);
		}
		else if (!(isdigit_str(av[i]))
			|| ft_atol(av[i]) < 0 || ft_atol(av[i]) > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

// TODO: DELETE TESTER
static void	print_philos(t_philo *philo)
{
	printf(HOT_PINK"number_of_philosophers: "COLOR_RESET"%d\n", philo->n_philo);
	printf(HOT_PINK"time_to_die: "COLOR_RESET"%d\n", philo->t_die);
	printf(HOT_PINK"time_to_eat: "COLOR_RESET"%d\n", philo->t_eat);
	printf(HOT_PINK"time_to_sleep: "COLOR_RESET"%d\n", philo->t_sleep);
	if (philo->n_eats_x_philo)
		printf(HOT_PINK"number_of_times_each_philosopher_must_eat: "COLOR_RESET
			"%d\n", philo->n_eats_x_philo);
}

static t_philo	*init_philo(t_philo *philo, char **av)
{
	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->n_philo = ft_atoi(av[1]);
	philo->t_die = ft_atoi(av[2]);
	philo->t_eat = ft_atoi(av[3]);
	philo->t_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->n_eats_x_philo = ft_atoi(av[5]);
	// TODO: DELETE TESTER
	print_philos(philo);
	return (philo);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = NULL;
	if (ac < 5 || ac > 6 || !(validate_args(av)))
		return (exit_msg("Incorrect arguments.", NULL, philo, EXIT_FAILURE));
	philo = init_philo(philo, av);
	if (!philo)
		return (exit_cleanup(philo, "ft_calloc(1, philo)", EXIT_FAILURE));
	// TODO: philos' stuff
	return (exit_cleanup(philo, NULL, EXIT_SUCCESS));
}
