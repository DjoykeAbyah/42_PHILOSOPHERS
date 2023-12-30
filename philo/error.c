/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/30 16:36:39 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/30 19:34:23 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @param void
 * @brief prints reminder of parameters of philo program
*/
void	error_message(void)
{
	printf("please give as input:\n");
	printf("./philo + in digits > 0\n1) number_of_philo\n2) time_to_die\n");
	printf("3) time_to_eat\n4) time_to_sleep\n");
	printf("optional is:\n5) times_eaten\n");
	printf("example: ./philo 7 2000 400 100 5");
}

/**
 * @param data struct containing all general data
 * for philo program
 * @brief destroys all mutexes
*/
static void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->printing);
	pthread_mutex_destroy(&data->eating);
	pthread_mutex_destroy(&data->monitor);
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->fork_array[i]);
		i++;
	}
}

/**
 * @param philo philo struct from specific thread
 * @param message string containing message of action
 * @brief prints message with correct timestamp and philo
*/
void	print_message(t_philo *philo, char *message)
{
	int long	time;

	pthread_mutex_lock(&philo->data->printing);
	time = time_stamp(philo);
	if ((stop_boolean_check(philo) == false) || \
		(ft_strcmp(message, "has died") == 0))
		printf("%ld %i %s\n", time, philo->p_id, message);
	pthread_mutex_unlock(&philo->data->printing);
}

/**
 * @param data struct containing all general data for
 * the program
 * @brief frees all allocated memory
*/
void	free_all(t_data *data)
{
	destroy_mutexes(data);
	free(data->fork_array);
	free(data->philo);
	free(data);
}
