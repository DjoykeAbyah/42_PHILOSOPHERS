#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int mails = 0;

/* race condition
	1. read mails
	2. increment value
	3. write mails back to memory 
	in one process it could read what is stored in the CPU register
	not in the memory which could be different to what is
	in the memory. one thread could be stuck at 23 while
	the other is at 30 and when the one wirtes 24 it will become
	instead of 31.
	If you compile with -S you can see in assembly 
	how much actions are done in a function
	- why only at big numbers?
	you don't have interleaving because its fast enough with small
	numbers to execute before starting the other thread.
	change of happening is lower but we cannot have the risk of
	data races.
*/
void *routine()
{
	for (int i = 0; i < 1000000; i++)
		mails++;
}

/* add -pthread to the gcc command or in your task file
	or gcc -g -pthread cv_practice.c -o main

	pass pointer to the function &routine and pthread varable
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);

	sort of wait for threads, pass the thread you want to wait for
	if (pthread_join(t1, NULL) != 0)
		return (3);
*/
int	main(int argc, char *argv[])
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	printf("number of mails %d\n", mails);
	return (0);
}

/*-----------------how to solve the data race?------------------*/

int mails = 0;
pthread_mutex_t mutex;

/*
	1. read mails
	2. increment value
	3. write mails back to memory
*/
void *routine()
{
	for (int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}

/* add -pthread to the gcc command or in your task file
	or gcc -g -pthread cv_practice.c -o main

	solve the race by using a mutex
	a lock around a section of code.

	locking and unlocking mutexes is protecting parts of code against
	other threads executing it at the same time.
	we want correct data but if we do this why not just have one process?
	this is just an example of how to use mutexes.
	race condition can only happen on a multi core processor.
*/
int	main(int argc, char *argv[])
{
	pthread_t	t1;
	pthread_t	t2;
	pthread_t	t3;
	pthread_t	t4;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_create(&t3, NULL, &routine, NULL) != 0)
		return (3);
	if (pthread_create(&t4, NULL, &routine, NULL) != 0)
		return (4);
	if (pthread_join(t1, NULL) != 0)
		return (5);
	if (pthread_join(t2, NULL) != 0)
		return (6);
	if (pthread_join(t3, NULL) != 0)
		return (7);
	if (pthread_join(t4, NULL) != 0)
		return (8);
	pthread_mutex_destroy(&mutex);
	printf("number of mails %d\n", mails);
	return (0);
}


/*-----------------how to create threads in a loop----------------*/


int mails = 0;
pthread_mutex_t mutex;

/*
	1. read mails
	2. increment value
	3. write mails back to memory
*/
void *routine()
{
	for (int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}

/* add -pthread to the gcc command or in your task file
	or gcc -g -pthread cv_practice.c -o main
	don't create and join in the same loop, else you wont really have a multi
	threaded program.

	the messages is not really the way it executes the order. it's just
	how we print.
	the messages correspond of the way we go over the list 
	of threads, not the order
	yhey finishe execution
*/
int	main(int argc, char *argv[])
{
	pthread_t	th[8];
	int			i;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < 8)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("failed to create thread");
			return (1);
		}
		printf("thread %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (2);
		printf("thread %d has finished execution\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("number of mails %d\n", mails);
	return (0);
}

/*---------------- get return value from a thread --------------*/

#include <time.h>

/*
	we need to allocate the return value because else
	it will be deallocated when leaving this function because 
	it's on the stack.

	allocate and deallocate in the same function.
*/
void *roll_dice()
{
	int	value;
	int	*result;

	result = malloc(sizeof(int));
	value = (rand() % 6) + 1;
	*result = value;
	// printf("%d\n", value);
	printf("thread result: %p\n", result);
	return ((void *)result);
}

/* add -pthread to the gcc command or in your task file
	or gcc -g -pthread cv_practice.c -o main

	thread result: 0x7f0b64000b70
	main result: 0x7f0b64000b70
	result: 4
*/
int	main(int argc, char *argv[])
{
	pthread_t	th[8];
	int			*result;
	int			i;

	i = 0;
	srand(time(NULL));
	while (i <= 8)
	{
		if (pthread_create(&th[i], NULL, &roll_dice, NULL) != 0)
			return (1);
		printf("process created %d\n", i);
		i++;
	}
	i = 0;
	while (i <= 8)
	{
		if (pthread_join(th[i], (void **)&result) != 0)
			return (2);
		printf("process ended %d\n", i);
		i++;
	}
	printf("main result: %p\n", result);
	printf("result: %d\n", *result);
	free(result);
	return (0);
}

/*------------------ how to pass arguments to threads -----------*/

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*routine(void *arg)
{
	int	index;

	index = *(int *)arg;
	printf("%d ", primes[index]);
	free(arg);

}

/*
	we're passing memory adresses instead of values
	the value at those adresses could change in the meantime

	don't free in the same if statement the thread is created,
	thread is created but the new thread that wants to allocated
	wants to use the variable that's already freed

*/
int	main(int argc, char **argv)
{
	pthread_t	th[10];
	int			i;

	for (int i = 0; i < 10; i++)
	{
		int	*a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
		{
			perror("failed to create thread");
			return (1);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("failed to join thread");
			return (2);
		}
	}
}

/*----------practical example for using threads---------*/

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*routine(void *arg)
{
	int	index;
	int	sum;

	index = *(int *)arg;
	sum = 0;
	for(int j = 0; j < 5; j++)
		sum += primes[index + j];
	printf("localsum :%d\n", sum);
	*(int *)arg = sum;
	return (arg);

}

/*
	sum computed in multithreaded way
*/
int	main(int argc, char **argv)
{
	pthread_t	th[2];
	int			i;

	for (int i = 0; i < 2; i++)
	{
		int	*a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
		{
			perror("failed to create thread");
			return (1);
		}
	}
	int globalsum = 0;
	for (int i = 0; i < 2; i++)
	{
		int *result;
		if (pthread_join(th[i], (void **)&result) != 0)
		{
			perror("failed to join thread");
			return (2);
		}
		globalsum += *result;
		free(result);
	}
	printf("global sum: %d\n", globalsum);
	return (0);
}

/*-----------------difference between lock and trylock----------------------*/

pthread_mutex_t	mutex;

/*
	all 4 threads ar execution this 
	function but only 1 will lock that mutex 
	and the others have to wait
	when that first thread unlocks the second mutex another can lock it etc.
*/
void *routine(void *arg)
{
	pthread_mutex_lock(&mutex);
	printf("got the lock\n");
	sleep(1);
	pthread_mutex_unlock(&mutex);
}

int main(int argc, char **argv)
{
	pthread_t th[4];

	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 4; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("Error at creating thread\n");
	}
	for (int i = 0; i < 4; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Error at joining thread\n");
	}
}

/*------------------deadlocks------------------------*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 8

pthread_mutex_t mutexfuel;
int fuel = 50;
pthread_mutex_t mutexwater;
int water = 10;

/*
	if you do the lock twice the process will never finish
	locking a mutex 2nd time in a tread will block it

	the issue is if we have multiple locks locked in different orders
	our threads are waiting for the others to unlock it so it can be used 
	
*/
void	*routine(void *args)
{
	if (rand() %2 - 0)
	{		
		pthread_mutex_lock(&mutexfuel);
		sleep(1);
		pthread_mutex_lock(&mutexwater);
	}
	else
	{		
		pthread_mutex_lock(&mutexwater);
		sleep(1);
		pthread_mutex_lock(&mutexfuel);
	}
	fuel += 50;
	water = fuel;
	printf("increment fuel to: %d set water to %d\n", fuel, water);
	pthread_mutex_unlock(&mutexfuel);
	pthread_mutex_unlock(&mutexwater);
}

int	main(int argc, char **argv)
{
	pthread_t	th[THREAD_NUM];
	int			i;
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("failed to create thread\n");
	}
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("failed to join thread\n")
	}
	return (0);
}

lock and unlock everytime you you print a message
struct for timing
mutex locks part of the function that no other threads can use it
one philo get's one fork so he dies thats oke
sleeping is usleep as many seconds as specified
gettimeofday function to keep up how long program takes