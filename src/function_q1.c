#include "function.h"

int main(int argc, char *argv[]){
	char* host = argv[1];
	char* port = argv[2];
	char* fileName = argv[3];

	// Vérification du bon nombre d'argument
	if(argc != 4){
		printf("Il a %d arguments sur 3 \n", argc-1);
		return(EXIT_FAILURE);
	}
	printf("Envoyer %s à l'host : %s@%s \n", fileName, host, port);
}
