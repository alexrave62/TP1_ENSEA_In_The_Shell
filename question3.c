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
	//Message d'accueil
	write(STDOUT_FILENO,WELCOME,strlen(WELCOME));
	write(STDOUT_FILENO,PROMPT,strlen(PROMPT));
	// boucle de commande
	char buf[BUFSIZE];
	while (1){
		//Réinitialization of the buffer
		for (int i=0; i<BUFSIZE; i++){buf[i]='\0';}
		
		//lecture commande
		ssize_t len_com = read(STDIN_FILENO, buf, BUFSIZE);	
		if (len_com < 0){return EXIT_FAILURE;}				//error test
		if (len_com == 0){return EXIT_FAILURE;}				//pas de commande
		buf[len_com-1] = '\0';					
		
		//Evaluation commande
		int status;
		pid_t ret = fork();
		if (ret==-1){exit(EXIT_FAILURE);}					//error test
		if (ret !=0) {
			if (strcmp(buf,"exit")==0){						//exit if 'exit' command
				write(STDOUT_FILENO,GOODBYE,strlen(GOODBYE));
				exit(EXIT_SUCCESS);}
			waitpid(ret,&status,0);}
		else {
			execlp(buf,buf, (char *)NULL);
			exit(EXIT_SUCCESS);}
		
		write(1,PROMPT,strlen(PROMPT));
	}
	return 0;
 }
