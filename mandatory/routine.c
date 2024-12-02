/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:45 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/01 19:22:56 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printing_(t_data *data, char *s)
{
	pthread_mutex_lock(data->lock);
	if (*data->still_alive != 1)
		printf("%ld %d %s\n", get_timestamp_in_ms(data->start_time),
				data->philo_id, s);
	pthread_mutex_unlock(data->lock);
}

void	death_monitor(t_data *data)
{
	int	i;
	
	while (1)
	{
		i = 0;
		while (i < data->philo_nb)
		{
			pthread_mutex_lock(data[i].lock);
			if (data[i].args.time_must_eat != 0
				&& *(data[i].eat_count) >= data[i].args.time_must_eat
				* data[i].philo_nb)
			{
				pthread_mutex_unlock(data[i].lock);
				return ;
			}
			if (get_timestamp_in_ms(data[i].start_time)
				- data[i].last_meal_time >= data[i].args.time_to_die)
			{
				*data[i].still_alive = 1;
				pthread_mutex_unlock(data[i].lock);
				printf("%ld %d died\n", get_timestamp_in_ms(data[i].start_time),
						data[i].philo_id);
				return ;
			}
			pthread_mutex_unlock(data[i].lock);
			i++;
		}
	}
}

void	eating_(t_data *data)
{
	pthread_mutex_lock(data->left_fork);
	printing_(data, "has taken a fork");
	if (data->philo_nb == 1)
	{
		pthread_mutex_unlock(data->left_fork);
		*data->still_alive = 1;
		return ;
	}
	pthread_mutex_lock(data->right_fork);
	printing_(data, "has taken a fork");
	printing_(data, "is eating");
	ft_usleep(data->args.time_to_eat);
	pthread_mutex_lock(data->lock);
	*data->eat_count = *data->eat_count + 1;
	data->last_meal_time = get_timestamp_in_ms(data->start_time);
	pthread_mutex_unlock(data->lock);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
}

void	*philo_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (data->philo_id % 2 == 0)
	{
		printing_(data, "is sleeping");
		ft_usleep(data->args.time_to_sleep);
	}
	while (1)
	{
		pthread_mutex_lock(data->lock);
		if(*data->still_alive)
		{
			pthread_mutex_unlock(data->lock);
			break;
		}
		pthread_mutex_unlock(data->lock);
		printing_(data, "is thinking");
		eating_(data);
		printing_(data, "is sleeping");
		ft_usleep(data->args.time_to_sleep);
		pthread_mutex_lock(data->lock);
		if (data->args.time_must_eat != 0
			&& *(data->eat_count) >= data->args.time_must_eat * data->philo_nb)
		{
			pthread_mutex_unlock(data->lock);
			break ;
		}
		pthread_mutex_unlock(data->lock);
	}
	return (NULL);
}
