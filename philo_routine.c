/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:00:59 by giomastr          #+#    #+#             */
/*   Updated: 2025/09/18 11:55:18 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eats(t_philo *phi)
{
	pthread_mutex_lock(&phi->meal_mutex);
	phi->last_meal = now_ms();
	phi->meals_eaten++;
	pthread_mutex_unlock(&phi->meal_mutex);
	stamp_handler(phi, "is eating");
	ft_usleep_interrupt(phi->rules->tt_eat, phi);
	pthread_mutex_unlock(&phi->rules->forks[phi->right_fork_idx]);
	pthread_mutex_unlock(&phi->rules->forks[phi->left_fork_idx]);
}

void	sleeps(t_philo *phi)
{
	stamp_handler(phi, "is sleeping");
	ft_usleep_interrupt(phi->rules->tt_sleep, phi);
}

void	thinks(t_philo *phi)
{
	stamp_handler(phi, "is thinking");
}

void	grabs_fork(t_philo *phi)
{
	pthread_mutex_lock(&phi->rules->forks[phi->left_fork_idx]);
	stamp_handler(phi, "has taken a fork");
	pthread_mutex_lock(&phi->rules->forks[phi->right_fork_idx]);
	stamp_handler(phi, "has taken another fork");
}

void	*philo_routine(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	if (phi->id % 2 == 0)
		usleep(50);
	while (check_status(phi) == false)
		;
	return (NULL);
}
