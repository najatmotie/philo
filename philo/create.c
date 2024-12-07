/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:30 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/06 18:29:59 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_data *data, pthread_t *philos,
		pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		data[i].left_fork = &forks[i];
		data[i].right_fork = &forks[(i + 1) % data->philo_nb];
		if (pthread_create(&philos[i], NULL, &philo_routine, &data[i]) != 0)
		{
			*data->error_occured = 1;
			printf("failed to create thread %d\n", data[i].philo_id);
			return ;
		}
		i++;
	}
}

void	join_threads(t_data data, pthread_t *philos)
{
	int	i;

	i = 0;
	while (i < data.philo_nb)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
}
