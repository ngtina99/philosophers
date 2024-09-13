/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stages.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:19:17 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/09/13 16:33:19 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(int stage, t_philo *philo, size_t timestamp)
{
	if (stage == GET_FORK)
		printf("%lu %ld %s\n", timestamp, philo->id, "has taken a fork");
	else if (stage == THINK)
		printf("%lu %ld %s\n", timestamp, philo->id, "is thinking");
	else if (stage == SLEEP)
		printf("%lu %ld %s\n", timestamp, philo->id, "is sleeping");
	else if (stage == EAT)
		printf("%lu %ld %s\n", timestamp, philo->id, "is eating");
}

void	ft_print(int stage, t_philo *philo)
{
	size_t		timestamp;
	static int	finish;

	pthread_mutex_lock(&(philo->info->print_mutex));
	if (finish == 1)
	{
		set_dead_bool(philo, CHANGE);
		pthread_mutex_unlock(&(philo->info->print_mutex));
		return ;
	}
	timestamp = get_time() - (philo->info->start_time);
	if (stage != DEAD)
		print_status(stage, philo, timestamp);
	else if (stage == DEAD)
	{
		finish = 1;
		set_dead_bool(philo, CHANGE);
		printf("%lu %ld %s\n", timestamp, philo->id, "died");
	}
	pthread_mutex_unlock(&(philo->info->print_mutex));
}

void	eating(t_philo *philo)
{
	set_status(philo, EAT);
	ft_print(EAT, philo);
	if (set_dead_bool(philo, CHECK))
		return ;
	set_last_meal(philo, CHANGE);
	ft_usleep(philo->info->eat_time);
	pthread_mutex_unlock(philo->right_fork);
	philo->have_right_lock = false;
	pthread_mutex_unlock(philo->left_fork);
	philo->have_left_lock = false;
	count_meal_nbr(philo, CHANGE);
	if (philo->nbr_eat == philo->info->limitnbr_eat)
		philo->done = true;
}

void	sleeping(t_philo *philo)
{
	set_status(philo, SLEEP);
	ft_print(SLEEP, philo);
	if (set_dead_bool(philo, CHECK))
		return ;
	ft_usleep(philo->info->sleep_time);
}

void	thinking(t_philo *philo)
{
	set_status(philo, THINK);
	ft_print(THINK, philo);
	if (set_dead_bool(philo, CHECK))
		return ;
}
