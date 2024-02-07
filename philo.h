/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:46:30 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/05 10:52:05 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data	t_data;

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	TAKE_RIGHT_FORK,
	TAKE_LEFT_FORK,
	DIED,
}		t_status;

typedef enum e_mutexcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
}		t_mutexcode;

typedef enum e_threadcode
{
	CREATE,
	DETACH,
	JOIN,
}		t_threadcode;

typedef enum e_time_code
{
	SECONDS,
	MILLISECOND,
	MICROSECOND,
}		t_time_code;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}		t_fork;

typedef struct s_philo
{
	int				id;
	long			nb_meal;
	bool			full;
	long			t_last_meal;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
	pthread_mutex_t	mutex_philo;
	t_data			*data;
}		t_philo;

struct s_data
{
	long			nb_philo;
	long			t_eat;
	long			t_sleep;
	long			t_die;
	long			nb_max_meal;
	long			time_start;
	long			nb_thread_run;
	bool			end_simulation;
	bool			all_thread_ready;
	pthread_t		monitor;
	pthread_mutex_t	mutex_data;
	pthread_mutex_t	mutex_write;
	t_fork			*fork;
	t_philo			*philo;
};

//Utils
void	error(char *str);
long	ft_atol(const char *s);
long	gettime(long time_code);
void	precise_usleep(long usec, t_data *data);
void	de_synchronize_philos(t_philo *philo);

//Parsing
bool	is_space(char c);
bool	is_digit(char c);
char	*valid_input(char *str);
void	parsing(t_data *data, char **av);

//Init
void	init(t_data *data);
void	wait_all_threads(t_data *data);
void	simulation(t_data *data);
void	increase_long(pthread_mutex_t *mutex, long *value);
bool	all_thread_run(pthread_mutex_t *mutex, long *thread, long philo_nb);
void	*monitor_diner(void *value);
void	think(t_philo *philo, bool odd_philo);

//Safe Function
void	*safe_malloc(unsigned int bytes);
void	safe_mutex(pthread_mutex_t *mutex, t_mutexcode mutex_code);
void	safe_thread(pthread_t *thread, void *(*foo)(void *), void *data,
			t_threadcode thread_code);

//Setters Getters
bool	simulation_finish(t_data *data);
long	get_long(pthread_mutex_t *mutex, long *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);

//Other
void	write_status(t_status status, t_philo *philo);
void	clean(t_data *data);

#endif