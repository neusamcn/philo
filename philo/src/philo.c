/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:59:23 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/10 20:07:27 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
				return (0);
		}
		else if (!(isdigit_str(av[i]))
			|| ft_atol(av[i]) < 0 || ft_atol(av[i]) > INT_MAX)
			return (0);
		i++;
	}
	return (1);
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

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	// signal(SIGINT, handle_sigint); // TODO: REMOVE TESTER
	if (ac < 5 || ac > 6 || !(validate_args(av)))
		return (exit_msg("Incorrect arguments.", NULL, table, EXIT_FAILURE));
	table = set_table(table, av);
	// print_table(table); // TODO: DELETE TESTER
	if (!table || (table && table->valid != VALID))
		return (exit_cleanup(table, "setting table", EXIT_FAILURE));
	// TODO: DELETE TESTER
	// print_p_struct(table);
	// TODO: philos' stuff
	run_philo_sim(table);
	return (exit_cleanup(table, NULL, EXIT_SUCCESS));
}
