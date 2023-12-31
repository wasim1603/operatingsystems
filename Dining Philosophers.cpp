#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (philosopher + 4) % N
#define RIGHT (philosopher + 1) % N

sem_t mutex;
sem_t S[N];

int state[N];
int phil[N] = {0, 1, 2, 3, 4};

void test(int philosopher) {
    if (state[philosopher] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[philosopher] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n", philosopher + 1, LEFT + 1, philosopher + 1);
        printf("Philosopher %d is Eating\n", philosopher + 1);
        sem_post(&S[philosopher]);
    }
}

void grabFork(int philosopher) {
    sem_wait(&mutex);
    state[philosopher] = HUNGRY;
    printf("Philosopher %d is Hungry\n", philosopher + 1);
    test(philosopher);
    sem_post(&mutex);
    sem_wait(&S[philosopher]);
    sleep(1);
}

void putFork(int philosopher) {
    sem_wait(&mutex);
    state[philosopher] = THINKING;
    printf("Philosopher %d puts fork %d and %d down\n", philosopher + 1, LEFT + 1, philosopher + 1);
    printf("Philosopher %d is thinking\n", philosopher + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void *philosopherAction(void *num) {
    while (1) {
        int *i = num;
        sleep(1);
        grabFork(*i);
        sleep(1);
        putFork(*i);
    }
}

int main() {
    int i;
    pthread_t thread_id[N];

    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);

    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopherAction, &phil[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    return 0;
}

