#include "philo.h"

void	printing_(t_data *data, char *s)
{
	pthread_mutex_lock(data->lock);
	if (*data->still_alive != 1)
		printf("%ld %d %s\n", get_timestamp_in_ms(data->start_time),
				data->philo_id, s);
	pthread_mutex_unlock(data->lock);
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
