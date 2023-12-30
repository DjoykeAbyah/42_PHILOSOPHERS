/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 21:00:27 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/30 19:39:56 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @param data pgrogram data struct
 * @brief loops infinite through philo's to see if a philo set the
 * stop_monitor on true or false.
*/
static void	monitor(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (death_check(&data->philo[i]) == true \
			|| eat_count_check(data->philo) == true)
			break ;
		i++;
		if (i == data->philo_count)
		{
			i = 0;
			usleep(100);
		}
	}
}

/**
 * @param data pgrogram data struct
 * @param last_create int with index of last created thread
 * @brief loops through threads to join them
*/
static void	thread_join(t_data *data, int last_create)
{
	int	i;

	i = 0;
	while (i < last_create)
	{
		if (pthread_join(data->philo[i].t_id, NULL) != 0)
		{
			perror("Error at joining thread\n");
			return ;
		}
		i++;
	}
}

/**
 * @param argv argument strings
 * @brief checks if arguments are digits
*/
static bool	input_check(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_atoi(argv[i]) == 0)
		{
			error_message();
			return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @param data struct containing all general data for
 * the program
 * @brief creates threads and joins them if creating fails from
 * last created thread
*/
static bool	thread_create(t_data *data, int i)
{
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philo[i].t_id, NULL, \
			&routine, &data->philo[i]) != 0)
		{
			thread_join(data, i);
			free_all(data);
			perror("Error at creating thread\n");
			return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @param argc int argument count
 * @param argv argument strings
 * @brief main process
*/
int	main(int argc, char **argv)
{
	t_data			*data;
	int				i;

	data = NULL;
	i = 0;
	if (argc == 5 || argc == 6)
	{
		if (input_check(argv) == false)
			return (1);
		data = init_data_struct(data, argc, argv);
		init_philo(data);
		if (thread_create(data, i) == false)
			return (1);
		monitor(data);
		thread_join(data, data->philo_count);
		free_all(data);
	}
	else
		error_message();
	return (0);
}
