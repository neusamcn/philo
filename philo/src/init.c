/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 23:03:03 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/07/16 23:56:00 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	print_philos(t_philo_args *tbl_args)
{
	printf("Simulation starting with the following parameters:\n");
	printf(HOT_PINK"number_of_philosophers: "CLR_RST"%d", tbl_args->n_philo);
	if (tbl_args->n_philo < 9999999)
		printf("\t");
	if (tbl_args->n_philo > 200)
		printf("\t-> "DEEP_PINK"WARNING"CLR_RST": you should NOT test "
			DEEP_PINK"above 200"CLR_RST"!");
	printf(HOT_PINK"\ntime_to_die: "CLR_RST"%d ms", tbl_args->t_die);
	if (tbl_args->t_die < 60)
		printf("\t\t\t-> "DEEP_PINK"WARNING"CLR_RST": you should NOT test "
			DEEP_PINK"below 60 ms"CLR_RST"!");
	printf(HOT_PINK"\ntime_to_eat: "CLR_RST"%d ms", tbl_args->t_eat);
	if (tbl_args->t_eat < 60)
		printf("\t\t\t-> "DEEP_PINK"WARNING"CLR_RST": you should NOT test "
			DEEP_PINK"below 60 ms"CLR_RST"!");
	printf(HOT_PINK"\ntime_to_sleep: "CLR_RST"%d ms", tbl_args->t_sleep);
	if (tbl_args->t_sleep < 60)
		printf("\t\t\t-> "DEEP_PINK"WARNING"CLR_RST": you should NOT test "
			DEEP_PINK"below 60 ms"CLR_RST"!");
	if (tbl_args->n_eats_x_philo)
		printf(HOT_PINK"\nnumber_of_times_each_philosopher_must_eat:"CLR_RST
			" %d\n", tbl_args->n_eats_x_philo);
	if (tbl_args->n_eats_x_philo == 0)
		printf("\n");
	printf("\n");
}

static t_philo_args	*init_table_args(t_philo_args *tbl_args, char **av)
{
	tbl_args->n_philo = ft_atoi(av[1]);
	tbl_args->t_die = ft_atoi(av[2]);
	tbl_args->t_eat = ft_atoi(av[3]);
	tbl_args->t_sleep = ft_atoi(av[4]);
	if (av[5])
		tbl_args->n_eats_x_philo = ft_atoi(av[5]);
	print_philos(tbl_args);
	return (tbl_args);
}

// TODO: update according to new structure
t_philo	*init_philo(t_philo *philo, char **av)
{
	int	i;

	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->valid = CALLOC_ERR;
	philo->pt_ids = ft_calloc(philo->args->n_philo, sizeof(pthread_t));
	if (!philo->pt_ids)
		return (philo);
	philo->chopsticks = ft_calloc(philo->args->n_philo,
			sizeof(pthread_mutex_t));
	if (!philo->chopsticks)
		return (philo);
	i = 0;
	while (i < philo->args->n_philo)
		pthread_mutex_init(&philo->chopsticks[i++], NULL);
	philo->valid = VALID;
	return (philo);
}

t_table	*set_table(t_table *table, char **av)
{
	table = ft_calloc(1, sizeof(t_table));
	if (!table)
		return (NULL);
	table->valid = CALLOC_ERR;
	table->args = ft_calloc(1, sizeof(t_philo_args));
	if (!table->args)
		return (table);
	table->args = init_table_args(table->args, av);
	table->tokens = table->args->n_philo / 2;
	// TODO: should init for head be here? or only with run_sim?
	table->head_philos = ft_calloc(1, sizeof(t_philo));
	table->meals_x_ph = 0;
	table->valid = VALID;
	return (table);
}
