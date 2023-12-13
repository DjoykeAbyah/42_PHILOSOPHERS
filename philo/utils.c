/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 17:46:34 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/13 17:56:29 by dreijans      ########   odam.nl         */
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

t_philo *init_struct_philo(int argc, char **argv)
{
	t_philo *philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		perror("malloc");
	philo->philo_input_count = ft_atoi(argv[1]);//needs to compare or be number_of_philosopers
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	return (philo);
}