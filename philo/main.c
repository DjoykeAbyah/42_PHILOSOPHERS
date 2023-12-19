/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 21:00:27 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/19 18:53:50 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_data			data;
	int 			i;
	int				j;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		init_data_struct(&data, argc, argv);
		init_philo(&data);
		while (i < data.philo_count)// i = philo_array
		{
			if (pthread_create(&data.philo[i].t_id, NULL, &routine, (void *)&data.philo[i]) != 0)
			{
				while (j < i)
				{
					if (pthread_join(data.philo[j].t_id, NULL) != 0)
						perror("Error at joining thread\n");
						j++;
				}
				perror("Error at creating thread\n");
			}
			i++;
		}
		i = 0;
		while (i < data.philo_count)
		{
			if (pthread_join(data.philo[i].t_id, NULL) != 0)
				perror("Error at joining thread\n");
			i++;
		}
	}
	else
		printf("please give ./philo nr nr nr nr nr");
}