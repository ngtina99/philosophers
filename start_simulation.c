/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 00:27:14 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/09/13 14:49:44 by thuy-ngu         ###   ########.fr       */
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

size_t	get_last_eat_time(t_philo *philo)
{
	size_t	last_eat_time;

	pthread_mutex_lock(&philo->last_meal_mutex);
	last_eat_time = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (last_eat_time);
}

bool	philo_died(t_philo *philo)
{
	bool		result;

	result = false;
	if (get_time() - get_last_eat_time(philo) > philo->info->die_time
		&& get_philo_state(philo) != E)
	{
		set_philo_state(philo, D);
		result = true;
	}
	return (result);
}

unsigned int	check_meal_nbr(t_philo *philo, int function)
{
	bool	done;

	done = false;
	pthread_mutex_lock(&(philo->meal_nbr_mutex));
	if (function == ADD)
		philo->nbr_eat += 1;
	if ((philo->nbr_eat) == (philo->info->limitnbr_eat))
		done = true;
	pthread_mutex_unlock(&(philo->meal_nbr_mutex));
	return (done);
}

void	*ft_checker(void *convert_philo)
{
	int		i;
	int done_checker;
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
			if (check_meal_nbr(philo_input, CHECK))
				done_checker += 1;
			if(done_checker == (philo->info->nbr_philo))
				return(NULL);
			if (philo_died(philo_input))
			{
				ft_print(DEAD, philo);
				//notify_all_philos(philo->info);
				return(NULL) ;
			}
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
	//philo->last_meal = get_time();
	update_last_meal_time(philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo->info->eat_time - 10);
	//update_last_meal_time(philo);
	while (1)
	{
		if (set_dead_bool(philo, CHECK))
		{
			check_locks(philo);
			return (NULL);
		}
		get_fork(philo);
		if (set_dead_bool(philo, CHECK))
		{
			check_locks(philo);
			return (NULL);
		}
		eating(philo);
		if (set_dead_bool(philo, CHECK))
		{
			check_locks(philo);
			return (NULL);
		}
		if (philo->done)
			return (NULL);
		sleeping(philo);
		if (set_dead_bool(philo, CHECK))
		{
			check_locks(philo);
			return (NULL);
		}
		thinking(philo);
	}
	return (NULL);
}
