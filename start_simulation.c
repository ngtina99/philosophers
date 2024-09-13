/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 00:27:14 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/09/13 16:52:09 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_locks(t_philo *philo)
{
	if (philo->have_right_lock)
		pthread_mutex_unlock(philo->right_fork);
	if (philo->have_left_lock)
		pthread_mutex_unlock(philo->left_fork);
}

int	quit(t_philo *philo)
{
	if (set_dead_bool(philo, CHECK))
	{
		check_locks(philo);
		return (1);
	}
	return (0);
}

void	*start_simulation(void *convert_philo)
{
	t_philo		*philo;

	philo = (t_philo *)convert_philo;
	set_last_meal(philo, CHANGE);
	//if (philo->id % 2 == 0)
	//	ft_usleep(philo->info->eat_time - 10);
	while (1)
	{
		if (quit)
			return (NULL);
		get_fork(philo);
		if (quit)
			return (NULL);
		eating(philo);
		if (quit)
			return (NULL);
		if (philo->done)
			return (NULL);
		sleeping(philo);
		if (quit)
			return (NULL);
		thinking(philo);
	}
	return (NULL);
}
