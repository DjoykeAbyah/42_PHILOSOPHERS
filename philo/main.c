/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 21:00:27 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/29 18:43:45 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @param data pgrogram data struct
 * @brief loops infinite through philo's to see if a philo set the
 * stop_monitor on true or false.
*/
void	monitor(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (death_check(&data->philo[i]) == true)
			break ;
		i++;
		if (i == data->philo_count)
			i = 0;
	}
}

/**
 * @param data pgrogram data struct
 * @param last_create int with index of last created thread
 * @brief loops through threads to join them
 * @todo make cleanup function adter perror
*/
void	thread_join(t_data *data, int last_create)
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
 * @todo replace perror?
*/
bool	input_check(char **argv)
{
	int i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_atoi(argv[i]) == 0)
		{
			perror("please give numeric input");
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
 * @todo norm proof
*/
int	main(int argc, char **argv)
{
	t_data			*data;
	int				i;

	data = NULL;
	i = 0;
	if (argc == 5 || argc == 6)
	{
		//create thread watch
		if (input_check(argv) == false)
			return (1);
		data = init_data_struct(data, argc, argv);
		init_philo(data);
		while (i < data->philo_count)
		{
			if (pthread_create(&data->philo[i].t_id, NULL, &routine, &data->philo[i]) != 0)
			{
				thread_join(data, i);
				perror("Error at creating thread\n");
				return (1);
			}
			i++;
		}
		monitor(data);
		thread_join(data, i);
	}
	else
		printf("please give ./philo nr nr nr nr nr");
}
