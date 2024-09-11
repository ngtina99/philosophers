/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:55:39 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/09/11 20:06:35 by thuy-ngu         ###   ########.fr       */
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
	ERR_CHECK,
	ERR_MALLOC,
	QUIT,
}	t_error;

typedef enum s_status
{
	GET_FORK,
	GET_LEFT_FORK,
	GET_RIGHT_FORK,
	THINK,
	SLEEP,
	EAT,
	DEAD,
	DIE_BEF_EAT,
	DIE_BEF_SLEEP,
}	t_status;

typedef enum s_state
{
	E,
	S,
	T,
	D,
	FULL,
	IDLE,
}	t_state;

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
	int				state;
	pthread_mutex_t	mut_state;
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
	pthread_mutex_t	eating_mutex;
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
void	set_philo_state(t_philo *philo, t_state state);
t_state	get_philo_state(t_philo *philo);

#endif
