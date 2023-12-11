/* multithreaded programs can execute parallel or concurrently
multiple sequences of statements that execute over the same period of time
parelell is two threads are executing statements at the same moment
concurrently is when the cpu is switching executing multiple threads*/

/* use pthread library */

#include <stdio.h>
#include <pthread.h>

void *computation(void *add);

void *computation(void *add)
{
	long sum = 0;
    long *add_num = (long *) (add);
	for (long i = 0; i < 1000000000, i++;)
		sum += *add_num;
    // printf("Add: %ld\n", *add_num);
    return (NULL);
}

int main ()
{
    pthread_t thread1;
	pthread_t thread2;
    long value1 = 1;
	long value2 = 2;

	// computation((void *) &value1);
	// computation((void *) &value2);
    //1st arg: passing pointer to pthread variable
    //2nd arg: to set attributes to the thread
    //3rd arg: function passed
    //4th arg: pass arguments to the function
	//pthread join is going to wait till it's done
	//executing with time (time ./a.out) joining before starting new thread seems to take longer
    /*pthread_create(&thread1, NULL, computation, (void *)&value1);
    pthread_join(thread1, NULL);
    pthread_create(&thread2, NULL, computation, (void *)&value2);
	pthread_join(thread2, NULL);*/
	pthread_create(&thread1, NULL, computation, (void *)&value1);
    pthread_create(&thread2, NULL, computation, (void *)&value2);
    
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	// 1st arg: thread that we're joining with main thread of execution
    // 2nd arg: could be used to work with return value from that function.
    return (0);
}
