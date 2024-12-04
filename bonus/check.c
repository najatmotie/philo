/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:24:39 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/02 23:07:03 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static int	integer_len(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i = 1;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*str;
	int		i;

	nb = n;
	str = (char *)malloc(integer_len(nb) + 1 * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[integer_len(nb)] = '\0';
	i = integer_len(nb) - 1;
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		str[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_s;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	new_s = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (new_s == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new_s[i + j] = s2[j];
		j++;
	}
	new_s[i + j] = '\0';
	return (new_s);
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
