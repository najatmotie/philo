/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:45 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/03 13:04:10 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_lock(data->right_fork);
	printing_(data, "has taken a fork");
	pthread_mutex_unlock(data->right_fork);
	printing_(data, "is eating");
	ft_usleep(data->args.time_to_eat);
	pthread_mutex_lock(data->lock);
	*data->eat_count = *data->eat_count + 1;
	data->last_meal_time = get_timestamp_in_ms(data->start_time);
	pthread_mutex_unlock(data->lock);
}

void	simulation_routine(t_data *data)
{
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
	simulation_routine(data);
	return (NULL);
}
