/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 18:08:55 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/23 20:36:21 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @param philo void * to eventually philo struct
 * @brief loops through routine actions untill a philo died
 * @return philo struct
*/
void	*routine(void *philo)
{
	t_philo		*philosopher;

	philosopher = (t_philo *)philo;
	while (!stop_boolean_check(philosopher))
	{
		sleeping(philosopher);
		thinking(philosopher);
	}
	return (philosopher);
}

/**
 * @param philo philo struct
 * @brief prints thinking message if no philo died
*/
void	thinking(t_philo *philo)
{
	if (stop_boolean_check(philo) == false)
		print_message(philo, "thinking");
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
		print_message(philo, "sleeping");
		usleep(philo->data->time_to_sleep);
	}
}