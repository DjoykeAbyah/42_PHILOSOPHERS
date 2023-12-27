/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/22 22:44:32 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/27 13:08:53 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @param data data struct containing all general data 
 * for the program
 * @param i index position at moment of init fail
 * @brief allocating memory and filling mutex array.
 * @todo use calloc?
*/
void	free_fork_array(t_data *data, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->fork_array[i]);
		i--;
	}
	while (&data->fork_array[i])
	{
		free(&data->fork_array[i]);
		i++;
	}
	free(data->fork_array);
}

/**
 * @param data data struct containing all general data 
 * for the program
 * @brief allocating memory and filling mutex array.
 * @todo what return?
*/
void	init_fork_array(t_data *data)
{
	int	i;

	i = 0;
	data->fork_array = ft_calloc(sizeof(pthread_mutex_t), data->philo_count);
	if (data->fork_array == NULL)
	{
		perror("error creating fork array");
		return ;
	}
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->fork_array[i], NULL) != 0)
		{
			while (i >= 0)
			{
				pthread_mutex_destroy(&data->fork_array[i]);
				perror("error with creating mutex, mutex destroyed called");
				i--;
			}
			free_fork_array(data, i);
		}
		i++;
	}
}

/**
 * @param data data struct containing all general data 
 * for the program
 * @brief initializing data struct mutexes, destroys if failed
*/
void	init_data_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->printing, NULL) != 0)
	{
		pthread_mutex_destroy(&data->printing);
		perror("error with creating mutex, mutex destroyed called");
	}
	if (pthread_mutex_init(&data->eating, NULL) != 0)
	{
		pthread_mutex_destroy(&data->eating);
		perror("error with creating mutex, mutex destroyed called");
	}
	if (pthread_mutex_init(&data->monitor, NULL) != 0)
	{
		pthread_mutex_destroy(&data->monitor);
		perror("error with creating mutex, mutex destroyed called");
	}
}

/**
 * @param data data struct containing all general data 
 * for the program
 * @brief initializing t_philo_data struct
 * @todo 
 * data->philo[i].right_fork = &data->fork_array[data->philo_count - 1];//minus one??
*/
void	init_philo(t_data *data)
{
	int		i;

	i = 0;
	data->philo = ft_calloc(sizeof(t_philo), data->philo_count);
	if (data->philo == NULL)
		perror("error malloc t_philo struct");
	while (i < data->philo_count)
	{
		data->philo[i].p_id = i + 1;
		if (i == 0)
		{
			data->philo[i].right_fork = &data->fork_array[data->philo_count - 1];
			data->philo[i].left_fork = &data->fork_array[i];
		}
		else
		{
			data->philo[i].left_fork = &data->fork_array[i];
			data->philo[i].right_fork = &data->fork_array[i - 1];
		}
		data->philo[i].times_eaten = 0;
		data->philo[i].time_of_death = 0;
		data->philo[i].data = data;
		i++;
	}
}

/**
 * @param data data struct containing all general data 
 * for the program
 * @param argc command line argument count
 * @param argv command line argument strings
 * @brief initializing data struct and filling mutex array.
 * @todo remove comments, check
*/
t_data	*init_data_struct(t_data *data, int argc, char **argv)
{
	data = ft_calloc(sizeof(t_data), 1);
	if (data == NULL)
	{
		perror("calloc went wrong");
		return (NULL);
	}
	data->start_time = get_current_time();
	data->philo_count = ft_atoi(argv[1]);
	init_fork_array(data);
	init_data_mutexes(data);
	data->stop_monitor = false;
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->eat_count = ft_atoi(argv[5]);
	return (data);
}
