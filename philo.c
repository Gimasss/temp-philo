/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:56:36 by giomastr          #+#    #+#             */
/*   Updated: 2025/09/18 18:46:11 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stamp_handler(t_philo *phi, char *s)
{
	int	time;

	time = now_ms() - phi->rules->start_lunch;
	pthread_mutex_lock(&phi->rules->print_mutex);
	pthread_mutex_lock(&phi->rules->stop_mutex);
	if (phi->rules->stop == 0)
		printf("%d %d %s\n", time, phi->id, s);
	pthread_mutex_unlock(&phi->rules->print_mutex);
	pthread_mutex_unlock(&phi->rules->stop_mutex);
}

void	init_philo(t_rules *table)
{
	int	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->n_philos);
	if (!table->philos)
		err_ex("Malloc failed for philosophers");
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->stop_mutex, NULL);
	while (i < table->n_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal = 0;
		table->philos[i].left_fork_idx = i;
		table->philos[i].right_fork_idx = (i + 1) % table->n_philos;
		if (i == table->n_philos - 1)
			table->philos[i].left_fork_idx = table->philos[i].right_fork_idx;
		if (i == table->n_philos - 1)
			table->philos[i].right_fork_idx = i;
		table->philos[i].rules = table;
		table->philos[i].survived = false;
		pthread_mutex_init(&table->philos[i].meal_mutex, NULL);
		i++;
	}
}

void	init_forks(t_rules *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philos);
	if (!table->forks)
		err_ex("Malloc failed for forks");
	while (i < table->n_philos)
	{
		table->forks[i] = (pthread_mutex_t){0};
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	table->stop = 0;
	table->n_survivors = 0;
}

void	check_and_save(int argc, char *argv[], t_rules *rules)
{
	int	i;
	int	nbr;

	i = 1;
	while (i < argc)
	{
		if (synt_check(argv[i]) == 0)
			err_ex("Syntax Error: shite");
		nbr = parse_atoi(argv[i]);
		if (nbr == 0)
			err_ex("Parse Error: shite");
		i++;
	}
	rules->n_philos = parse_atoi(argv[1]);
	rules->tt_die = parse_atoi(argv[2]);
	rules->tt_eat = parse_atoi(argv[3]);
	rules->tt_sleep = parse_atoi(argv[4]);
	if (argv[5] != NULL)
		rules->n_meals = parse_atoi(argv[5]);
	else
		rules->n_meals = -1;
}

int	main(int argc, char *argv[])
{
	t_rules	table;
	int		i;

	if (argc < 5 || argc > 6)
		err_ex("Fix arg count, it's wrong\n");
	check_and_save(argc, argv, &table);
	if (sad_philo(&table))
		return (0);
	init_forks(&table);
	init_philo(&table);
	table.start_lunch = now_ms();
	create_thread(&table);
	table.monitor = malloc(sizeof(t_philo));
	monitor_routine(&table);
	i = -1;
	while (++i < table.n_philos)
	{
		pthread_join(table.philos[i].thread, NULL);
	}
	mutex_killer(&table);
	clean_slate(&table);
	return (0);
}
