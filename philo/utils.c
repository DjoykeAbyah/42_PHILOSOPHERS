/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 17:46:34 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/30 20:04:37 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @param void
 * @brief get's current time from 1979 until now
*/
int long	get_current_time(void)
{
	struct timeval	current_time;
	int long		time_millisec;

	if (gettimeofday(&current_time, NULL) != 0)
	{
		write(2, "Error getting time of day\n", 27);
		return (0);
	}
	else
		time_millisec = \
			current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time_millisec);
}

/**
 * @param philo philo struct from specific thread
 * @brief returns correct timestamp by 
 * extracting start_time from current_time
 * @return int long new_time
*/
int long	time_stamp(t_philo *philo)
{
	long int	current_time;
	long int	new_time;

	current_time = get_current_time();
	new_time = current_time - philo->data->start_time;
	return (new_time);
}

/**
 * @param philo philo struct from specific thread
 * @brief checks if monitor boolean is set to true or false
 * @return true if philo died, false if not
*/
bool	stop_boolean_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->monitor);
	if (philo->data->stop_monitor == true)
	{
		pthread_mutex_unlock(&philo->data->monitor);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->monitor);
	return (false);
}

/**
 * @param philo philo struct from specific thread
 * @brief checks if philo exeeded time to die and 
 * sets monitor boolean on true.
 * @return true is philo died, false if not
*/
bool	death_check(t_philo *philo)
{
	long int	time;

	pthread_mutex_lock(&philo->data->eating);
	time = get_current_time() - philo->last_eat;
	if (time > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->eating);
		pthread_mutex_lock(&philo->data->monitor);
		philo->data->stop_monitor = true;
		pthread_mutex_unlock(&philo->data->monitor);
		print_message(philo, "died");
		return (true);
	}
	pthread_mutex_unlock(&philo->data->eating);
	return (false);
}

/**
 * @param philo philo struct from specific thread
 * @brief checks if there is a eat count and if times eaten
 * is equal to the eat count
 * @return true if times eaten equal to eat count, 
 * false if no eat count or not equal to times eaten
*/
bool	eat_count_check(t_philo *philo)
{
	if (philo->data->has_eat_count == true)
	{
		if (philo->times_eaten == philo->data->eat_count)
			return (true);
	}
	return (false);
}
