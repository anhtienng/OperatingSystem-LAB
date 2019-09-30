#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_THREADS 8
void *calPi (void *param);
int range;

int main(int argc,char *argv[])
{
    if (argc != 2)
    {
        printf("Wrong input!\n");
        exit(1);
    }
    if (atoll(argv[1])<=0)
    {
        printf("Input must larger than 0\n");
        exit(1);
    }
    pthread_t threads[NUM_THREADS];
    int counts[NUM_THREADS] = {};
    int inCircle = 0;
    int totalPoint = atoll(argv[1]);
    range = totalPoint/NUM_THREADS;
    
    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC,&start);
    
    for (int i =0;i<NUM_THREADS;i++)
        pthread_create(&threads[i],NULL,calPi,&counts[i]);

    for (int i=0;i<NUM_THREADS;i++)
    {
        pthread_join(threads[i],NULL);
        inCircle = inCircle + counts[i];
    }
    double pi = 4.0 * (double)inCircle/(double)totalPoint;
    
    printf("pi = %f\n",pi);
    clock_gettime(CLOCK_MONOTONIC,&finish);
    elapsed = (finish.tv_sec - start.tv_sec)*1e9;
    elapsed = (elapsed + (finish.tv_nsec - start.tv_nsec))*1e-9;
    printf("Time = %f sec\n",elapsed);
}
void *calPi (void *param)
{
    int *count = (int*) param;
    int seed = time(NULL);
    for (int i = 0;i<range;i++)
        {
            double x = (double)rand_r(&seed)/(double)RAND_MAX * 2 + -1;
            double y = (double)rand_r(&seed)/(double)RAND_MAX * 2 + -1;
            if ((x*x+y*y) <= 1) *count = *count +1;
        }
    pthread_exit(0);
}

