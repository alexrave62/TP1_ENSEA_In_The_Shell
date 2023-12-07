#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>


#define WELCOME "Bienvenue dans le Shell ENSEA.\nPour quitter, taper 'exit'.\n"
#define PROMPT "enseash %% "
#define GOODBYE "Bye Bye ...\n"
#define BUFSIZE 200

int main (){
	//Initialisation of variables
    char buf[BUFSIZE];
    int status;
    pid_t ret;
    ssize_t len_com;
    pid_t wpid;
    char info[BUFSIZE];
    struct timespec start_time, end_time;
    long execution_time;

    //Welcoming message
	write(STDOUT_FILENO,WELCOME,strlen(WELCOME));
	write(STDOUT_FILENO,PROMPT,strlen(PROMPT));
	
    // Command loop
	while (1){

        //Buffer reset
		for (int i=0; i<BUFSIZE; i++){buf[i]='\0';}
		
		//Command reading
		len_com = read(STDIN_FILENO, buf, BUFSIZE);	
		if (len_com < 0){return EXIT_FAILURE;}				//error test
		if (len_com == 0){return EXIT_FAILURE;}				//no command
		buf[len_com-1] = '\0';					
		
		//Commande evaluation
		ret = fork();

        //start clock after creating fork
        if (clock_gettime(CLOCK_MONOTONIC, &start_time)){perror("clock_gettime");exit(EXIT_FAILURE);}   

		if (ret==-1){exit(EXIT_FAILURE);}					//error test
        
        //parent
		if (ret !=0) {   

            //exit if 'exit' command
			if (strcmp(buf,"exit")==0){						
				write(STDOUT_FILENO,GOODBYE,strlen(GOODBYE));
				exit(EXIT_SUCCESS);}
			wpid = waitpid(ret,&status,0);                  
            
            //get time after the execution to calculate the execution time in ms
            if (clock_gettime(CLOCK_MONOTONIC, &end_time)){perror("clock_gettime");exit(EXIT_FAILURE);}
            execution_time = (end_time.tv_sec-start_time.tv_sec)*1e3 +(end_time.tv_nsec-start_time.tv_nsec)/1e6;    
            
            // Return of exit or signal code and execution time
            if (wpid == -1) {exit(EXIT_FAILURE);}
            if (WIFEXITED(status)) {
				sprintf(info,"enseash [exit:%d|%ld ms] %%",WEXITSTATUS(status),execution_time);
                } 
            else if (WIFSIGNALED(status)) {
				sprintf(info,"enseash [sign:%d|%ld ms] %%",WTERMSIG(status),execution_time);
            }
            write(STDOUT_FILENO,info,strlen(info));
        }
        
        //child  
		else {                                               
        // Execution of command                                  
            execlp(buf,buf, (char *)NULL);
            exit(EXIT_SUCCESS);
            }
	}
	return 0;
 }
