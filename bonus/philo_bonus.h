/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:19 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/03 15:57:01 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <semaphore.h>

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
	int				eat_count;
	int				still_alive;
	long			last_meal_time;
	sem_t			*sem_lock;
	sem_t			*forks;
	sem_t	*left_fork;
	sem_t	*right_fork;
	struct timeval	start_time;
	t_args			args;
}					t_data;

int					ft_atoi(const char *str);
char				*ft_itoa(int n);
char				*ft_strjoin(char *s1, char *s2);
int					check_errors(char **av, int ac);
void				init_philos(t_data *data, char **av, int ac);
long				get_timestamp_in_ms(struct timeval start_time);
void				ft_usleep(useconds_t time);
void				create_philos(t_data *data, sem_t	*forks);
void	*philo_routine(t_data *data, sem_t	*forks);
void	death_monitor(t_data *data, pid_t *philos);