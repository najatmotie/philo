/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:15 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/03 17:54:39 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_ressources(t_data *data, pid_t *philos)
{
	free(philos);
	free(data);
}

int	main(int ac, char **av)
{
	t_data			*data;
	sem_t	*forks;
	pid_t		*philos;
	
	if (check_errors(av, ac))
		return (1);
	data = malloc(ft_atoi(av[1]) * sizeof(t_data));
	philos = malloc(ft_atoi(av[1]) * sizeof(pthread_t));
	init_philos(data, av, ac);
	forks = sem_open("/fork_sem", O_CREAT, 0666, data->philo_nb);
	create_philos(data, forks);
	death_monitor(data, philos);
	free_ressources(data, philos);
	sem_close(forks);
	sem_unlink("/fork_sem");
}
