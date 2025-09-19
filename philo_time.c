/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:00:41 by giomastr          #+#    #+#             */
/*   Updated: 2025/09/18 11:56:29 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep_interrupt(long ms, t_philo *phi)
{
	long	start;

	start = now_ms();
	while (now_ms() - start < ms)
	{
		usleep(1000);
		if (ru_dead_yet(phi))
			break ;
	}
}

long	now_ms(void)
{
	struct timeval	time;

	time = (struct timeval){0};
	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000L) + (time.tv_usec / 1000L));
}
