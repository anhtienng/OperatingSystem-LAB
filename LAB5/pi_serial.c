#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv){
    int seed = time(NULL);
    if(argc<2){
        fprintf(stderr,"Usage: ./pi_serial numOfPoints\n");
        exit(1);
    }

    int numOfPoints = atoi(argv[1]);
    int numOfInCirclePoints = 0;

    if(numOfPoints <= 0){
        fprintf(stderr,"numOfPoints must be > 0\n");
        exit(1);
    }
    
    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC,&start);

    for (int i = 0; i < numOfPoints; i++){
        double x = (double)rand_r(&seed)/(double)RAND_MAX * 2 - 1;
        double y = (double)rand_r(&seed)/(double)RAND_MAX * 2 - 1;
        if (x*x + y*y <= 1)
            numOfInCirclePoints++;
    }

    double pi = 4*(double) numOfInCirclePoints / numOfPoints;
    
    clock_gettime(CLOCK_MONOTONIC,&finish);
    elapsed = (finish.tv_sec - start.tv_sec)*1e9;
    elapsed = (elapsed + (finish.tv_nsec - start.tv_nsec))*1e-9;
    printf("pi = %f\n",pi);
    printf("Time = %f sec\n",elapsed);
    return 0;
}

