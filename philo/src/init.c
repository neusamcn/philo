/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 23:03:03 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/14 10:19:44 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	print_philos(t_sim_args *sim_args)
{
	printf("Simu- erm... Dinner starting with:\n");
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

static t_philo	*arrange_seats(t_philo *p, t_philo *prev, t_sim *sim)
{
	p->previous = prev;
	p->next = NULL;
	if (prev)
		prev->next = p;
	else
		*sim->table->philo_head = p;
	p->valid = VALID;
	prev = p;
	return (prev);
}

static void	sit_philo(t_philo *p, int i, t_sim *sim)
{
	int	n_philo;

	n_philo = sim->args->n_philo;
	p->philo_id = i + 1;
	p->alive = true;
	p->call_server = NULL;
	if (i % 2 == 0 && i < n_philo - 1)
		p->call_server = &sim->pass->rail[i / 2];
	p->l_chopstick = &sim->table->chopsticks[i];
	p->r_chopstick = &sim->table->chopsticks[(i + 1) % n_philo];
	p->t_last_meal = sim->table->t_dinner_start;
	p->meals = 0;
	p->table = &sim->table;
}

static int	sit_philos(t_sim *sim)
{
	int		i;
	int		n_philo;
	t_philo	*p;
	t_philo	*prev;

	i = 0;
	n_philo = sim->args->n_philo;
	*sim->table->philo_head = NULL;
	prev = NULL;
	while (i < n_philo)
	{
		p = ft_calloc(1, sizeof(t_philo));
		if (!p)
			return (CALLOC_ERR);
		sit_philo(p, i, sim);
		prev = arrange_seats(p, prev, sim);
		i++;
	}
	if (prev && *sim->table->philo_head)
	{
		prev->next = *sim->table->philo_head;
		(*sim->table->philo_head)->previous = prev;
	}
	return (VALID);
}

void	setup_sim_args(t_sim *sim, char **av)
{
	sim->args = ft_calloc(1, sizeof(t_sim_args));
	if (!sim->args)
	{
		sim->valid = CALLOC_ERR;
		return ;
	}
	sim->args->n_philo = ft_atoi(av[1]);
	sim->args->t_die = ft_atoi(av[2]);
	sim->args->t_eat = ft_atoi(av[3]);
	sim->args->t_sleep = ft_atoi(av[4]);
	if (av[5])
		sim->args->n_eats_x_philo = ft_atoi(av[5]);
	if (FLAIR == ON)
		print_philos(sim->args);
	return ;
}

static int	place_chopsticks(t_sim *sim)
{
	int	max_chopsticks;
	int	i;

	max_chopsticks = sim->args->n_philo;
	sim->table->chopsticks = ft_calloc(max_chopsticks, sizeof(pthread_mutex_t));
	if (!sim->table->chopsticks)
		return (CALLOC_ERR);
	i = 0;
	while (i < max_chopsticks)
	{
		pthread_mutex_init(&sim->table->chopsticks[i], NULL);
		i++;
	}
	return (VALID);
}

t_err	mise_en_place(t_sim *sim)
{
	int	i;

	sim->pass = ft_calloc(1, sizeof(t_pass));
	if (!sim->pass)
		return (CALLOC_ERR);
	sim->pass->max_chits = (sim->args->n_philo / 2);
	sim->pass->rail = ft_calloc(sim->pass->max_chits, sizeof(pthread_mutex_t));
	if (!sim->pass->rail)
		return (CALLOC_ERR);
	i = 0;
	while (i < sim->pass->max_chits)
		pthread_mutex_init(&sim->pass->rail[i++], NULL);
	pthread_mutex_init(&sim->pass->run_dish, NULL);
	sim->pass->valid = VALID;
	return (sim->pass->valid);
}

t_err	set_table(t_sim *sim)
{
	sim->table = ft_calloc(1, sizeof(t_table));
	if (!sim->table)
		return (CALLOC_ERR);
	sim->table->valid = place_chopsticks(sim);
	if (sim->table->valid != VALID)
		return (sim->table->valid);
	sim->table->t_dinner_start = time_in_ms();
	if (sim->table->t_dinner_start == TIME_ERR)
		return (sim->table->t_dinner_start);
	sim->table->end_dinner = false;
	sim->table->philo_head = ft_calloc(1, sizeof(t_philo *)); // TODO: needed?
	if (!sim->table->philo_head)
		return (CALLOC_ERR);
	sim->table->sim = sim;
	sim->table->valid = sit_philos(sim);
	return (sim->table->valid);
}
