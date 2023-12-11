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
int main(int argc, char *argv[])
{
    pthread_t t1;
    pthread_t t2;

    //pass pointer to the function &routine
    if (pthread_create(&t1, NULL, &routine, NULL) != 0)
        return (1);
    if (pthread_create(&t2, NULL, &routine, NULL) != 0)
        return (2);
    if (pthread_join(t1, NULL) != 0)
        return (3);
    if (pthread_join(t2, NULL) != 0)
        return (4);
    return 0;
}