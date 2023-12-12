/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cv_practice.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/11 17:22:26 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/11 17:33:14 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *routine()
{
	printf("test threads\n");
	sleep(3);
	printf("ending thead\n");
}

// add -pthread to the gcc command or in your task file
// gcc -g -pthread cv_practice.c -o main
int	main(int argc, char *argv[])
{
	pthread_t	t1;
	pthread_t	t2;

	//pass pointer to the function &routine and pthread varable
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	//sort of wait for threads, pass the thread you want to wait for
	if (pthread_join(t1, NULL) != 0)
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	return (0);
}
