/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 17:46:34 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/27 13:55:49 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief get's current time from 1979 until now
*/
int long	get_current_time(void)
{
	struct timeval	current_time;
	int long		time_millisec;

	if (gettimeofday(&current_time, NULL) != 0)
	{
		perror("Error getting time of day");
		return (0);
	}
	else
		time_millisec = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time_millisec);
}

/**
 * @param philo philo struct from specific thread
 * @param message string containing message of action
 * @brief prints message with correct timestamp and philo
*/
void	print_message(t_philo *philo, char *message)
{
	int long	time;
	int 		i;

	pthread_mutex_lock(&philo->data->printing);
	time = time_stamp(philo);
	// if (ft_strncmp(message, "has died"))
	// {
	// 	printf("%ld philo nr %i is %s\n", time, philo->p_id, message);
	// 	while (i <= philo->data->philo_count)
	// 		pthread_detach(philo->t_id);
	// }
	printf("%ld philo nr %i is %s\n", time, philo->p_id, message);
	pthread_mutex_unlock(&philo->data->printing);
	usleep(500);
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

	pthread_mutex_lock(&philo->data->monitor);
	time = time_stamp(philo);
	if (time > philo->data->time_to_die)
	{
		philo->data->stop_monitor = true;
		print_message(philo, "has died");
		pthread_mutex_unlock(&philo->data->monitor);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->monitor);
	return (false);
}
