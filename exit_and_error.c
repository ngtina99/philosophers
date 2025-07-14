/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngtina1999 <ngtina1999@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:19:34 by thuy-ngu          #+#    #+#             */
/*   Updated: 2025/07/14 23:40:57 by ngtina1999       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(int sign)
{
	if (sign == ERR_ARG)
	{
		printf(RED "Please put 5 or 6 arguments\n" EOC);
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		exit(1);
	}
	else if (sign == ERR_NUMBER)
	{
		printf(RED "Please put only (positive) numbers\n" EOC);
		exit(1);
	}
	else if (sign == ERR_PHILO)
	{
		printf(RED "Please don't put more than 200 philosophers or 0\n" EOC);
		exit(1);
	}
	else if (sign == ERR_TIME)
	{
		printf(RED "Please don't put less than 60 at time\n" EOC);
		exit(1);
	}
	else if (sign == ERR_MALLOC)
	{
		printf(RED "Memory allocation error\n" EOC);
		exit(1);
	}
	else if (sign == QUIT)
		exit (1);
}

void	destroy_philo(t_philo *philo, pthread_mutex_t *forks, t_info *info)
{
	int	i;

	i = 0;
	while (i < philo->info->nbr_philo)
	{
		pthread_mutex_destroy(&(forks[i]));
		pthread_mutex_destroy(&(philo[i].nbr_eat_mutex));
		pthread_mutex_destroy(&(philo[i].last_meal_mutex));
		pthread_mutex_destroy(&(philo[i].status_mutex));
		pthread_mutex_destroy(&(philo[i].dead_bool_mutex));
		i++;
	}
	pthread_mutex_destroy(&(info->print_mutex));
	free(philo);
	free(forks);
}
