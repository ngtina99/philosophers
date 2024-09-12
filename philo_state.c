#include "philo.h"

t_state	get_philo_state(t_philo *philo)
{
	t_state	state;

	pthread_mutex_lock(&philo->state_mutex);
	state = philo->state;
	pthread_mutex_unlock(&philo->state_mutex);
	return (state);
}

void	set_philo_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->state_mutex);
	if (philo->state != DEAD)
		philo->state = state;
	pthread_mutex_unlock(&philo->state_mutex);
}

bool	set_dead_bool(t_philo *philo, int function)
{
	bool	one_died;

	one_died = false;
	pthread_mutex_lock(&philo->dead_bool_mutex);
	if (function ==  ADD)
		philo->dead = true;
	if(philo->dead)
		one_died = true;
	pthread_mutex_unlock(&philo->dead_bool_mutex);
	return(one_died);
}

/*bool	get_keep_iter(t_data *data)
{
	bool	keep_iterating;

	pthread_mutex_lock(&data->mut_keep_iter);
	keep_iterating = data->keep_iterating;
	pthread_mutex_unlock(&data->mut_keep_iter);
	return (keep_iterating);
}

void	set_keep_iterating(t_data *data, bool set_to)
{
	pthread_mutex_lock(&data->mut_keep_iter);
	data->keep_iterating = set_to;
	pthread_mutex_unlock(&data->mut_keep_iter);
}*/