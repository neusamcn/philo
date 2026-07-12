/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 23:03:03 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/07/12 23:56:15 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	print_philos(t_philo_args *p_args)
{
	printf("Simulation starting with the following parameters:\n");
	printf(HOT_PINK"number_of_philosophers: "COLOR_RESET"%d", p_args->n_philo);
	if (p_args->n_philo < 9999999)
		printf("\t");
	if (p_args->n_philo > 200)
		printf("\t-> "DEEP_PINK"WARNING"COLOR_RESET": you should NOT test "
			DEEP_PINK"above 200"COLOR_RESET"!");
	printf(HOT_PINK"\ntime_to_die: "COLOR_RESET"%d ms", p_args->t_die);
	if (p_args->t_die < 60)
		printf("\t\t\t-> "DEEP_PINK"WARNING"COLOR_RESET": you should NOT test "
			DEEP_PINK"below 60 ms"COLOR_RESET"!");
	printf(HOT_PINK"\ntime_to_eat: "COLOR_RESET"%d ms", p_args->t_eat);
	if (p_args->t_eat < 60)
		printf("\t\t\t-> "DEEP_PINK"WARNING"COLOR_RESET": you should NOT test "
			DEEP_PINK"below 60 ms"COLOR_RESET"!");
	printf(HOT_PINK"\ntime_to_sleep: "COLOR_RESET"%d ms", p_args->t_sleep);
	if (p_args->t_sleep < 60)
		printf("\t\t\t-> "DEEP_PINK"WARNING"COLOR_RESET": you should NOT test "
			DEEP_PINK"below 60 ms"COLOR_RESET"!");
	if (p_args->n_eats_x_philo)
		printf(HOT_PINK"\nnumber_of_times_each_philosopher_must_eat:"COLOR_RESET
			" %d\n", p_args->n_eats_x_philo);
	if (p_args->n_eats_x_philo == 0)
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

static void	*pt_routine(void *arg)
{
	(void)arg;
	return (NULL);
}

static t_philo	*init_philo_threads(t_philo *p)
{
	int	n_i;

	n_i = 0;
	while (n_i < p->args->n_philo)
	{
		p->valid = pthread_create(&p->pt_ids[n_i], 0, pt_routine, p);
		if (p->valid)
			break ;
		n_i++;
	}
	return (p);
}

t_philo	*init_philo(t_philo *philo, char **av)
{
	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->args = ft_calloc(1, sizeof(t_philo_args));
	if (!philo->args)
		return (NULL);
	philo->args = init_philo_args(philo->args, av);
	philo->pt_ids = ft_calloc(philo->args->n_philo, sizeof(pthread_t));
	if (!philo->pt_ids)
		return (NULL);
	philo->valid = 0;
	philo = init_philo_threads(philo);
	if (philo->valid)
		return (NULL);
	return (philo);
}
