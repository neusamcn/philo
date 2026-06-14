/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 19:46:00 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/06/14 18:17:36 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
	s = (void *)ptr;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	flowcheck;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(0);
		return (ptr);
	}
	flowcheck = nmemb * size;
	if (flowcheck / nmemb == size)
	{
		ptr = malloc(nmemb * size);
		if (ptr == NULL)
			return (NULL);
		ft_bzero(ptr, size * nmemb);
		return (ptr);
	}
	return (NULL);
}
// TODO: create error handling wrapper?
