/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 18:08:55 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/23 20:27:05 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	thinking(t_philo *philo)
{
	if (stop_boolean_check(philo) == false)
		print_message(philo, "thinking");
}

void	sleeping(t_philo *philo)
{
	if (stop_boolean_check(philo) == false)
	{
		print_message(philo, "sleeping");
		usleep(philo->data->time_to_sleep);
	}
}