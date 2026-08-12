/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:59:23 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/12 16:27:20 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

// TODO: REMOVE TESTER
// volatile sig_atomic_t	g_stop = 0;
//
// static void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	g_stop = 1;
// }

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

// TODO: update according to new structure
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
// TODO: DELETE TESTER
// static void	print_table(t_table *tbl)
// {
// 	t_philo	*p;
//
//	p = tbl->philo_turn;
//	while (p)
//	{
//		printf("philo_id: %d\n", p->philo_id);
//		// printf("thread_id: %ld\n", p->thread_id);
//		printf("has_tkn: %d\n", p->has_tkn);
//		printf("meals: %d\n", p->meals);
//		if (p->next)
//			printf("next philo_id: %d\n", p->next->philo_id);
//		if (p->previous)
//			printf("previous philo_id: %d\n", p->previous->philo_id);
//		p = p->next;
//		if (p == tbl->philo_turn)
//			break ;
//	}
// }

static bool	philo_dead(t_sim *sim)
{

}

static bool	philos_sated(t_sim *sim)
{
	t_philo	*curr_p;
	int		start;

	if (sim->args->n_eats_x_philo == 0)
		return (false);
	curr_p = *sim->table->philo_head;
	start = 1;
	while (curr_p != *sim->table->philo_head)
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

// TODO: create validation functions(s)?
int	main(int ac, char **av)
{
	t_sim	*sim;

	// signal(SIGINT, handle_sigint); // TODO: REMOVE TESTER
	sim = NULL;
	if (ac < 5 || ac > 6 || validate_args(av) != VALID)
		return (exit_msg("Incorrect arguments.", NULL, sim, EXIT_FAILURE));
	sim = ft_calloc(1, sizeof(t_sim));
	if (!sim)
		return (exit_cleanup(sim, "Simulation ft_calloc()", EXIT_FAILURE));
	setup_sim_args(sim, av);
	if (!sim->args || sim->valid != VALID)
		return (exit_cleanup(sim, "Failed sim->args setup", EXIT_FAILURE));
	mise_en_place(sim);
	if (!sim->pass || sim->valid != VALID
		|| (sim->pass && sim->pass->valid != VALID))
		return (exit_cleanup(sim, "Failed mise en place", EXIT_FAILURE));
	set_table(sim);
	if (!sim->table || sim->valid != VALID
		|| (sim->table && (sim->table->valid != VALID || (*sim->table->philo_head)->philo_id != 1)))
		return (exit_cleanup(sim, "Failed setting table", EXIT_FAILURE));
	// print_table(sim->table); // TODO: DELETE TESTER
	// TODO: DELETE TESTER
	// print_p_struct(table);
	// TODO: philos' stuff
	pthread_mutex_init(&sim->print_log, NULL);
	pthread_mutex_init(&sim->end_sim, NULL);
	sim->valid = VALID;
	if (start_dinner(sim) != VALID)
		return (exit_cleanup(sim, "Dinner couldn't start", EXIT_FAILURE));
	monitor_dinner(sim);
	return (exit_cleanup(sim, NULL, EXIT_SUCCESS));
}
