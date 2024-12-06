/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:23 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/06 13:07:01 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	shared_data(t_data *data, pthread_mutex_t *mutex)
{
	int	i;
	int	*p1;
	int	*p2;
	int	*p3;

	i = 0;
	p1 = malloc(sizeof(int));
	*p1 = 0;
	p2 = malloc(sizeof(int));
	*p2 = 0;
	p3 = malloc(sizeof(int));
	*p3 = 0;
	while (i < data->philo_nb)
	{
		data[i].eat_count = p1;
		data[i].still_alive = p2;
		data[i].error_occured = p3;
		data[i].multi_lock = mutex;
		i++;
	}
}

void	set_values(t_data *data, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		data[i].args.time_must_eat = 0;
		data[i].philo_nb = ft_atoi(av[1]);
		data[i].philo_id = i + 1;
		data[i].args.time_to_die = ft_atoi(av[2]);
		data[i].args.time_to_eat = ft_atoi(av[3]);
		data[i].args.time_to_sleep = ft_atoi(av[4]);
		gettimeofday(&data[i].start_time, NULL);
		data[i].last_meal_time = get_timestamp_in_ms(data[i].start_time);
		i++;
	}
}

void	init_philos(t_data *data, pthread_mutex_t *mutex, char **av, int ac)
{
	int	i;

	i = 0;
	set_values(data, av);
	shared_data(data, mutex);
	if (ac == 6)
	{
		while (i < ft_atoi(av[1]))
		{
			data[i].args.time_must_eat = ft_atoi(av[5]);
			i++;
		}
	}
}

int	init_mutexes(t_data *data, pthread_mutex_t *forks, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		printf("failed to init mutex of lock\n");
		return (0);
	}
	while (i < data->philo_nb)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			printf("failed to init mutex of fork number %d\n", data->philo_id);
			return (0);
		}
		i++;
	}
	return (1);
}

void	destroy_mutexes(t_data *data, pthread_mutex_t *forks,
		pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(mutex);
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
