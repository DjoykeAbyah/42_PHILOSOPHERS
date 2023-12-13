/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 21:00:27 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/13 17:53:31 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine()
{
	//eat
	//did you die?
	//sleep
	//did you die?
	//think
	//did you die?
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

int main(int argc, char **argv)
{

	t_philo			*philo;
	t_philo_data 	*philo_data;
	int 			i;

	i = 0;
	philo = init_struct_philo(argc, argv);
	if (argc == 5 || argc == 6)
	{
		pthread_mutex_init(philo->forks, NULL);
		while (i < philo->philo_input_count)
		{
			if (pthread_create(&philo_data->number_of_philosophers[i], NULL, &routine, NULL) != 0)
				perror("Error at creating thread\n");
			i++;
		}
		i = 0;
		(i < philo->philo_input_count)
		{
			if (pthread_join(&philo_data->number_of_philosophers[i], NULL) != 0)
				perror("Error at joining thread\n");
			i++;
		}
	}
	else
		printf("please give ./philo nr nr nr nr nr");
}