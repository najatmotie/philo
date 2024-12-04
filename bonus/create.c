/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:30 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/03 15:54:56 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_philos(t_data *data, sem_t	*forks)
{
	int	i;
	int	j;
	i = 0;
	j = 1;
	int philos[data->philo_nb];
	
	while(i < data->philo_nb)
	{
		
		philos[i] = fork();
		if(philos[i] == 0)
			philo_routine(data, forks);
		i++;
	}
	i = 0;
	while(i < data->philo_nb)
	{
		waitpid(philos[i], NULL, 0);
		i++;
	}
}
