/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:59:23 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/14 13:32:13 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	validate_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if ((i < 5))
		{
			if (av[i][0] == 0 || !(isdigit_str(av[i])) || ft_atoi(av[i]) <= 0)
				return (ARGS_ERR);
		}
		else if (!(isdigit_str(av[i]))
			|| ft_atol(av[i]) < 0 || ft_atol(av[i]) > INT_MAX)
			return (ARGS_ERR);
		i++;
	}
	return (VALID);
}

static t_err	mise_en_place(t_sim *sim)
{
	sim->pass = ft_calloc(1, sizeof(t_pass));
	if (!sim->pass)
		return (CALLOC_ERR);
	pthread_mutex_init(&sim->pass->server, NULL);
	pthread_mutex_init(&sim->pass->run_dish, NULL);
	sim->pass->valid = VALID;
	return (sim->pass->valid);
}

static void	setup_sim_args(t_sim *sim, char **av)
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

int	main(int ac, char **av)
{
	t_sim	*sim;

	sim = NULL;
	if (ac < 5 || ac > 6 || validate_args(av) != VALID)
		return (exit_msg("Incorrect arguments", NULL, sim, EXIT_FAILURE));
	if (FLAIR == ON)
		printf("%s", WELCOME);
	sim = ft_calloc(1, sizeof(t_sim));
	if (!sim)
		return (exit_cleanup(sim, "Failed *sim ft_calloc()", EXIT_FAILURE));
	pthread_mutex_init(&sim->print_log, NULL);
	pthread_mutex_init(&sim->end_sim, NULL);
	setup_sim_args(sim, av);
	if (!sim->args || sim->valid != VALID)
		return (exit_cleanup(sim, "Failed sim->args setup", EXIT_FAILURE));
	if (mise_en_place(sim) != VALID || sim->valid != VALID)
		return (exit_cleanup(sim, "Failed mise en place", EXIT_FAILURE));
	if (set_table(sim) != VALID || sim->valid != VALID)
		return (exit_cleanup(sim, "Failed setting table", EXIT_FAILURE));
	sim->valid = VALID;
	if (start_dinner(sim) != VALID)
		return (exit_cleanup(sim, "Dinner couldn't start", EXIT_FAILURE));
	monitor_dinner(sim);
	return (exit_cleanup(sim, NULL, EXIT_SUCCESS));
}
