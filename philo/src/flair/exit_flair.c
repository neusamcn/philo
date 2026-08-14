/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_flair.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 10:58:42 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/14 11:01:12 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	exit_msg(char *out_msg, char *err_msg, t_sim *sim, int exit_status)
{
	if (FLAIR == ON)
	{
		printf(ERR"%s\nSee "CLR_RST, out_msg);
		printf("<project root>/README.md");
		printf(ERR" for instructions.\n"CLR_RST);
	}
	if (out_msg && !err_msg)
		err_msg = out_msg;
	return (exit_cleanup(sim, err_msg, exit_status));
}
