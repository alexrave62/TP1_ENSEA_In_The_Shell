#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>

#define WELCOME "Bienvenue dans le Shell ENSEA.\nPour quitter, taper 'exit'.\n"
#define PROMPT "enseash % "
#define GOODBYE "Bye Bye ...\n"
#define BUFSIZE 200

int main (){
	
    //Initialisation des variables
    char buf[BUFSIZE];
    int status;
    pid_t ret;

    //Message d'accueil
	write(STDOUT_FILENO,WELCOME,strlen(WELCOME));
	write(STDOUT_FILENO,PROMPT,strlen(PROMPT));
	
    
    // boucle de commande
	while (1){

		//Réinitialization of the buffer
		for (int i=0; i<BUFSIZE; i++){buf[i]='\0';}
		
		//lecture commande
		ssize_t len_com = read(STDIN_FILENO, buf, BUFSIZE);	
		if (len_com < 0){return EXIT_FAILURE;}				//error test
		buf[len_com-1] = '\0';					
		if (len_com == 0){return EXIT_FAILURE;}				//pas de commande ou ctrl+d
		
        //Evaluation commande
		ret = fork();
		if (ret==-1){exit(EXIT_FAILURE);}					//error test
		
        //parent
        if (ret !=0) {
			waitpid(ret,&status,0);
            write(1,PROMPT,strlen(PROMPT));}
        
        //enfant
		else {
			execlp(buf,buf, (char *)NULL);
			exit(EXIT_SUCCESS);}
	}
	return 0;
 }


	
			
