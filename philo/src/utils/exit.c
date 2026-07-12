/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:47:12 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/07/12 22:04:05 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

//  TODO: test threads cleanup
int	exit_cleanup(t_philo *philo, char *err_msg, int exit_status)
{
	int	i;

	if (philo)
	{
		if (philo->args)
			free(philo->args);
		if (philo->pt_ids)
		{
			i = 0;
			while (philo->pt_ids[i])
				free(philo->pt_ids[i++]);
			free(philo->pt_ids[i]);
			free(philo->pt_ids);
		}
		free(philo);
	}
	if (err_msg)
		ft_putstr_fd(STDERR_FILENO, err_msg);
	return (exit_status);
}

int	exit_msg(char *out_msg, char *err_msg, t_philo *philo, int exit_status)
{
	printf(ERR"%s\nSee "COLOR_RESET, out_msg);
	printf("<project root>/README.md");
	printf(ERR" for instructions.\n"COLOR_RESET);
	return (exit_cleanup(philo, err_msg, exit_status));
}
