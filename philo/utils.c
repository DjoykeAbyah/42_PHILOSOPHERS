/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 17:46:34 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/19 17:08:08 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/**
 * @param c character to be checked
 * @brief checks characters for whitespaces
*/
static	int	ft_iswhitespace(char c)
{
	return (c == ' ' || ((c >= 9 && c <= 13)));
}

/**
 * @param str string to be converted to integer
 * @brief converting numeric characters to integers
*/
long int	ft_atoi(const char *str)
{
	long	i;
	long	sign;
	long	number;

	number = 0;
	sign = 1;
	i = 0;
	while (ft_iswhitespace(str[i]) && str[i] != '\0')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		number = number * 10 + str[i] -48;
		i++;
	}
	return (number * sign);
}

/**
 * @param data data struct containing all general data 
 * for the program
 * @param argc command line argument count
 * @param argv command line argument strings
 * @brief initializing data struct and filling mutex array.
*/
void init_data_struct(t_data *data, int argc, char **argv)
{
	int				i;

	i = 0;
	data->philo_count = ft_atoi(argv[1]);
	data->fork_array = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (data->fork_array == NULL)
		return ;//return iets anders/free?
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->fork_array[i], NULL);
		i++;
	}
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
}

/**
 * @param data data struct containing all general data 
 * for the program
 * @param argc command line argument count
 * @param argv command line argument strings
 * @brief initializing t_philo_data struct
*/
void init_philo(t_data *data)
{
	int		i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->philo_count);
	if (data->philo == NULL)
		return ; //free error??
	i = 0;
	while (i < data->philo_count)
	{
		data->philo[i].p_id = i;
		//if id % 2 != 0;
		//left is right, right is left :) muhahhaha 
		data->philo[i].left_fork = &data->fork_array[i];
		//tenzij philo 0 = right fork = philo count
		data->philo[i].right_fork = &data->fork_array[i - 1];
		data->philo[i].times_eaten = 0;//needs to be -1?
		data->philo[i].time_of_death = 0;//needs to be -1?
		i++;
	}
}

/**
 * @param 
 * @param 
 * @param 
 * @brief routine of the philosophers
*/
void *routine(void *philo)
{
	//cast terug naar t_philo;
	//message think--->die?
	//lock left fork
	//message pick up left fork----> die?
	//lock right fork
	//message pick up right fork---> die?
	//message eating---> die?
	//unlock
	//message sleep---> die?
	//usleep
	return (NULL);
}
