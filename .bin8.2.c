#include<pthread.h>
#include<stdio.h>

static volatile int count = 0;

void *mythread(void *arg){
	printf("%s: begin\n", (char *)arg);
	int i;
	for(i=0; i<20; i++){
	count = count+1;
	}
	printf("%s:done. Counter = %d\n", (char *)arg, count);
	
	return NULL;
}

int main(int argc, char* argv[]){

	pthread_t p1, p2;
	
	printf("main: begin (counter = %d)\n", count);
	pthread_create(&p1, NULL, mythread, "A");
	pthread_create(&p2, NULL, mythread,"B");
	
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	
	printf("main: done with both (counter = %d)\n", count);
	return 0;

}


/*

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t m;

void *table(void *num){
    int n = *((int *)num);

    pthread_mutex_lock(&m);

    for(int i=1; i<=1000; i++){
        printf("%d x %d = %d\n", n, i, i * n);
    }

    pthread_mutex_unlock(&m);

    return NULL; 
}

int main(){
    pthread_mutex_init(&m, NULL);

    pthread_t t[4];
    int rc;

    for(int i=0; i<4; i++){
        int num = 5 + i;
        rc = pthread_create(&t[i], NULL, table, &num); 
        if(rc != 0){
            printf("Error: Thread not created\n");
        }
    }

    for(int i = 0; i < 4; i++){
        pthread_join(t[i], NULL);
        if(rc != 0) {
            printf("Error: Thread not exited\n");
        }
    }
    pthread_mutex_destroy(&m);

    return 0;
}

*/
