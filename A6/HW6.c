//
//  HW6.c
//  
//
//  Created by Lili Peng on 12/3/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <time.h>

static volatile int counter = 0;
int threshold;
pthread_mutex_t lock;

void *mythread(void *arg) {
    printf("%s: begin\n", (char*)arg);
    int i;
    int localCounter = 0;
    
    for (i = 0; i < 10000000; i++)
    {
        localCounter++;
        if (localCounter == threshold) {
            pthread_mutex_lock(&lock);
            counter = counter + threshold;
            pthread_mutex_unlock(&lock);
            localCounter = 0;
        }
    }
    return NULL;
}

int
main (int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("usage: name number\n");
        return 0;
    }
    threshold = atoi(argv[1]);
    pthread_t p1,p2,p3,p4,p5;
    int pres = pthread_mutex_init(&lock, NULL);
    printf("pres = %d\n", pres);
    int rc;
    
    printf("main: begin\n");
    
    // Start recording time
    clock_t t;
    t = clock();
    
    rc = pthread_create(&p1, NULL, mythread, "A");
    rc = pthread_create(&p2, NULL, mythread, "B");
    rc = pthread_create(&p3, NULL, mythread, "C");
    rc = pthread_create(&p4, NULL, mythread, "D");
    rc = pthread_create(&p5, NULL, mythread, "E");
    
    rc = pthread_join(p1, NULL);
    rc = pthread_join(p2, NULL);
    rc = pthread_join(p3, NULL);
    rc = pthread_join(p4, NULL);
    rc = pthread_join(p5, NULL);
    
    printf("counter = %d\n", counter);
    
    // Calculate the time it takes for counting this threshold
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("main: end\n");
    printf("processed time: %f seconds\n", time_taken);
    return 0;
}
