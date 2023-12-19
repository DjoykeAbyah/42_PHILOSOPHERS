/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 18:08:55 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/19 19:45:49 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void thinking(t_philo *philo)
{
	//message think
	printf("%d is thinking\n", (philo->p_id + 1));
	//--->die?
}

static void sleeping(t_philo *philo)
{
	//message sleep---> die?
	printf("%d is sleeping\n", (philo->p_id + 1));
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
	while (1)
	{
		thinking(philosopher);
		//lock left fork
		pthread_mutex_lock(philosopher->left_fork);
		//message pick up left fork----> die?
		printf("%d has picked up left fork\n", (philosopher->p_id + 1));
		//lock right fork
		pthread_mutex_lock(philosopher->right_fork);
		//message pick up right fork---> die?
		printf("%d has picked up right fork\n", (philosopher->p_id + 1));
		printf("%d is eating\n", (philosopher->p_id + 1));
		//message eating---> die?
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
		//unlock
		sleeping(philosopher);
	}
	return (philosopher);
}
