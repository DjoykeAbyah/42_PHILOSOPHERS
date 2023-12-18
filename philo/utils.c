/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 17:46:34 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/18 19:17:02 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	ft_iswhitespace(char c)
{
	return (c == ' ' || ((c >= 9 && c <= 13)));
}

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

void init_struct_philo( t_data *data, int argc, char **argv)
{
	int		i;

	i = 0;
	data->philo_count = ft_atoi(argv[1]);
	while (i <= data->philo_count)
	{
		//mutex create silly not with int
		data->fork_array = i;
		i++;
	}
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
}

void init_philo( t_data *data, int argc, char **argv)
{
	int		i;

	i = 0;
	data->philosopher = malloc(sizeof(t_philo_data) * data->philo_count + 1);
	//if null meh
	//return something
	//while data->philospher[i] != data_philo_count
		//philo_data_left fork is fork_array[i] 
		//right fork is philo[i] - 1
		//i++;
}