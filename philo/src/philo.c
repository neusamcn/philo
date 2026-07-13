/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:59:23 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/07/13 20:46:15 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// TODO: add to /utils if there isn't enough space here
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
// static void	print_thread_ids(t_philo *philo)
// {
// 	int	i;
//
// 	i = 0;
// 	while (i < philo->args->n_philo)
// 	{
// 		printf("philo->pt_id[%d] = %ld\n", i, philo->pt_ids[i]);
// 		i++;
// 	}
// 	printf("\nphilo->valid = %d\n\n", philo->valid);
// }

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = NULL;
	if (ac < 5 || ac > 6 || !(validate_args(av)))
		return (exit_msg("Incorrect arguments.", NULL, philo, EXIT_FAILURE));
	philo = init_philo(philo, av);
	if (!philo || (philo && philo->valid != 0))
		return (exit_cleanup(philo, "t_philo *philo init", EXIT_FAILURE));
	// TODO: DELETE TESTER
	// print_thread_ids(philo);
	// TODO: philos' stuff

	return (exit_cleanup(philo, NULL, EXIT_SUCCESS));
}
