/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:19:12 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/09/11 15:46:41 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time_val;
	size_t			time_msec;

	gettimeofday(&time_val, NULL);
	time_msec = ((time_val.tv_sec * 1e3) + (time_val.tv_usec / 1e3));
	return (time_msec);
}

void	ft_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(500);
}


int	check_args(char **argv)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	while (argv[i])
	{
		len = 0;
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			if (len >= 10)
				return (1);
			len++;
			j++;
		}
		i++;
	}
	return (0);
}

size_t	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	value;

	i = 0;
	value = 0;
	if (str[i] != '\0')
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			value = value * 10 + (str[i] - 48);
			i++;
		}
	}
	if (value > 4294967295)
		print_error(ERR_CHECK);
	return ((size_t)value);
}
