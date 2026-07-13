/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:59:23 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/07/14 00:09:40 by ncruz-ne         ###   ########.fr       */
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
// static void	print_p_struct(t_philo *philo)
// {
// 	int	i;
// 	int	mtx_lock_st;
// 
// 	i = 0;
// 	while (i < philo->args->n_philo)
// 	{
// 		printf("philo->pt_id[%d] = %ld\n", i, philo->pt_ids[i]);
// 		i++;
// 	}
// 	printf("\nphilo->valid = %d", philo->valid);
// 	printf("\nphilo->tokens = %d\n\n", philo->tokens);
// 	i = 0;
// 	while (i < philo->args->n_philo)
// 	{
// 		mtx_lock_st = pthread_mutex_trylock(&philo->chopsticks[i]);
// 		if (mtx_lock_st == 0)
// 		{
// 			printf("philo->chopsticks[%d] is unlocked\n", i);
// 			pthread_mutex_unlock(&philo->chopsticks[i]);
// 		}
// 		else if (mtx_lock_st == EBUSY)
// 			printf("philo->chopsticks[%d] is locked\n", i);
// 		else
// 			printf("philo->chopsticks[%d] with errno %d\n", i, mtx_lock_st);
// 		i++;
// 	}
// 	printf("\n");
// }

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = NULL;
	if (ac < 5 || ac > 6 || !(validate_args(av)))
		return (exit_msg("Incorrect arguments.", NULL, philo, EXIT_FAILURE));
	philo = init_philo(philo, av);
	if (!philo || (philo && philo->valid != VALID))
		return (exit_cleanup(philo, "t_philo *philo init", EXIT_FAILURE));
	// TODO: DELETE TESTER
	print_p_struct(philo);
	// TODO: philos' stuff
	run_philo_sim(philo);
	return (exit_cleanup(philo, NULL, EXIT_SUCCESS));
}
