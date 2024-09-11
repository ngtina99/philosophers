/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 00:27:14 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/09/11 20:08:11 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*ft_checker(void *info_converter)
// {
// 	int		i;
// 	int		nbr_philo;
// 	t_info	*info;
// 	t_philo	*philo;

// 	info = (t_info *)info_converter;
// 	philo = info->philo_info;
	
// 	{
		
// 	}
// }

void	*ft_checker(void *info_converter)
{
	t_info	*info;
	t_philo	*philo;
	int		i;
	size_t current_time;
	int		done_checker;
	info = (t_info *)info_converter;

	while (1)
	{
		i = 0;
		done_checker = 0;
		while (i < info->nbr_philo)
		{
			philo = &info->philo_info[i];

			pthread_mutex_lock(&(philo->info->eating_mutex));
			current_time = get_time();
			
			if(philo->done)
				done_checker++;
			if(done_checker == info->nbr_philo)
			{
				pthread_mutex_unlock(&(philo->info->eating_mutex));
				return(NULL);
			}
			if (current_time - philo->last_meal > info->die_time && !philo->done)
			{
				//pthread_mutex_unlock(&philo->eating_mutex);
				ft_print(DEAD, philo);
	
				//pthread_mutex_lock(&info->eating_mutex);
				pthread_mutex_unlock(&(philo->info->eating_mutex));
				return (NULL);
			}
			pthread_mutex_unlock(&(philo->info->eating_mutex));
			i++;
		}
		//usleep(1000);
	}
	return (NULL);
}

void	check_locks(t_philo *philo)
{
	if (philo->have_right_lock)
		pthread_mutex_unlock(philo->right_fork);
	if (philo->have_left_lock)
		pthread_mutex_unlock(philo->left_fork);
}

void	*start_simulation(void *convert_philo)
{
	t_philo		*philo;

	philo = (t_philo *)convert_philo;
	philo->last_meal = get_time();
	while (1)
	{
		if (philo->dead)
		{
			check_locks(philo);
			return (NULL);
		}
		get_fork(philo);
		if (philo->dead)
		{
			check_locks(philo);
			return (NULL);
		}
		eating(philo);
		if (philo->dead)
		{
			check_locks(philo);
			return (NULL);
		}
		if (philo->done)
			return (NULL);
		sleeping(philo);
		if (philo->dead)
		{
			check_locks(philo);
			return (NULL);
		}
		thinking(philo);
	}
	return (NULL);
}
