/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flair.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 11:06:30 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/14 20:47:17 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	print_philos(t_sim_args *sim_args)
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

void	welcome_msg(void)
{
	printf("\nWelcome to " ITALIC DEEP_PINK" The Restaur" CLR_RST LIGHT_PINK"4"
		CLR_RST DEEP_PINK "n" CLR_RST LIGHT_PINK"2" CLR_RST FMT_RST "...\n");
	printf("Where " PLUM "philosophers" CLR_RST " come to dine");
	printf(" succulent chinese meals until they're ");
	printf(LIGHT_PINK "satisfied" CLR_RST " or... ");
	printf(BLUE_VIOLET "dead" CLR_RST "!\nEnjoy!\n\n");
}
