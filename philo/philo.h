/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 21:01:11 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/29 20:57:17 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;

/**
 * @param philo_count amount of philo's passed from command line
 * @param fork_array array containing all mutexes
 * @param philosopher t_philo philospher containing unique to philo data
 * @param time_to_die time allowed before philo dies
 * @param time_to_eat time allowed to eat before philo dies
 * @param time_to_sleep time philo is allowed to sleep
 * @param number_of_times_each_philosopher_must_eat number of times
 * each philo has to eat.
 * @brief struct containing general info of the program
*/
typedef struct s_data
{
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					eat_count;
	bool				stop_monitor;
	t_philo				*philo;
	pthread_mutex_t		*fork_array;
	pthread_mutex_t		printing;
	pthread_mutex_t		eating;
	pthread_mutex_t		monitor;
	long int			start_time;
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
typedef struct s_philo
{
	pthread_t			t_id;
	int					p_id;
	int					times_eaten;
	int					time_of_death;
	long int 			last_eat;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
}		t_philo;

//init.c
t_data			*init_data_struct(t_data *data, int argc, char **argv);
void			init_philo(t_data *data);
void			init_data_mutexes(t_data *data);
void			init_fork_array(t_data *data);
void			free_fork_array(t_data *data, int i);

//utils.c
void			*ft_calloc(size_t count, size_t size);
void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *b, int c, size_t len);
long int		ft_atoi(const char *str);
int				ft_iswhitespace(char c);
int				ft_isdigit(int c);
int long		get_current_time(void);
int long		time_stamp(t_philo *philo);
void			print_message(t_philo *philo, char *message);
bool			death_check(t_philo *philo);
bool			stop_boolean_check(t_philo *philo);
int				ft_strcmp(const char *s1, const char *s2);

//routine.c
void			*routine(void *philosopher);
void			thinking(t_philo *philo);
void			sleeping(t_philo *philo);
void			eating(t_philo *philo);

#endif
