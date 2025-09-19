/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:38:01 by giomastr          #+#    #+#             */
/*   Updated: 2025/09/18 11:56:01 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sad_philo(t_rules *table)
{
	if (table->n_philos == 1)
	{
		printf("%d 1 has taken a fork\n", 0);
		printf("%d 1 died\n", (int)table->tt_die);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	int		i;
	int		j;
	int		time;
	t_rules	*table;

	i = 0;
	table = (t_rules *)arg;
	while (table->n_survivors < table->n_philos)
	{
		if (ru_dead_yet(&table->philos[i]))
		{
			j = 0;
			time = now_ms() - table->start_lunch;
			printf("%d %d died\n", time, table->stop);
			break ;
		}
		i++;
		if (i == table->n_philos)
			i = 0;
		usleep(1);
	}
	return (NULL);
}
