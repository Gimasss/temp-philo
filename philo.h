/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:00:44 by giomastr          #+#    #+#             */
/*   Updated: 2025/09/18 18:45:52 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_PHILO 200
# define ERR_MESS "ERROR"

//********STRUCTS*********/

typedef struct s_rules	t_rules;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	int				left_fork_idx;
	int				right_fork_idx;
	bool			survived;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	t_rules			*rules;
}	t_philo;

struct s_rules
{
	int				n_meals;
	int				n_philos;
	int				n_survivors;
	long			tt_die;
	long			tt_sleep;
	long			tt_eat;
	int				stop;
	int				full;
	long			start_lunch;
	t_philo			*philos;
	pthread_t		*monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
};

// initialise and parse in main
void	init_forks(t_rules *table);
void	init_philo(t_rules *table);
void	stamp_handler(t_philo *phi, char *s);
void	check_and_save(int argc, char *argv[], t_rules *rules);

//routine
void	*philo_routine(void *arg);
void	grabs_fork(t_philo *phi);
void	thinks(t_philo *phi);
void	eats(t_philo *phi);
void	sleeps(t_philo *phi);

//TIME
long	now_ms(void);
void	ft_usleep_interrupt(long ms, t_philo *phi);

// monitor
void	*monitor_routine(void *arg);
int		sad_philo(t_rules *table);

// checks
void	is_dead(t_philo *phi);
int		end_dinner(t_philo *phi);
int		ru_full_yet(t_philo *phi);
int		ru_dead_yet(t_philo *phi);

//utils
void	create_thread(t_rules *table);
bool	check_status(t_philo *phi);
bool	isitdigit(int n);
size_t	ft_strlen(const char *s);
int		ft_putstr_fd(const char *s, int fd);
int		parse_atoi(const char *str);
int		synt_check(const char *str);

//cleaner
void	clean_slate(t_rules *table);
void	mutex_killer(t_rules *table);
void	err_ex(char *s);

#endif
