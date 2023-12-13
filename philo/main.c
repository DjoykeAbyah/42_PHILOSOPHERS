/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 21:00:27 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/13 18:49:50 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine()
{
	//mutex lock
	//eat
	//did you die?
	//mutx unlock
	//sleep
	//did you die?
	//think
	//did you die?
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
		while (i < philo->philo_input_count)
		{
			//create mutex array.
			//assign forks to the philosopher
			pthread_mutex_init(philo->forks, NULL);// how do  I set the forks to the actual number?
			i++;
		}
		while (i < philo->philo_input_count)
		{
			if (pthread_create(&philo->number_of_philosophers[i], NULL, &routine, NULL) != 0)
				perror("Error at creating thread\n");
			i++;
		}
		i = 0;
		while (i < philo->philo_input_count)
		{
			if (pthread_join(&philo->number_of_philosophers[i], NULL) != 0)
				perror("Error at joining thread\n");
			i++;
		}
	}
	else
		printf("please give ./philo nr nr nr nr nr");
}