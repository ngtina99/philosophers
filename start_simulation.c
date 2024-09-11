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

size_t	get_time_checker(void)
{
	struct timeval	time_val;
	size_t			time_msec;

	gettimeofday(&time_val, NULL);
	time_msec = ((time_val.tv_sec * 1e3) + (time_val.tv_usec / 1e3));
	return (time_msec);
}

void	*ft_checker(void *convert_philo)
{
	int		i;
	int		done_checker;
	t_philo		*philo;
	t_philo		*philo_input;

	philo = (t_philo *)convert_philo;

	while (1)
	{
		i = 0;
		done_checker = 0;
		while (i < philo->info->nbr_philo)
		{
			philo_input = &philo[i];
			pthread_mutex_lock(&(philo_input->info->eating_mutex));			
			//if(philo->done)
			//	done_checker++;
			//if(done_checker == info->nbr_philo)
			//{
			//	pthread_mutex_unlock(&(philo->info->eating_mutex));
			//	return(NULL);
			//}
			//if (((get_time_checker() - philo->last_meal) > info->die_time) && !philo->done)
			if (((get_time_checker() - philo->last_meal) > philo->info->die_time))
			{
				//pthread_mutex_unlock(&philo->eating_mutex);
				ft_print(DEAD, philo);
				//pthread_mutex_lock(&info->eating_mutex);
				pthread_mutex_unlock(&(philo_input->info->eating_mutex));
				return (NULL);
			}
			pthread_mutex_unlock(&(philo_input->info->eating_mutex));
			i++;
		}
		usleep(1000);
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
	if (philo->id % 2 == 0)
		ft_usleep(philo->info->eat_time - 1000);
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
