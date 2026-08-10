/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 23:03:03 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/10 13:41:26 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
// #include <bits/pthreadtypes.h>

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

// TODO: norm fix
static int	sit_philos(t_table *tbl)
{
	int		i;
	int		n_philo;
	t_philo	*p;
	t_philo	*prev;

	i = 0;
	n_philo = tbl->args->n_philo;
	*tbl->philo_head = NULL;
	prev = NULL;
	while (i < n_philo)
	{
		p = ft_calloc(1, sizeof(t_philo));
		if (!p)
			return (CALLOC_ERR);
		p->philo_id = i + 1;
		pthread_mutex_init(&p->r_chopstick, NULL);
		p->meals = 0;
		// TODO: separate function to link nodes?
		p->previous = prev;
		p->next = NULL;
		if (prev)
			prev->next = p;
		else
		 	*tbl->philo_head = p;
		p->valid = VALID;
		prev = p;
		i++;
	}
	if (prev && *tbl->philo_head)
	{
		prev->next = *tbl->philo_head;
		(*tbl->philo_head)->previous = prev;
	}
	return (VALID);
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

// TODO: norm fix
t_table	*set_table(t_table *table, char **av)
{
	int	tkn_max;
	int	i;

	table = ft_calloc(1, sizeof(t_table));
	if (!table)
		return (NULL);
	table->args = ft_calloc(1, sizeof(t_philo_args));
	if (!table->args)
	{
		table->valid = CALLOC_ERR;
		return (table);
	}
	tkn_max = table->args->n_philo / 2;
	table->args = init_table_args(table->args, av);
	table->tokens = ft_calloc(tkn_max, sizeof(pthread_mutex_t));
	if (!table->tokens)
	{
		table->valid = CALLOC_ERR;
		return (table);
	}
	i = 0;
	while (i < tkn_max)
	{
		pthread_mutex_init(&table->tokens[i], NULL);
		i++;
	}
	table->meals_x_ph = 0;
	table->philo_head = ft_calloc(1, sizeof(t_philo *));
	if (!table->philo_head)
	{
		table->valid = CALLOC_ERR;
		return (table);
	}
	table->valid = sit_philos(table);
	return (table);
}
