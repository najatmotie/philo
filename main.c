/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:15 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/06 13:07:16 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_ressources(t_data *data, pthread_mutex_t *forks, pthread_t *philos)
{
	free(forks);
	free(philos);
	free(data->eat_count);
	free(data->still_alive);
	free(data->error_occured);
	free(data);
}

int	main(int ac, char **av)
{
	t_data			*data;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
	int				created_number;

	created_number = 0;
	if (check_errors(av, ac))
		return (1);
	data = malloc(ft_atoi(av[1]) * sizeof(t_data));
	philos = malloc(ft_atoi(av[1]) * sizeof(pthread_t));
	forks = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	init_philos(data, &mutex, av, ac);
	if (!init_mutexes(data, forks, &mutex))
	{
		free_ressources(data, forks, philos);
		return (1);
	}
	create_threads(data, philos, forks, &created_number);
	death_monitor(data);
	join_threads(philos, &created_number);
	destroy_mutexes(data, forks, &mutex);
	free_ressources(data, forks, philos);
}
