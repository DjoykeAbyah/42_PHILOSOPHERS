/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 21:01:11 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/19 15:38:41 by dreijans      ########   odam.nl         */
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

/**
 * @param philo_count amount of philo's passed from command line
 * @param fork_array array containing all mutexes
 * @param philosopher t_philo_data philospher containing everything
 * unique to that thread
 * @param time_to_die time allowed before philo dies, passed form 
 * commandline.
 * @param time_to_eat time allowed to eat before philo dies, passed from
 * commandline
 * @param time_to_sleep time philo is allowed to sleep
 * @param number_of_times_each_philosopher_must_eat number of times
 * each philo has to eat.
 * @brief struct containing general info of the program
*/
typedef struct s_data
{
	int					philo_count;
	pthread_mutex_t		*fork_array;
	t_philo_data		*philosopher;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
}			t_data;

/**
 * @param philo_id integer for each unique thread
 * @param left_fork mutex assigned as left fork unique to each philo
 * @param right_fork mutex assigned as right fork unique to each philo
 * @param times_eaten amount of times philo has eaten
 * @param time_of_death exact time philo passed away
 * @param data pointer to data struct containing all general info of the
 * @brief struct containing unique data for each philo(thread)
 * program
*/
typedef struct s_philo_data
{
	int					*philo_id;
	pthread_mutex_t		left_fork;//id;
	pthread_mutex_t		right_fork;//id -1;
	int					times_eaten;
	int					time_of_death;
	t_data				data;
}				t_philo_data;

void 			init_struct_philo(t_data *data, int argc, char **argv);
static	int		ft_iswhitespace(char c);
long int		ft_atoi(const char *str);
void 			*routine()

#endif
