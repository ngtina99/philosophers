/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:19:31 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/09/13 14:51:12 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_info *args, int argc, char **argv)
{
	if (check_args(argv))
		print_error(ERR_CHECK);
	args->nbr_philo = ft_atoi(argv[1]);
	if (args->nbr_philo > 200 || args->nbr_philo == 0)
		print_error(ERR_CHECK);
	args->die_time = ft_atoi(argv[2]);
	args->eat_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	if (args->die_time < 60 || args->eat_time < 60 || args->sleep_time < 60)
		print_error(ERR_CHECK);
	if (argc == 6)
		args->limitnbr_eat = ft_atoi(argv[5]);
	else
		args->limitnbr_eat = -1;
	if (args->limitnbr_eat == 0)
		print_error(QUIT);
	pthread_mutex_init(&(args->print_mutex), NULL);
	pthread_mutex_init(&(args->eating_mutex), NULL);
	args->start_time = get_time();
}

void	init_philos(t_info *args, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < args->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].status = 0;
		philo[i].nbr_eat = 0;
		philo[i].dead = false;
		philo[i].done = false;
		philo[i].info = args;
		philo[i].have_right_lock = false;
		philo[i].have_left_lock = false;
		philo[i].state = IDLE;
		pthread_mutex_init(&philo[i].state_mutex, NULL);
		pthread_mutex_init(&philo[i].meal_nbr_mutex, NULL);
		pthread_mutex_init(&philo[i].last_meal_mutex, NULL);
		pthread_mutex_init(&philo[i].dead_bool_mutex, NULL);
		update_last_meal_time(&philo[i]);
		i++;
	}
}

void	init_tools(t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philo->info->nbr_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	philo[0].left_fork = &forks[0];
	philo[0].right_fork = &forks[philo->info->nbr_philo - 1];
	i = 1;
	while (i < philo->info->nbr_philo)
	{
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[i - 1];
		i++;
	}
}

void	init_threads(t_philo *philo, t_info *args)
{
	int			i;
	pthread_t	*thread_id;

	i = 0;
	thread_id = malloc(philo->info->nbr_philo * sizeof(pthread_t));
	if (!thread_id)
		print_error(ERR_MALLOC);
	while (i < philo->info->nbr_philo)
	{
		pthread_create(&thread_id[i], NULL, \
		&start_simulation, (void *)&philo[i]);
		i++;
	}
	if (philo->info->nbr_philo != 1)
	{
		pthread_create(&args->checker, NULL, &ft_checker, args->philo_info);
		pthread_join(args->checker, NULL);
	}
	i = 0;
	while (i < philo->info->nbr_philo)
	{
		pthread_join(thread_id[i], NULL);
		i++;
	}
	free(thread_id);
}

void	init_data(t_info *args, int argc, char **argv)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;

	init_args(args, argc, argv);
	args->philo_info = malloc(sizeof(t_philo) * args->nbr_philo);
		if (!args->philo_info)
			print_error(ERR_MALLOC);
	philo = args->philo_info;
	//philo = malloc(sizeof(t_philo) * args->nbr_philo);
	//if (!philo)
	//	print_error(ERR_MALLOC);
	init_philos(args, philo);
	forks = malloc(philo->info->nbr_philo * sizeof(pthread_mutex_t));
	if (!forks)
		print_error(ERR_MALLOC);
	init_tools(philo, forks);
	init_threads(philo, args);
	destroy_philo(philo, forks, args);
}
