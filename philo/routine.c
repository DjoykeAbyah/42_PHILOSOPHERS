/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 18:08:55 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/29 20:57:38 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void 	sleepy(t_philo *philo, int time)
{
	int long current_time;
	
	current_time = get_current_time();
	while ((get_current_time() - current_time) < time && stop_boolean_check(philo) == false)
		usleep(100);
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
	while (stop_boolean_check(philo) == false && (philo->times_eaten < philo->data->eat_count))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

/**
 * @param philo philo struct
 * @brief prints thinking message if no philo died
*/
void	thinking(t_philo *philo)
{
	print_message(philo, "is thinking");
}

/**
 * @param philo philo struct
 * @brief prints sleeping message if no philo died
 * and sleeps for data->time_to_sleep amount
*/
void	sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	sleepy(philo, philo->data->time_to_sleep);
}

/**
 * @param philo philo struct
 * @brief prints eating message if no philo died
 * and eats for data->time_to_eat amount
*/
void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a left fork");
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a right fork");
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->data->eating);
	philo->last_eat = get_current_time();
	philo->times_eaten += 1;
	pthread_mutex_unlock(&philo->data->eating);
	sleepy(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}