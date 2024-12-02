/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:30 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/01 21:55:11 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_data *data, pthread_t *philos, pthread_mutex_t *forks, pthread_mutex_t	*mutex)
{
	int	i;
	int	j;
	i = 0;
	j = 1;
	while (i < data->philo_nb)
	{
		data[i].left_fork = &forks[i];
		data[i].right_fork = &forks[(i + 1) % data->philo_nb];
		data[i].lock = mutex;
		// printf("-->lock: %p mutex: %p i : %d\n", data[i].lock, mutex, i);
		pthread_create(&philos[i], NULL, &philo_routine, &data[i]);
		i += 2;
	}
	while (j < data->philo_nb)
	{
		data[j].left_fork = &forks[j];
		data[j].right_fork = &forks[(j + 1) % data->philo_nb];
		data[j].lock = mutex;
		// printf("-->lock: %p mutex: %p i : %d\n", data[i].lock, mutex, i);
		pthread_create(&philos[j], NULL, &philo_routine, &data[j]);
		j += 2;
	}
}

void	join_threads(t_data *data, pthread_t *philos)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
}
