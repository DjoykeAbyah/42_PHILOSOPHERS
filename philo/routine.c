/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 18:08:55 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/22 20:15:44 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void thinking(t_philo *philo)
{
	int long 		milliseconds;
	struct timeval 	current_time;
	int	long		start;
	
	//message sleep---> die?
	start = get_current_time();
	milliseconds = start - philo->data->start_time;
	pthread_mutex_lock(&philo->data->printing_mutex);
	printf("%09ld %d is thinking\n", milliseconds, (philo->p_id + 1));
	pthread_mutex_unlock(&philo->data->printing_mutex);
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
	pthread_mutex_lock(&philo->data->printing_mutex);
	printf("%09ld %d is sleeping\n", milliseconds, (philo->p_id + 1));
	pthread_mutex_unlock(&philo->data->printing_mutex);
	while ((philo->data->time_to_sleep + start) < get_current_time())
		usleep(250);
}

static void eating(t_philo *philo)
{
	int long 		milliseconds;
	struct timeval 	current_time;
	int	long		start;
	
	//message sleep---> die?
	start = get_current_time();
	milliseconds = start - philo->data->start_time;
	pthread_mutex_lock(&philo->data->printing_mutex);
	printf("%09ld %d is eating\n", milliseconds, (philo->p_id + 1));
	pthread_mutex_unlock(&philo->data->printing_mutex);
	while ((philo->data->time_to_eat + start) < get_current_time())
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
	while (!philosopher->data->stop_monitor)
	{
		if (philosopher->p_id % 2 != 0)
			sleeping(philosopher);
		pthread_mutex_lock(philosopher->left_fork);
		pthread_mutex_lock(&philosopher->data->printing_mutex);
		printf("%d has picked up left fork\n", (philosopher->p_id + 1));
		pthread_mutex_unlock(&philosopher->data->printing_mutex);
		//message pick up left fork----> die?
		pthread_mutex_lock(philosopher->right_fork);
		pthread_mutex_lock(&philosopher->data->printing_mutex);
		printf("%d has picked up right fork\n", (philosopher->p_id + 1));
		pthread_mutex_unlock(&philosopher->data->printing_mutex);
		//message pick up right fork---> die?
		eating(philosopher);
		//message eating---> die?
		pthread_mutex_unlock(philosopher->right_fork);
		pthread_mutex_unlock(philosopher->left_fork);
		sleeping(philosopher);
		thinking(philosopher);
	}
	return (philosopher);
}
