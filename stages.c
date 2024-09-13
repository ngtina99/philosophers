/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stages.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:19:17 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/09/13 14:36:41 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(int stage, t_philo *philo)
{
	size_t		timestamp;
	static int	finish;

	pthread_mutex_lock(&(philo->info->print_mutex));
	if (finish == 1)
	{
		set_dead_bool(philo, ADD);
		pthread_mutex_unlock(&(philo->info->print_mutex));
		return ;
	}
	timestamp = get_time() - (philo->info->start_time);
	if (stage == GET_RIGHT_FORK || stage == GET_LEFT_FORK)
		printf("%lu %ld %s\n", timestamp, philo->id, "has taken a fork");
	else if (stage == THINK)
		printf("%lu %ld %s\n", timestamp, philo->id, "is thinking");
	else if (stage == SLEEP)
		printf("%lu %ld %s\n", timestamp, philo->id, "is sleeping");
	else if (stage == EAT)
		printf("%lu %ld %s\n", timestamp, philo->id, "is eating");
	else if (stage == DEAD || stage == DIE_BEF_EAT || stage == DIE_BEF_SLEEP)
	{
		finish = 1;
		set_dead_bool(philo, ADD);
		printf("%lu %ld %s\n", timestamp, philo->id, "died");
	}
	pthread_mutex_unlock(&(philo->info->print_mutex));
}

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
}

void	eating(t_philo *philo)
{
	set_philo_state(philo, E);
	ft_print(EAT, philo);
	if (set_dead_bool(philo, CHECK))
		return ;
	update_last_meal_time(philo);
	//philo->last_meal = get_time();
	ft_usleep(philo->info->eat_time);
	pthread_mutex_unlock(philo->right_fork);
	philo->have_right_lock = false;
	pthread_mutex_unlock(philo->left_fork);
	philo->have_left_lock = false;
	check_meal_nbr(philo, ADD);
	if (philo->nbr_eat == philo->info->limitnbr_eat)
		philo->done = true;
}

void	sleeping(t_philo *philo)
{
	set_philo_state(philo, S);
	ft_print(SLEEP, philo);
	if (set_dead_bool(philo, CHECK))
		return ;
	ft_usleep(philo->info->sleep_time);
}

void	thinking(t_philo *philo)
{
	set_philo_state(philo, T);
	ft_print(THINK, philo);
	if (set_dead_bool(philo, CHECK))
		return ;
}
