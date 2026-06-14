/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 18:27:10 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/06/14 17:39:43 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	isdigit_str(char *s)
{
	int	i;

	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (ft_isdigit(s[i]))
	{
		while (s[i])
		{
			if (ft_isdigit(s[i]))
				i++;
			else
				break ;
		}
	}
	else
		return (0);
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == 0)
		return (1);
	return (0);
}
