/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:37:20 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/09/13 16:37:20 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	count_meal_nbr(t_philo *philo, int function)
{
	bool	done;

	done = false;
	pthread_mutex_lock(&(philo->nbr_eat_mutex));
	if (function == CHANGE)
		philo->nbr_eat += 1;
	if ((philo->nbr_eat) == (philo->info->limitnbr_eat))
		done = true;
	pthread_mutex_unlock(&(philo->nbr_eat_mutex));
	return (done);
}

size_t	set_last_meal(t_philo *philo, int function)
{
	size_t	last_meal_time;

	last_meal_time = 0;
	pthread_mutex_lock(&philo->last_meal_mutex);
	if (function == CHANGE)
		philo->last_meal = get_time();
	last_meal_time = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (last_meal_time);
}

int	check_status(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(&philo->status_mutex);
	status = philo->status;
	pthread_mutex_unlock(&philo->status_mutex);
	return (status);
}

void	set_status(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->status_mutex);
	if (philo->status != DEAD)
		philo->status = status;
	pthread_mutex_unlock(&philo->status_mutex);
}

bool	set_dead_bool(t_philo *philo, int function)
{
	bool	one_died;

	one_died = false;
	pthread_mutex_lock(&philo->dead_bool_mutex);
	if (function == CHANGE)
		philo->dead = true;
	if (philo->dead)
		one_died = true;
	pthread_mutex_unlock(&philo->dead_bool_mutex);
	return (one_died);
}
