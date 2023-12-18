/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 21:01:11 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/18 17:06:57 by dreijans      ########   odam.nl         */
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

typedef struct s_data
{
	int					philo_count;
	pthread_mutex_t		*fork_array;
	pthread_t			*philo_array;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
}			t_data;


typedef struct s_philo_data
{
	int					*philo_id;
	pthread_mutex_t		left_fork;//id;
	pthread_mutex_t		right_fork;//id -1;
	int					times_eaten;
	int					time_of_death;
}				t_philo_data;

void 			init_struct_philo(t_data *data, int argc, char **argv);
static	int		ft_iswhitespace(char c);
long int		ft_atoi(const char *str);

#endif

//data struct to compare philo data with.
//what do i need from where
//what do the philosophers need
