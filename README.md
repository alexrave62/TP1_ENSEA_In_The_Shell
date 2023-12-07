# TP1_SYNTHESE_2G2TP6_GAILLARD_RAVENNE
07/12/2023

Question 1: affichage d'un message en utilisant la commande write
utiliser un #define pour la chaîne de caractère permet plus 
facilement d'utiliser read et strlen por avoir la taille de 
la chaîne de cararctère.

Question 2:

    (a) lecture de la commande réalisé avec un buffer et un read, il faut attention à bien 
    délimiter la commande au dernier caractère.
    (b) exécution en créant un fork et dans le fils on utilise execlp
    (c) réaffichage du prompt 
Question 3: Création d'un code conditionnel qui affiche le message de sortie 
et sort s'il reconnaÎt la commande exit. Pour sortir avec un CTRL+d, il faut
le cas où la commande est vide.

Question 4: Après l'exécution de la commande on demande le code de sortie ou
de signal. Pour utiliser le write on convertira la chaîne de caractère avec
un %d à l'aide de la fonction sprintf

Question 5: Notre temps initial est le temps d'une horloge après le fork et 
le temps final est après l'exécution après le waitpid. On calcule le temps
d'exécution en soustrayant les deux.
Attention on veut le temps em ms et il y a 2 indicateurs de temps 1 en s 
et l'autre en ns. Ces 2 indicateurs s'additionne pour donner le temps donné
par l'horloge.

Question 6: Pour répondre à la commande complexe il faut séparer les différents
arguments dans un premier temps, puis utiliser execvp une fois la commande bien
séparée.