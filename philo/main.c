/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:15 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/07 14:15:14 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data			*data;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	pthread_t		*philos;

	if (check_errors(av, ac))
		return (1);
	data = malloc(ft_atoi(av[1]) * sizeof(t_data));
	forks = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	philos = malloc(ft_atoi(av[1]) * sizeof(pthread_t));
	init_philos(data, &mutex, av, ac);
	if (!init_mutexes(data, forks, &mutex))
	{
		free_ressources(data, forks, philos);
		destroy_mutexes(*data, forks, &mutex);
		return (1);
	}
	create_threads(data, philos, forks);
	death_monitor(data);
	join_threads(*data, philos);
	free_ressources(data, forks, philos);
	destroy_mutexes(*data, forks, &mutex);
	return (0);
}
