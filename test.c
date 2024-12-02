#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t lock1;
pthread_mutex_t lock2;

void* test_function(void* arg) 
{
    int i = *(int *)arg;
    printf("i'm thread %d\n", i);
    if (pthread_mutex_lock(&lock1) != 0) {
        perror("Failed to lock lock1");
        return NULL;
    }
    printf("lock1 is locked.\n");
    if (pthread_mutex_lock(&lock1) != 0) {
        perror("Failed to lock lock1");
        return NULL;
    }
    printf("lock2 is locked.\n");
    printf("i'm thread %d\n", i);
    pthread_mutex_unlock(&lock1);
    printf("lock1 is unlocked.\n");
    pthread_mutex_unlock(&lock2);
    printf("lock2 is unlocked.\n");
    return NULL;
}
                                                                     
int main() 
{
    int i1 = 1;
    int i2 = 2;
    
    pthread_t thread1;
    pthread_t thread2;
    pthread_mutex_t locktmp;

    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    // pthread_mutex_init(&locktmp, NULL);
    // lock1 = &locktmp;
    // lock2 = &locktmp;

    if (pthread_create(&thread1, NULL, test_function, &i1) != 0) {
        perror("Failed to create thread");
        return EXIT_FAILURE;
    }
    if (pthread_create(&thread2, NULL, test_function, &i2) != 0) {
        perror("Failed to create thread");
        return EXIT_FAILURE;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&lock1);

    return 0;
}
