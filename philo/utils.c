/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:38:35 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/06 15:36:34 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	free_ressources(t_data *data, pthread_mutex_t *forks, pthread_t *philos)
{
	free(forks);
	free(philos);
	free(data->eat_count);
	free(data->still_alive);
	free(data->error_occured);
	free(data);
}
