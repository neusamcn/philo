/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 19:49:40 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/06/13 22:48:17 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	ft_putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(int fd, char *s)
{
	int	i;

	i = 0;
	while (s[i])
		ft_putchar_fd(fd, s[i++]);
}

void	ft_puts_fd(int fd, char *s)
{
	ft_putstr_fd(fd, s);
	ft_putchar_fd(fd, '\n');
}
