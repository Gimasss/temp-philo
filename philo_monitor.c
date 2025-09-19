/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:38:01 by giomastr          #+#    #+#             */
/*   Updated: 2025/09/19 13:01:08 by giomastr         ###   ########.fr       */
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

int	get_n_survivors(t_rules *table)
{
	int	res;

	pthread_mutex_lock(&table->stop_mutex);
	res = table->n_survivors;
	pthread_mutex_unlock(&table->stop_mutex);
	return (res);
}

void	*monitor_routine(void *arg)
{
	int		i;
	int		time;
	t_rules	*table;

	i = 0;
	table = (t_rules *)arg;
	while (i < table->n_philos && get_n_survivors(table) < table->n_philos)
	{
		if (ru_dead_yet(&table->philos[i]))
		{
			time = now_ms() - table->start_lunch;
			pthread_mutex_lock(&table->print_mutex);
			pthread_mutex_lock(&table->stop_mutex);
			printf("%d %d died\n", time, table->stop);
			pthread_mutex_unlock(&table->stop_mutex);
			pthread_mutex_unlock(&table->print_mutex);
			break ;
		}
		i++;
		if (i == table->n_philos)
			i = 0;
		usleep(1);
	}
	return (NULL);
}
