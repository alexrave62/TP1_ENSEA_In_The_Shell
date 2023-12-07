#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>


#define WELCOME "Bienvenue dans le Shell ENSEA.\nPour quitter, taper 'exit'.\n"
#define PROMPT "enseash % "
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
		if (ret==-1){exit(EXIT_FAILURE);}					//error test
        
        //parent
		if (ret !=0) {           

            //exit if 'exit' command                           
			if (strcmp(buf,"exit")==0){						
				write(STDOUT_FILENO,GOODBYE,strlen(GOODBYE));
				exit(EXIT_SUCCESS);}
			wpid = waitpid(ret,&status,0);

            // Return of exit or signal code
            if (wpid == -1) {exit(EXIT_FAILURE);}
            if (WIFEXITED(status)) {
				sprintf(info,"enseash [exit:%d] %% ",WEXITSTATUS(status));
                } 
            else if (WIFSIGNALED(status)) {
				sprintf(info,"enseash [sign:%d] %% ",WTERMSIG(status));
            }
            write(STDOUT_FILENO,info,strlen(info));
        }

        //child
		else {                                              
			execlp(buf,buf, (char *)NULL);
			exit(EXIT_SUCCESS);}
	}
	return 0;
 }
