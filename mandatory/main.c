/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:15 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/01 21:55:45 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_ressources(t_data *data, pthread_t *philos, pthread_mutex_t *forks)
{
	free(philos);
	free(forks);
	free(data->eat_count);
	free(data->still_alive);
	free(data);
}

int	main(int ac, char **av)
{
	t_data			*data;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
	if (check_errors(av, ac))
		return (1);
	data = malloc(ft_atoi(av[1]) * sizeof(t_data));
	philos = malloc(ft_atoi(av[1]) * sizeof(pthread_t));
	forks = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	init_philos(data, av, ac);
	pthread_mutex_init(&mutex, NULL);
	init_mutex(data, forks);
	create_threads(data, philos, forks, &mutex);
	death_monitor(data);
	join_threads(data, philos);
	destroy_mutex(data, forks, &mutex);
	// system("leaks philo");
	free_ressources(data, philos, forks);
}
// main return : no compile error!
// if thread failed to create: must remove all threads created
// protection                                    
//time late
//pthread_detach