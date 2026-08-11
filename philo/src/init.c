/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 23:03:03 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/11 15:35:39 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

static void	print_philos(t_sim_args *sim_args)
{
	printf("Simulation starting with the following parameters:\n");
	printf(HOT_PINK"number_of_philosophers: "CLR_RST"%d", sim_args->n_philo);
	if (sim_args->n_philo < 9999999)
		printf("\t");
	if (sim_args->n_philo > 200)
		printf("\t-> "DEEP_PINK"WARNING"CLR_RST": you should NOT test "
			DEEP_PINK"above 200"CLR_RST"!");
	printf(HOT_PINK"\ntime_to_die: "CLR_RST"%d ms", sim_args->t_die);
	if (sim_args->t_die < 60)
		printf("\t\t\t-> "DEEP_PINK"WARNING"CLR_RST": you should NOT test "
			DEEP_PINK"below 60 ms"CLR_RST"!");
	printf(HOT_PINK"\ntime_to_eat: "CLR_RST"%d ms", sim_args->t_eat);
	if (sim_args->t_eat < 60)
		printf("\t\t\t-> "DEEP_PINK"WARNING"CLR_RST": you should NOT test "
			DEEP_PINK"below 60 ms"CLR_RST"!");
	printf(HOT_PINK"\ntime_to_sleep: "CLR_RST"%d ms", sim_args->t_sleep);
	if (sim_args->t_sleep < 60)
		printf("\t\t\t-> "DEEP_PINK"WARNING"CLR_RST": you should NOT test "
			DEEP_PINK"below 60 ms"CLR_RST"!");
	if (sim_args->n_eats_x_philo)
		printf(HOT_PINK"\nnumber_of_times_each_philosopher_must_eat:"CLR_RST
			" %d\n", sim_args->n_eats_x_philo);
	if (sim_args->n_eats_x_philo == 0)
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
		p->alive = 1;
		pthread_mutex_init(&p->r_chopstick, NULL);
		p->t_eat = tbl->args->t_eat;
		p->t_sleep = tbl->args->t_sleep;
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

static t_sim_args	*init_table_args(t_sim_args *sim_args, char **av)
{
	sim_args->n_philo = ft_atoi(av[1]);
	sim_args->t_die = ft_atoi(av[2]);
	sim_args->t_eat = ft_atoi(av[3]);
	sim_args->t_sleep = ft_atoi(av[4]);
	if (av[5])
		sim_args->n_eats_x_philo = ft_atoi(av[5]);
	print_philos(sim_args);
	return (sim_args);
}

static int	place_chopsticks(t_table *tbl)
{
	int	max_chopsticks;
	int	i;

	max_chopsticks = tbl->args->n_philo;
	tbl->chopsticks = ft_calloc(max_chopsticks, sizeof(pthread_mutex_t));
	if (!tbl->chopsticks)
		return (CALLOC_ERR);
	i = 0;
	while (i < max_chopsticks)
	{
		pthread_mutex_init(&tbl->chopsticks[i], NULL);
		i++;
	}
	return (VALID);
}

static int	prep_chits(t_table *tbl)
{
	int	max_chits;
	int	i;

	max_chits = (tbl->args->n_philo / 2) + (tbl->args->n_philo % 2);
	tbl->chits = ft_calloc(max_chits, sizeof(pthread_mutex_t));
	if (!tbl->chits)
		return (CALLOC_ERR);
	i = 0;
	while (i < max_chits)
	{
		pthread_mutex_init(&tbl->chits[i], NULL);
		i++;
	}
	return (VALID);
}

static int	expo_clock_in(t_table *tbl)
{
	int	i;

	tbl->expo = ft_calloc(3, sizeof(pthread_mutex_t));
	if (!tbl->expo)
		return (CALLOC_ERR);
	i = 0;
	while (i < 3)
	{
		pthread_mutex_init(&tbl->expo[i], NULL);
		i++;
	}
	return (VALID);
}

// TODO: norm fix
t_table	*set_table(t_table *table, char **av)
{
	// int	max_chits;
	// int	i;

	table = ft_calloc(1, sizeof(t_table));
	if (!table)
		return (NULL);
	table->args = ft_calloc(1, sizeof(t_sim_args));
	if (!table->args)
	{
		table->valid = CALLOC_ERR;
		return (table);
	}
	table->args = init_table_args(table->args, av);
	table->valid = prep_chits(table);
	if (table->valid != VALID)
		return (table);
	// max_chits = (table->args->n_philo / 2) + (table->args->n_philo % 2);
	// table->chits = ft_calloc(max_chits, sizeof(pthread_mutex_t));
	// if (!table->chits)
	// {
	// 	table->valid = CALLOC_ERR;
	// 	return (table);
	// }
	// i = 0;
	// while (i < max_chits)
	// {
	// 	pthread_mutex_init(&table->chits[i], NULL);
	// 	i++;
	// }
	table->valid = place_chopsticks(table);
	if (table->valid != VALID)
		return (table);
	table->t_dinner_start = time_in_ms();
	if (table->t_dinner_start == TIME_ERR)
	{
		table->valid = TIME_ERR;
		return (table);
	}
	table->meals_x_ph = 0;
	table->valid = expo_clock_in(table);
	if (table->valid != VALID)
		return (table);
	table->end_dinner = false;
	table->philo_head = ft_calloc(1, sizeof(t_philo *));
	if (!table->philo_head)
	{
		table->valid = CALLOC_ERR;
		return (table);
	}
	// table->philo_turn = ft_calloc((table->args->n_philo), sizeof(int));
	// if (!table->philo_turn)
	// {
	// 	table->valid = CALLOC_ERR;
	// 	return (table);
	// }
	table->valid = sit_philos(table);
	return (table);
}
