/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:39:45 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/09/13 16:42:37 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_died(t_philo *philo)
{
	bool	result;

	result = false;
	if (get_time() - set_last_meal(philo, CHECK) > philo->info->die_time
		&& check_status(philo) != EAT)
	{
		set_status(philo, DEAD);
		result = true;
	}
	return (result);
}

void	*ft_checker(void *convert_philo)
{
	int		i;
	int		done_checker;
	t_philo	*philo;

	philo = (t_philo *)convert_philo;
	while (1)
	{
		i = 0;
		done_checker = 0;
		while (i < philo->info->nbr_philo)
		{
			if (count_meal_nbr(&philo[i], CHECK))
				done_checker += 1;
			if (done_checker == (philo->info->nbr_philo))
				return (NULL);
			if (philo_died(&philo[i]))
			{
				ft_print(DEAD, &philo[i]);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
