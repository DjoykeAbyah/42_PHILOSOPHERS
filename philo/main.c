/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 21:00:27 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/18 17:59:12 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine()
{
	//message think--->die?
	//lock left fork
	//message pick up left fork----> die?
	//lock right fork
	//message pick up right fork---> die?
	//did you die?
	//message eating---> die?
	//unlock
	//message sleep---> die?
	//usleep
	//did you die?
}

int main(int argc, char **argv)
{

	t_data			data;
	t_philo_data 	*philo_data;
	int 			i;

	i = 0;
	init_struct_philo(&data, argc, argv);
	philo_data = NULL;
	if (argc == 5 || argc == 6)
	{
		while (i < data.philo_count)
		{
			//make forks amount of philo_count pthread_t for araay. loopen
			//init philo_data<--- assign forks
			i++;
		}
		while (i < data.philo_count)// i = philo_array
		{
			if (pthread_create(&philo_data->philo_id[i], NULL, &routine, NULL) != 0)
				perror("Error at creating thread\n")
				//if wronk join untill i (last create);
			i++;
		}
		i = 0;
		while (i < data.philo_count)// use the for join for mutex for lock yey for wronk yes
		{
			if (pthread_join(&philo_data->philo_id[i], NULL) != 0)
				perror("Error at joining thread\n");
			i++;
		}
	}
	else
		printf("please give ./philo nr nr nr nr nr");
}