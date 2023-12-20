/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 18:08:55 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/20 19:02:06 by dreijans      ########   odam.nl         */
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
	int long 		milliseconds;
	struct timeval 	current_time;
	int	long		start;
	
	//message sleep---> die?
	start = get_current_time();
	milliseconds = start - philo->data->start_time;
	printf("%09ld %d is sleeping\n", milliseconds, (philo->p_id + 1));
	while ((philo->data->time_to_sleep + start) < get_current_time())
		usleep(250);
}

int long	get_current_time()
{
	int long 	time_milli;
	struct 		timeval 	current_time;
	
	if (gettimeofday(&current_time, NULL) == -1)
		perror("gettimeofday error");
	time_milli = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time_milli);
}

/**
 * @param philo array of philosophers
 * @brief routine of the philosophers
*/
void	*routine(void *philo)
{
	t_philo *philosopher;

	philosopher = (t_philo *)philo;
	while (1)
	{
		thinking(philosopher);
		pthread_mutex_lock(philosopher->left_fork);
		//message pick up left fork----> die?
		printf("%d has picked up left fork\n", (philosopher->p_id + 1));
		pthread_mutex_lock(philosopher->right_fork);
		//message pick up right fork---> die?
		printf("%d has picked up right fork\n", (philosopher->p_id + 1));
		printf("%d is eating\n", (philosopher->p_id + 1));
		//message eating---> die?
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
		sleeping(philosopher);
	}
	return (philosopher);
}
