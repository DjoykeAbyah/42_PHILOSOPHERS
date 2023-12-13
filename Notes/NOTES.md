int x = 2;

void *routine()
{
    x++;
    sleep(2);
    printf("value of x: %d\n", x);
}
void *routine2()
{
    sleep(2);
    printf("value of x: %d\n", x);
}

int main(int argc, char *arg[])
{
    pthread_t t1;
	pthread_t t2;

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

PHILOSOPHERS on  main [?] 
➜ ./a.out
value of x: 3
value of x: 3

because it uses the same variable it's incremented at both becayse thread2 is using the incremented x.

if you do anything in one thread it will be displayed in both

