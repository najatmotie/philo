/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:19 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/07 14:12:03 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_args
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_must_eat;
}					t_args;

typedef struct s_data
{
	int				philo_nb;
	int				philo_id;
	int				*eat_count;
	int				*still_alive;
	int				*error_occured;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*multi_lock;
	struct timeval	start_time;
	t_args			args;
	long			last_meal_time;
}					t_data;

int					ft_atoi(const char *str);
void				printing_(t_data *data, char *s);
void				free_ressources(t_data *data, pthread_mutex_t *forks,
						pthread_t *philos);
int					check_errors(char **av, int ac);
long				get_timestamp_in_ms(struct timeval start_time);
void				ft_usleep(useconds_t time);
void				init_philos(t_data *data, pthread_mutex_t *mutex, char **av,
						int ac);
int					init_mutexes(t_data *data, pthread_mutex_t *forks,
						pthread_mutex_t *mutex);
void				create_threads(t_data *data, pthread_t *philos,
						pthread_mutex_t *forks);
void				*philo_routine(void *arg);
void				death_monitor(t_data *data);
void				join_threads(t_data data, pthread_t *philos);
void				destroy_mutexes(t_data data, pthread_mutex_t *forks,
						pthread_mutex_t *mutex);