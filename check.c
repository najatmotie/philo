/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:24:39 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/03 11:36:05 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_values(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		if (av[i][0] == '-')
			return (1);
		if (av[i][0] == '+' && av[i][1] == '\0')
			return (1);
		if (av[i][0] == '+' && av[i][1] != '\0')
			j = 1;
		else
			j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_args(char **av, int ac)
{
	if (ac != 5 && ac != 6)
	{
		printf("Invalid arguments!\n");
		return (1);
	}
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) == 0)
	{
		printf("Number of philos must be between 1 and 200!\n");
		return (1);
	}
	if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
	{
		printf("Time must not be lower than 60 ms!\n");
		return (1);
	}
	if (ac == 6 && ft_atoi(av[5]) == 0)
	{
		printf("Number of meals must start from 1!\n");
		return (1);
	}
	else
		return (0);
}

int	check_errors(char **av, int ac)
{
	if (check_values(av))
	{
		printf("Only digits and positive numbers!\n");
		return (1);
	}
	else if (check_args(av, ac))
		return (1);
	else
		return (0);
}
