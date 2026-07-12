/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:59:23 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/07/12 23:00:48 by ncruz-ne         ###   ########.fr       */
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

static t_philo_args	*init_philo_args(t_philo_args *p_args, char **av)
{
	p_args->n_philo = ft_atoi(av[1]);
	p_args->t_die = ft_atoi(av[2]);
	p_args->t_eat = ft_atoi(av[3]);
	p_args->t_sleep = ft_atoi(av[4]);
	if (av[5])
		p_args->n_eats_x_philo = ft_atoi(av[5]);
	print_philos(p_args);
	return (p_args);
}

static t_philo	*init_philo_threads(t_philo *philo)
{
	int	n_i;

	n_i = 0;
	while (n_i < philo->args->n_philo)
	{
		philo->pt_ids[n_i] = ft_calloc(1, sizeof(pthread_t));
		if (!philo->pt_ids[n_i])
		{
			philo->valid = CALLOC_ERR;
			break ;
		}
		philo->valid = pthread_create(philo->pt_ids[n_i], NULL, NULL, NULL);
		if (philo->valid)
			break ;
		n_i++;
	}
	if (n_i == philo->args->n_philo)
	{
		philo->pt_ids[n_i] = ft_calloc(1, sizeof(pthread_t));
		if (!philo->pt_ids[n_i])
			philo->valid = CALLOC_ERR;
	}
	return (philo);
}

static t_philo	*init_philo(t_philo *philo, char **av)
{
	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->args = ft_calloc(1, sizeof(t_philo_args));
	if (!philo->args)
		return (NULL);
	philo->args = init_philo_args(philo->args, av);
	philo->pt_ids = ft_calloc(1, sizeof(pthread_t *));
	if (!philo->pt_ids)
		return (NULL);
	philo->valid = ft_calloc(1, sizeof(int));
	philo = init_philo_threads(philo);
	if (philo->valid)
		return (NULL);
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
