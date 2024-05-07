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
