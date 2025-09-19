/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:20:51 by giomastr          #+#    #+#             */
/*   Updated: 2025/09/18 18:45:43 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_slate(t_rules *table)
{
	free(table->philos);
	free(table->monitor);
	free(table->forks);
}

void	err_ex(char *s)
{
	ft_putstr_fd(s, 2);
	exit(EXIT_FAILURE);
}

void	mutex_killer(t_rules *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->stop_mutex);
}
