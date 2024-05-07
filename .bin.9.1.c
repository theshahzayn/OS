#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h> 

#define NUM_THREADS 2

pthread_t threads[NUM_THREADS];

void sigusr1_handler(int signum){

    pid_t tid = syscall(SYS_gettid);
    pid_t pid = getpid();
    pid_t ppid = getppid();
    fprintf(stdout, "Thread %u received SIGUSR1 signal [parent=%u] [pid=%u] [tid=%u]\n", (unsigned int)pthread_self(), (unsigned int)ppid, (unsigned int)pid, (unsigned int)tid);
}

void *thread_function(void *arg){
    while (1) sleep(1);
    return NULL;
}

int main(){
    signal(SIGUSR1, sigusr1_handler);

    for(int i=0; i<NUM_THREADS; i++){
        if(pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    pid_t tid = syscall(SYS_gettid);
    pid_t pid = getpid();
    pid_t ppid = getppid();
    fprintf(stdout, "Parent process ID: %u, Process ID: %u, main() thread ID: %u\n", (unsigned int)ppid, (unsigned int)pid, (unsigned int)tid);
    fprintf(stdout, "Thread IDs: 0=%u, 1=%u\n", (unsigned int)threads[0], (unsigned int)threads[1]);

    kill(pid, SIGUSR1);
    pthread_kill(threads[0], SIGUSR1);

    for(int i = 0; i < NUM_THREADS; i++){
        if(pthread_join(threads[i], NULL) != 0){
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}


