/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:23 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/03 17:53:40 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_variables(t_data *data, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		data[i].args.time_must_eat = 0;
		data[i].philo_nb = ft_atoi(av[1]);
		data[i].philo_id = i + 1;
		data[i].args.time_to_die = ft_atoi(av[2]);
		data[i].args.time_to_eat = ft_atoi(av[3]);
		data[i].args.time_to_sleep = ft_atoi(av[4]);
		data[i].eat_count = 0;
		data[i].still_alive = 0;
		gettimeofday(&data[i].start_time, NULL);
		data[i].last_meal_time = get_timestamp_in_ms(data[i].start_time);
		// data[i].left_fork = sem_open(ft_strjoin("/fork_", ft_itoa(i)), O_CREAT, 0666, 1);
		// data[i].right_fork = sem_open(ft_strjoin("/fork_", ft_itoa((i + 1) % data->philo_nb)), O_CREAT, 0666, 1) ;
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
