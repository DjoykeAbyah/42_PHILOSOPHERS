/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_process.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/11 17:33:35 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/11 17:35:54 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int	main(int argc, char *arg[])
{
	int	x;
	int	pid;

	x = 2;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		x++;
	sleep (2);
	printf("value of x: %d\n", x);
	// printf("process id: %d\n", getpid());
	if (pid != 0)
		wait(NULL);
	return (0);
}
