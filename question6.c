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
	//Message d'accueil
	write(STDOUT_FILENO,WELCOME,strlen(WELCOME));
	write(STDOUT_FILENO,PROMPT,strlen(PROMPT));
	// boucle de commande
	char buf[BUFSIZE];
    ssize_t len_com;
    int status;
    pid_t ret;
    pid_t wpid;
    struct timespec start_time, end_time;
    long execution_time;
    char info[BUFSIZE];   
    char *command[BUFSIZE];
    int command_count=0; 
	while (1){
		//Réinitialization of the buffer
		for (int i=0; i<BUFSIZE; i++){buf[i]='\0';command[i]='\0';}
        command_count=0;		
		//lecture commande complexe
		len_com = read(STDIN_FILENO, buf, BUFSIZE);	
		if (len_com < 0){return EXIT_FAILURE;}				//error test
		if (len_com == 0){return EXIT_FAILURE;}				//pas de commande
        buf[len_com-1] = '\0';
        char *letter = strtok(buf, " ");
        while (letter != NULL) {
            command[command_count++] = letter;
            letter = strtok(NULL, " ");    }
        command[command_count] = NULL; // La liste d'arguments doit se terminer par NULL					
		
		//Evaluation commande
		ret = fork();
        //start clock after creating fork
        if (clock_gettime(CLOCK_MONOTONIC, &start_time)){perror("clock_gettime");exit(EXIT_FAILURE);}   
		if (ret==-1){exit(EXIT_FAILURE);}					//error test
		if (ret !=0) {                                      
            //parent
            //exit if 'exit' command
			if (strcmp(buf,"exit")==0){						
				write(STDOUT_FILENO,GOODBYE,strlen(GOODBYE));
				exit(EXIT_SUCCESS);}
			wpid = waitpid(ret,&status,0);                  
            
            if (clock_gettime(CLOCK_MONOTONIC, &end_time)){perror("clock_gettime");exit(EXIT_FAILURE);}
            execution_time = (end_time.tv_sec-start_time.tv_sec)*1e3 +(end_time.tv_nsec-start_time.tv_nsec)/1e6;                                            //end clock after waiting
            if (wpid == -1) {exit(EXIT_FAILURE);}
            //return signal or exit
            if (WIFEXITED(status)) {
				sprintf(info,"enseash [exit:%d|%ld ms] %%",WEXITSTATUS(status),execution_time);
                } 
            else if (WIFSIGNALED(status)) {
				sprintf(info,"enseash [sign:%d|%ld ms] %%",WTERMSIG(status),execution_time);
            }
            write(STDOUT_FILENO,info,strlen(info));
        }
		else {                                              
            //child   
            // Execution of command complexe                                  
            execvp(command[0],command);              //execvp because many arguments and size can vary
            exit(EXIT_SUCCESS);
            }
	}
	return 0;
 }

