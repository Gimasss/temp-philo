/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:00:50 by giomastr          #+#    #+#             */
/*   Updated: 2025/09/17 15:36:45 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(t_rules *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		table->philos[i].last_meal = table->start_lunch;
		pthread_create(&table->philos[i].thread, NULL,
			philo_routine, &table->philos[i]);
		i++;
	}
}

bool	isitdigit(int n)
{
	return (n >= '0' && n <= '9');
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_putstr_fd(const char *s, int fd)
{
	if (!s)
		return (write(fd, "(null)", 6));
	return (write(fd, s, ft_strlen(s)));
}

int	synt_check(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-' || isitdigit(str[i]))
		{
			if (str[i] == '-')
				return (0);
		}
		if (!isitdigit(str[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}
