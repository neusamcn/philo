/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:59:23 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/13 23:53:40 by ncruz-ne         ###   ########.fr       */
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
				return (ARGS_ERR);
		}
		else if (!(isdigit_str(av[i]))
			|| ft_atol(av[i]) < 0 || ft_atol(av[i]) > INT_MAX)
			return (ARGS_ERR);
		i++;
	}
	return (VALID);
}

static bool	philo_dead(t_sim *sim)
{
	t_philo	*curr_p;
	int		start;
	int64_t	t_since_last_meal;

	curr_p = *sim->table->philo_head;
	start = 1;
	while (curr_p && (start || curr_p != *sim->table->philo_head))
	{
		start = 0;
		t_since_last_meal = time_in_ms() - curr_p->t_last_meal;
		if (t_since_last_meal >= sim->args->t_die)
		{
			state_log(curr_p, "died", "");
			update_end_dinner_status(sim->table, true);
			return (true);
		}
		curr_p = curr_p->next;
	}
	return (false);
}

static bool	philos_sated(t_sim *sim)
{
	t_philo	*curr_p;
	int		start;

	if (sim->args->n_eats_x_philo == 0)
		return (false);
	curr_p = *sim->table->philo_head;
	start = 1;
	while (curr_p && (start || curr_p != *sim->table->philo_head))
	{
		start = 0;
		if (curr_p->meals < sim->args->n_eats_x_philo)
			return (false);
		curr_p = curr_p->next;
	}
	update_end_dinner_status(sim->table, true);
	return (true);
}

static void	monitor_dinner(t_sim *sim)
{
	bool	dinner_ended;

	dinner_ended = false;
	while (dinner_ended == false)
	{
		pthread_mutex_lock(&sim->pass->run_dish);
		if (philo_dead(sim) == true || philos_sated(sim) == true)
			dinner_ended = true;
		pthread_mutex_unlock(&sim->pass->run_dish);
		usleep(1);
	}
}

int	main(int ac, char **av)
{
	t_sim	*sim;

	sim = NULL;
	if (ac < 5 || ac > 6 || validate_args(av) != VALID)
		return (exit_msg("Incorrect arguments.", NULL, sim, EXIT_FAILURE));
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
