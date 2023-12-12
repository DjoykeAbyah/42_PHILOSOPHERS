/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_threads.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/11 17:33:43 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/11 17:49:49 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 2;
// you can have multiple threads inside of a process
// all threads can access all variables whatever you do in 
// one thread will appear in the other.
void	*routine()
{
	x++;
	sleep(2);
	printf("value of x: %d\n", x);
}

void	*routine2()
{
	// x += 5;
	sleep(2);
	printf("value of x: %d\n", x);
}

int	main(int argc, char *arg[])
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, &routine, NULL))
		return (1);
	if (pthread_create(&t2, NULL, &routine2, NULL))
		return (2);
	if (pthread_join(t1, NULL))
		return (3);
	if (pthread_join(t2, NULL))
		return (4);
	return (0);
}
