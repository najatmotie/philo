#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t *forks;

void test_function(int i) 
{
    printf("I'm philosopher %d\n", i);
    sem_wait(forks);
    printf("Philosopher %d: Semaphore is locked.\n", i);
    sleep(1);
    sem_post(forks);
    printf("Philosopher %d: Semaphore is unlocked.\n", i);
    exit(0);
}
                                                                     
int main() 
{
    int i = 0;
    pid_t philo[4];
    forks = sem_open("/fork", O_CREAT, 0666, 4);
    while(i < 4)
    {
        philo[i] = fork();
        if(philo[i] == 0)
            test_function(i);
        i++;
    }
    for (i = 0; i < 4; i++){
        waitpid(philo[i], NULL, 0);
    }
	sem_unlink("/fork");
    sem_close(forks);
}
