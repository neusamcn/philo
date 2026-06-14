/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:59:23 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/06/14 23:24:14 by ncruz-ne         ###   ########.fr       */
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

static void	print_philos(t_philo *philo)
{
	printf("Simulation starting with the following parameters:\n");
	printf(HOT_PINK"number_of_philosophers: "COLOR_RESET"%d", philo->n_philo);
	if (philo->n_philo < 9999999)
		printf("\t");
	if (philo->n_philo > 200)
		printf("\t-> "DEEP_PINK"WARNING"COLOR_RESET": you should NOT test "
			DEEP_PINK"above 200"COLOR_RESET"!");
	printf(HOT_PINK"\ntime_to_die: "COLOR_RESET"%d ms", philo->t_die);
	if (philo->t_die < 60)
		printf("\t\t\t-> "DEEP_PINK"WARNING"COLOR_RESET": you should NOT test "
			DEEP_PINK"below 60 ms"COLOR_RESET"!");
	printf(HOT_PINK"\ntime_to_eat: "COLOR_RESET"%d ms", philo->t_eat);
	if (philo->t_eat < 60)
		printf("\t\t\t-> "DEEP_PINK"WARNING"COLOR_RESET": you should NOT test "
			DEEP_PINK"below 60 ms"COLOR_RESET"!");
	printf(HOT_PINK"\ntime_to_sleep: "COLOR_RESET"%d ms", philo->t_sleep);
	if (philo->t_sleep < 60)
		printf("\t\t\t-> "DEEP_PINK"WARNING"COLOR_RESET": you should NOT test "
			DEEP_PINK"below 60 ms"COLOR_RESET"!");
	if (philo->n_eats_x_philo)
		printf(HOT_PINK"\nnumber_of_times_each_philosopher_must_eat:"COLOR_RESET
			" %d\n", philo->n_eats_x_philo);
	if (philo->n_eats_x_philo == 0)
		printf("\n");
	printf("\n");
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
