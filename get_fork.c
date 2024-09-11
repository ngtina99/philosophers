/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:38:41 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/09/11 20:03:19 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	odd_case(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo->have_left_lock = true;
	ft_print(GET_RIGHT_FORK, philo);
	if (philo->info->nbr_philo == 1)
	{
		ft_usleep(philo->info->die_time);
		ft_print(DEAD, philo);
	}
	if (philo->dead)
		return ;

	pthread_mutex_lock(philo->right_fork);
	philo->have_right_lock = true;
	ft_print(GET_LEFT_FORK, philo);
	if (philo->dead)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
}

void	even_case(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	philo->have_right_lock = true;
	ft_print(GET_LEFT_FORK, philo);
	if (philo->dead)
	{
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	philo->have_left_lock = true;
	ft_print(GET_RIGHT_FORK, philo);
	if (philo->dead)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
}

void	get_fork(t_philo *philo)
{
	if (philo->id % 2)
		odd_case(philo);
	else
		even_case(philo);
}
