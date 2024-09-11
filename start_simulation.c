/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 00:27:14 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/09/11 19:29:51 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_checker(void *info_converter)
{
	int		i;
	int		nbr_philo;
	t_info	*info;
	t_philo	*philo;

	info = (t_info *)info_converter;
	philo = info->philo_info;
	
	{
		
	}
}

void	*start_simulation(void *convert_philo)
{
	t_philo		*philo;

	philo = (t_philo *)convert_philo;
	philo->last_meal = get_time();
	while (1)
	{
		if (philo->dead)
			return (NULL);
		get_fork(philo);
		if (philo->dead)
			return (NULL);
		eating(philo);
		if (philo->done || philo->dead)
			return (NULL);
		sleeping(philo);
		if (philo->dead)
			return (NULL);
		thinking(philo);
	}
	return (NULL);
}
