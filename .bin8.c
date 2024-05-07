#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

int sum = 0;

void *runner(void *parameters){
	int i;
	int upper = *((int *)parameters);
	if (upper>0){
		for (i=1; i<=upper; i++){
		sum = sum+i;
		}
	}	
	pthread_exit(0);
}

int main(int argc, char* argv[]){
	
	pthread_t threadId;
	pthread_attr_t attributes;
	int num = 5;
	void *exit_status;
	
	pthread_attr_init(&attributes);
pthread_create(&threadId, &attributes, runner, (void *)&num);
pthread_join(threadId, &exit_status);
	printf("sum=%d\nThread Exit with status %ld",sum, (long)exit_status);	
	exit(0);
}

