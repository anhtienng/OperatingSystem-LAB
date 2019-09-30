#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define NUM_OF_THREADS 8

pthread_t threads[NUM_OF_THREADS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
volatile long long numOfInCirclePoints = 0;

void *runner(void *arg)
{
    long long num = (long long)arg;
    unsigned int rand_state = rand();
    long long numInCircle = 0;
    for (int i = 0; i < num; i++)
    {
        double x = (double)rand_r(&rand_state) / RAND_MAX * 2 + -1;
        double y = (double)rand_r(&rand_state) / RAND_MAX * 2 + -1;
        if (x * x + y * y <= 1)
        {
            numInCircle++;
        }
    }
    pthread_mutex_lock(&mutex);
    numOfInCirclePoints += numInCircle;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: ./pi_multithread numOfPoints\n");
        exit(1);
    }

    long long numOfPoints = atoll(argv[1]);

    if (numOfPoints <= 0)
    {
        fprintf(stderr, "numOfPoints must be > 0\n");
        exit(1);
    }

    double pi;
    long long numOfPointsPerThread = numOfPoints / NUM_OF_THREADS;
    
    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC,&start);

    for (int i = 0; i < NUM_OF_THREADS - 1; i++)
    {
        pthread_create(&threads[i], NULL, runner, (void *)numOfPointsPerThread);
    }
    long long num = numOfPoints - (NUM_OF_THREADS - 1) * numOfPointsPerThread;
    pthread_create(&threads[NUM_OF_THREADS - 1], NULL, runner, (void *)num);

    for (int i = 0; i < NUM_OF_THREADS; i++)
        pthread_join(threads[i], NULL);

    pi = 4 * (double)numOfInCirclePoints / numOfPoints;
    
    clock_gettime(CLOCK_MONOTONIC,&finish);
    elapsed = (finish.tv_sec - start.tv_sec)*1e9;
    elapsed = (elapsed + (finish.tv_nsec - start.tv_nsec))*1e-9;
    
    fprintf(stdout, "pi = %f\n", pi);
    fprintf(stdout, "time = %f\n", elapsed);

    return 0;
}
