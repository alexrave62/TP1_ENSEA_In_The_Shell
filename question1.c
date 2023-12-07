#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>

#define WELCOME "Bienvenue dans le Shell ENSEA.\nPour quitter, taper 'exit'.\nenseash %\n"


int main (int argc, char *argv[]){
	//Message d'accueil
	write(STDOUT_FILENO,WELCOME,strlen(WELCOME));
	return 0;
 }