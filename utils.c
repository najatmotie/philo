/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:38:35 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/06 13:07:42 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printing_(t_data *data, char *s)
{
	pthread_mutex_lock(data->multi_lock);
	if (*data->still_alive != 1 && *data->error_occured != 1)
		printf("%ld %d %s\n", get_timestamp_in_ms(data->start_time),
			data->philo_id, s);
	pthread_mutex_unlock(data->multi_lock);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	r;
	int	sign;

	i = 0;
	r = 0;
	sign = 1;
	if (str[i] != '\0' && (str[i] == '+' && str[i + 1] != '\0'))
		i++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		r = (r * 10) + (str[i] - 48);
		i++;
	}
	return (r * sign);
}
