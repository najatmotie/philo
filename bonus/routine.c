/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:45 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/03 17:47:03 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_philos(t_data data, pid_t *philos)
{
	int i = 0;
	while(i < data.philo_nb)
	{
		kill(philos[i], SIGKILL);
		i++;
	}
}

int 	meals_reached(t_data *data)
{
	int i = 0;
	int count = 0;
	while(i < data->philo_nb)
	{
		if (data[i].args.time_must_eat != 0
			&& data[i].eat_count >= data[i].args.time_must_eat)
			count++;
		i++;
	}
	if(count == data->philo_nb)
		return(1);
	else
		return(0);
}

void	printing_(t_data *data, char *s)
{
	printf("%ld %d %s\n", get_timestamp_in_ms(data->start_time),
			data->philo_id, s);
}

void	death_monitor(t_data *data, pid_t *philos)
{
	int	i;
	
	while (1)
	{
		i = 0;
		while (i < data->philo_nb)
		{
			if(meals_reached(data))
				return ;
			if (get_timestamp_in_ms(data[i].start_time)
				- data[i].last_meal_time >= data[i].args.time_to_die)
			{
				data[i].still_alive = 1;
				printf("%ld %d died\n", get_timestamp_in_ms(data[i].start_time),
						data[i].philo_id);
				kill_philos(*data, philos);
				return ;
			}
			i++;
		}
	}
}

void	eating_(t_data *data, sem_t	*forks)
{
	sem_wait(forks);
	printing_(data, "has taken a fork");
	if (data->philo_nb == 1)
	{
		sem_post(forks);
		data->still_alive = 1;
		exit(0);
	}
	else
	{
		sem_wait(forks);
		printing_(data, "has taken a fork");
		printing_(data, "is eating");
		usleep(data->args.time_to_eat * 1000); 
		data->eat_count = data->eat_count + 1;
		data->last_meal_time = get_timestamp_in_ms(data->start_time); 
		sem_post(forks);
		sem_post(forks);
	}
}

void	*philo_routine(t_data *data, sem_t	*forks)
{

	if (data->philo_id % 2 == 0)
	{
		printing_(data, "is sleeping");
		usleep(data->args.time_to_sleep * 1000);
	}
	while (1)
	{
		printing_(data, "is thinking");
		eating_(data, forks);
		printing_(data, "is sleeping");
		usleep(data->args.time_to_sleep * 1000);
		if (data->args.time_must_eat != 0 && data->eat_count >= data->args.time_must_eat)
			break ;
	}
	return (NULL);
}
