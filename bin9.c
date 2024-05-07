#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void handler(int num){

	printf("I won't die: %d\n", num);
}
int main(){
	signal(SIGINT, handler);

	while(1){
	printf("wasting your cycle %d\n", getpid());
	sleep(1);
	}
}


/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

void childSignalHandler(int signum){
    printf("Child process signal. Creating folder.\n");
    
    char FN[256];
    printf("Folder name: ");
    scanf("%s", FN);
    
    char fn[256];
    snprintf(fn, sizeof(fn), "%s_@_$_%d", FN, getpid());

    if(mkdir(fn, 0777) == -1){
        perror("mkdir");
        exit(EXIT_FAILURE);
    }

    printf("Folder with name %s created successfully.\n", fn);
    exit(EXIT_SUCCESS);
}

int main(){
    signal(SIGUSR1, childSignalHandler);

    pid_t pid = fork();

    if(pid == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }else if(pid == 0){
        printf("Child process created.\n");
        kill(getppid(), SIGUSR1);
        exit(EXIT_SUCCESS);
    }else{
        printf("Parent waiting for childp termination.\n");
        wait(NULL);
    }

    return 0;
}

*/

