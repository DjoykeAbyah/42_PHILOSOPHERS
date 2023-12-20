/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 17:46:34 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/20 19:00:56 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @param c int to be checked
 * @brief checks characters for numeric characters
*/
static	int	ft_isdigit(int c)
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

static void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*charb;
	size_t			i;

	i = 0;
	charb = b;
	while (i < len)
	{
		*charb = (unsigned char)c;
		charb++;
		i++;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*aloc_mem;

	aloc_mem = malloc(count * size);
	if (aloc_mem == NULL)
	{
		return (NULL);
	}
	ft_bzero(aloc_mem, (count * size));
	return (aloc_mem);
}

/**
 * @param data data struct containing all general data 
 * for the program
 * @param argc command line argument count
 * @param argv command line argument strings
 * @brief initializing data struct and filling mutex array.
 * @todo remove comments, check
*/
// void	init_data_struct(t_data *data, int argc, char **argv)
t_data	*init_data_struct(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	data = ft_calloc(sizeof(t_data), 1);
	if (data == NULL)
		perror("calloc went wrong");
	data->start_time = get_current_time();
	data->philo_count = ft_atoi(argv[1]);
	data->fork_array = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (data->fork_array == NULL)
		return (NULL);//return iets anders/free?
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
	return (data);
}

/**
 * @param data data struct containing all general data 
 * for the program
 * @param argc command line argument count
 * @param argv command line argument strings
 * @brief initializing t_philo_data struct
 * @todo remove comments, check return values
*/
void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->philo_count);
	if (data->philo == NULL)
		return ;
	if (i == 0)
	{
		data->philo[0].p_id = i;
		data->philo[0].right_fork = &data->fork_array[data->philo_count];
		data->philo[0].left_fork = &data->fork_array[0];
		data->philo[0].times_eaten = 0;//needs to be -1?
		data->philo[0].time_of_death = 0;//needs to be -1?
		data->philo[0].data = data;
		i++;
	}
	while (i < data->philo_count)
	{
		data->philo[i].p_id = i;
		if (i % 2 != 0)
		{
			data->philo[i].right_fork = &data->fork_array[i];
			data->philo[i].left_fork = &data->fork_array[i - 1];
		}
		else
		{
			data->philo[i].left_fork = &data->fork_array[i];
			data->philo[i].right_fork = &data->fork_array[i - 1];
		}
		data->philo[i].times_eaten = 0;//needs to be -1?
		data->philo[i].time_of_death = 0;//needs to be -1?
		data->philo[i].data = data;
		i++;
	}
}
