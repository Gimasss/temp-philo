/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:10:52 by giomastr          #+#    #+#             */
/*   Updated: 2025/09/18 18:46:08 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_status(t_philo *phi)
{
	thinks(phi);
	if (end_dinner(phi) == 1)
		return (true);
	grabs_fork(phi);
	if (end_dinner(phi) == 1)
	{
		pthread_mutex_unlock(&phi->rules->forks[phi->left_fork_idx]);
		pthread_mutex_unlock(&phi->rules->forks[phi->right_fork_idx]);
		return (true);
	}
	eats(phi);
	if (end_dinner(phi) == 1)
		return (true);
	if (ru_full_yet(phi) == 1)
		return (true);
	sleeps(phi);
	if (end_dinner(phi) == 1)
		return (true);
	return (false);
}

void	is_dead(t_philo *phi)
{
	if (ru_dead_yet(phi))
	{
		pthread_mutex_lock(&phi->rules->stop_mutex);
		phi->rules->stop = phi->id;
		pthread_mutex_unlock(&phi->rules->stop_mutex);
	}
}

int	end_dinner(t_philo *phi)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&phi->rules->stop_mutex);
	if (phi->rules->stop != 0)
		result = 1;
	pthread_mutex_unlock(&phi->rules->stop_mutex);
	return (result);
}

int	ru_dead_yet(t_philo *phi)
{
	int		dead;
	long	time_from_lm;
	bool	survived;

	dead = 0;
	survived = false;
	pthread_mutex_lock(&phi->meal_mutex);
	time_from_lm = now_ms() - phi->last_meal;
	if (phi->rules->n_meals != -1 && phi->meals_eaten
		>= phi->rules->n_meals && !phi->survived)
	{
		phi->rules->n_survivors++;
		phi->survived = true;
	}
	pthread_mutex_unlock(&phi->meal_mutex);
	pthread_mutex_lock(&phi->rules->stop_mutex);
	if (time_from_lm > phi->rules->tt_die && !phi->survived)
	{
		phi->rules->stop = phi->id;
		dead = 1;
	}
	pthread_mutex_unlock(&phi->rules->stop_mutex);
	return (dead);
}

int	ru_full_yet(t_philo *phi)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	pthread_mutex_lock(&phi->meal_mutex);
	if (phi->rules->n_meals > 0 && phi->meals_eaten >= phi->rules->n_meals)
		full = 1;
	pthread_mutex_unlock(&phi->meal_mutex);
	return (full);
}
