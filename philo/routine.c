/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 18:08:55 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/30 20:04:00 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @param philo philo struct
 * @param time int containing time philo must sleep
 * @brief loops through short iterations of time philo
 * must sleep
*/
static void	sleepy(t_philo *philo, int time)
{
	int long	current_time;

	current_time = get_current_time();
	while ((get_current_time() - current_time) < time && \
		stop_boolean_check(philo) == false)
		usleep(100);
}

/**
 * @param philo philo struct
 * @brief prints thinking message if no philo died
*/
static void	thinking(t_philo *philo)
{
	print_message(philo, "is thinking");
}

/**
 * @param philo philo struct
 * @brief prints sleeping message if no philo died
 * and sleeps for data->time_to_sleep amount
*/
static void	sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	sleepy(philo, philo->data->time_to_sleep);
}

/**
 * @param philo philo struct
 * @brief prints eating message if no philo died
 * and eats for data->time_to_eat amount
*/
static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork");
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->data->stop_monitor = true;
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->data->eating);
	philo->last_eat = get_current_time();
	philo->times_eaten += 1;
	pthread_mutex_unlock(&philo->data->eating);
	sleepy(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

/**
 * @param philo void * to eventually philo struct
 * @brief loops through routine actions untill a philo died
 * @return philo struct
*/
void	*routine(void *philosopher)
{
	t_philo		*philo;

	philo = (t_philo *)philosopher;
	if (philo->p_id % 2)
		usleep(1000);
	while (stop_boolean_check(philo) == false)
	{
		eating(philo);
		sleeping(philo);
		if (eat_count_check(philo) == true)
			return (NULL);
		thinking(philo);
		if (eat_count_check(philo) == true)
			return (NULL);
	}
	return (NULL);
}
