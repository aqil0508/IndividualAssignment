//NAME:MUHAMMAD AQIL BIN ABDUL RAHMAN
//STUDENT ID:2022780335
//GROUP:CS2514A
//INDIVIDUAL ASSIGNMENT (ITT440)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

 
 void sigint_handler(int sig)
 {
 	printf("Dont't interrupt the process \n");
 }
 
int main()
{
    
    if (signal(SIGINT,sigint_handler)== SIG_ERR){
    	perror("signal");
    	exit(1);
	}
    int fd1[2]; 
 
    char input_str[100];
    pid_t p;
 
    if (pipe(fd1) == -1) {
        perror("Pipe");
        return 1;
    }
      	printf("\nEnter a word : ");
        scanf("%s", input_str);
    
    for(int i = 0; i < 3 ; i++){
	
    p = fork();
 
    if (p < 0) {
        perror("fork");
        return 1;
    }
 
    // Parent process
    else if (p > 0) {
        
       
        write(fd1[1], input_str, strlen(input_str) + 1);
        
        printf("\n\nParent sending word '%s' to child        => PID=%d \n", input_str, getpid());
        sleep(4);
     
    }
 
    // child process
    else {
    	
      	char buffer_str[100];
        close(fd1[1]); 
 
        sleep(2);
        read(fd1[0], buffer_str, 100);
        printf("Child received word '%s' from parent     => PPID=%d  PID=%d  \n\n\n", buffer_str, getppid(), getpid());
        close(fd1[0]);
 
        exit(0);
    }
    }
}