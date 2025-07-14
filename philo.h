/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngtina1999 <ngtina1999@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:55:39 by thuy-ngu          #+#    #+#             */
/*   Updated: 2025/07/14 23:40:29 by ngtina1999       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/time.h>

# define PURPLE	"\033[1;35m"
# define RED	"\033[1;91m"
# define GREEN	"\033[1;32m"
# define BLUE	"\033[1;36m"
# define EOC	"\033[0;0m"

typedef enum s_error
{
	ERR_ARG,
	ERR_NUMBER,
	ERR_PHILO,
	ERR_TIME,
	ERR_MALLOC,
	QUIT,
}	t_error;

typedef enum s_status
{
	START,
	GET_FORK,
	THINK,
	SLEEP,
	EAT,
	DEAD,
}	t_status;

typedef enum s_function
{
	CHECK,
	CHANGE,
}	t_function;

struct	s_info;

typedef struct s_philo
{
	struct s_info	*info;
	size_t			id;
	int				status;
	size_t			nbr_eat;
	size_t			last_meal;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	bool			dead;
	bool			done;
	bool			have_right_lock;
	bool			have_left_lock;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t	nbr_eat_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	dead_bool_mutex;
}	t_philo;

typedef struct s_info
{
	int				nbr_philo;
	size_t			limitnbr_eat;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			start_time;
	pthread_mutex_t	print_mutex;
	t_philo			*philo_info;
	pthread_t		checker;
	pthread_mutex_t	dead_mutex;
	bool			dead;
}	t_info;

void	print_error(int sign);
int		check_args(char **argv);
void	init_data(t_info *args, int argc, char **argv);
int		check_args(char **argv);
size_t	ft_atoi(const char *str);
void	*start_simulation(void *args);
void	get_fork(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
size_t	get_time(void);
void	ft_print(int stage, t_philo *philo);
void	ft_usleep(size_t time);
void	init_threads(t_philo *philo, t_info *args);
void	init_tools(t_philo *philo, pthread_mutex_t *forks);
void	destroy_philo(t_philo *philo, pthread_mutex_t *forks, t_info *info);
void	get_fork(t_philo *philo);
void	*ft_checker(void *info_converter);
void	set_status(t_philo *philo, int status);
int		check_status(t_philo *philo);
size_t	count_meal_nbr(t_philo *philo, int function);
bool	set_dead_bool(t_philo *philo, int function);
size_t	set_last_meal(t_philo *philo, int function);
bool	philo_died(t_philo *philo);
void	*ft_checker(void *convert_philo);

#endif
