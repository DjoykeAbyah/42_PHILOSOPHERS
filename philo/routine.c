/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 18:08:55 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/27 18:36:36 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void 	sleepy(int time)
{
	int long current_time;
	
	current_time = get_current_time();
	while ((get_current_time() - current_time) < time)
		usleep(100);
}

/**
 * @param philo void * to eventually philo struct
 * @brief loops through routine actions untill a philo died
 * @return philo struct
*/
void	*routine(void *philo)
{
	t_philo		*philosopher;

	philosopher = (t_philo *)philo;
	if (philosopher->p_id % 2)
		usleep(500);
	while (stop_boolean_check(philosopher) == false)
	{
		eating(philosopher);
		sleeping(philosopher);
		thinking(philosopher);
	}
	return (NULL);
}

/**
 * @param philo philo struct
 * @brief prints thinking message if no philo died
*/
void	thinking(t_philo *philo)
{
	if (stop_boolean_check(philo) == false)
		print_message(philo, "is thinking");
}

/**
 * @param philo philo struct
 * @brief prints sleeping message if no philo died
 * and sleeps for data->time_to_sleep amount
*/
void	sleeping(t_philo *philo)
{
	if (stop_boolean_check(philo) == false)
	{
		print_message(philo, "is sleeping");
		sleepy(philo->data->time_to_sleep);
	}
}

/**
 * @param philo philo struct
 * @brief prints eating message if no philo died
 * and eats for data->time_to_eat amount
*/
void	eating(t_philo *philo)
{
	if (stop_boolean_check(philo) == false)
	{	
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
		print_message(philo, "is eating");
		pthread_mutex_lock(&philo->data->eating);
		philo->last_eat = get_current_time();
		pthread_mutex_unlock(&philo->data->eating);
		sleepy(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}