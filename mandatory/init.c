/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:23 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/01 19:46:02 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_variables(t_data *data, char **av)
{
	int	i;
	int	*p;
	int	*r;

	i = 0;
	p = malloc(sizeof(int));
	*p = 0;
	r = malloc(sizeof(int));
	*r = 0;
	while (i < ft_atoi(av[1]))
	{
		data[i].args.time_must_eat = 0;
		data[i].philo_nb = ft_atoi(av[1]);
		data[i].philo_id = i + 1;
		data[i].args.time_to_die = ft_atoi(av[2]);
		data[i].args.time_to_eat = ft_atoi(av[3]);
		data[i].args.time_to_sleep = ft_atoi(av[4]);
		data[i].eat_count = p;
		data[i].still_alive = r;
		gettimeofday(&data[i].start_time, NULL);
		data[i].last_meal_time = get_timestamp_in_ms(data[i].start_time);
		i++;
	}
}

void	init_philos(t_data *data, char **av, int ac)
{
	int	i;

	i = 0;
	init_variables(data, av);
	if (ac == 6)
	{
		while (i < ft_atoi(av[1]))
		{
			data[i].args.time_must_eat = ft_atoi(av[5]);
			i++;
		}
	}
}

void	init_mutex(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	destroy_mutex(t_data *data, pthread_mutex_t *forks, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(mutex);
		i++;
	}
}
