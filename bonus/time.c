/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:32:39 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/03 17:49:31 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_timestamp_in_ms(struct timeval start_time)
{
	long			start_ms;
	long			current_ms;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	current_ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	start_ms = start_time.tv_sec * 1000 + start_time.tv_usec / 1000;
	return (current_ms - start_ms);
}

void	ft_usleep(useconds_t time)
{
	useconds_t		t;
	struct timeval	start;
	long			current_time;

	t = time * 1000;
	gettimeofday(&start, NULL);
	current_time = get_timestamp_in_ms(start);
	while (current_time * 1000 < t)
	{
		current_time = get_timestamp_in_ms(start);
		usleep(50);
	}
}
