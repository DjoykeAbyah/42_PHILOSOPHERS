/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 18:08:55 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/19 18:48:06 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void thinking(t_philo *philo)
{
	//message think
	printf("%d is thinking\n", philo->p_id);
	//--->die?
}

static void sleeping(t_philo *philo)
{
	//message sleep---> die?
	printf("%d is sleeping\n", philo->p_id);
	//usleep
}

/**
 * @param philo array of philosophers
 * @brief routine of the philosophers
*/
void	*routine(void *philo)
{
	t_philo *philosopher;

	//cast terug naar t_philo;
	philosopher = (t_philo *)philo;
	thinking(philo);
	//lock left fork
	pthread_mutex_lock(philosopher->left_fork);
	//message pick up left fork----> die?
	printf("%d has picked up left fork\n", philosopher->p_id);
	//lock right fork
	pthread_mutex_lock(philosopher->right_fork);
	//message pick up right fork---> die?
	printf("%d has picked up right fork\n", philosopher->p_id);
	printf("%d is eating\n", philosopher->p_id);
	//message eating---> die?
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
	//unlock
	sleeping(philo);
	return (NULL);
}
