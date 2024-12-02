/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:19 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/01 21:54:11 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
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
	long			last_meal_time;
	struct timeval	start_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*lock;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	alive_mutex;
	t_args			args;
}					t_data;

int					ft_atoi(const char *str);
int					check_errors(char **av, int ac);
long				get_timestamp_in_ms(struct timeval start_time);
void				ft_usleep(useconds_t time);
void				init_philos(t_data *data, char **av, int ac);
void				init_mutex(t_data *data, pthread_mutex_t *forks);
void 				create_threads(t_data *data, pthread_t *philos,
						pthread_mutex_t *forks, pthread_mutex_t	*mutex);
void				*philo_routine(void *arg);
void				death_monitor(t_data *data);
void				destroy_mutex(t_data *data, pthread_mutex_t *forks, pthread_mutex_t *mutex);
void				join_threads(t_data *data, pthread_t *philos);