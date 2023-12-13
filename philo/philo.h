/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 21:01:11 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/13 17:53:50 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

typedef struct s_philo
{
	int					philo_input_count;
	// pthread_t			number_of_philosophers[6];//200
	pthread_mutex_t		forks[6];//200
	pthread_t			death_checker;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
}			t_philo;


typedef struct s_philo_data
{
	pthread_t			number_of_philosophers[6];//200
	// int					number_eat;
}				t_philo_data;

t_philo 		*init_struct_philo(int argc, char **argv);
static	int		ft_iswhitespace(char c);
long int		ft_atoi(const char *str);

#endif

//data struct to compare philo data with.