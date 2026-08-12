/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 13:37:18 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/08/12 17:48:51 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <unistd.h>

int64_t   time_in_ms(void)
{
    struct timeval  tv;
    int64_t         time_ms;

    if (gettimeofday(&tv, NULL))
        return (TIME_ERR);
    time_ms = (int64_t)tv.tv_sec * INT64_C(1000)
        + (int64_t)tv.tv_usec / INT64_C(1000);
    return (time_ms);
}

void    usleep_precise(int64_t t_ms, t_table *tbl)
{
    int64_t t_end_ms;

    t_end_ms = time_in_ms() + t_ms;
    while (time_in_ms() < t_end_ms)
    {
        usleep(100);
        if (dinner_is_over(tbl) == true)
            break ;
        usleep(100);
    }
}
