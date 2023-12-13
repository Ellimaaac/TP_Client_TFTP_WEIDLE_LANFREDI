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
	
	int n_bytes;
	struct addrinfo hints;
	struct addrinfo *res;
	memset(&hints, 0, sizeof(struct addrinfo)); // Initialise à 0
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_family = AF_INET;
	hints.ai_protocol = IPPROTO_UDP;
	
	int en = getaddrinfo(host, "1069", &hints, &res);
	if (en == -1) {
		perror("getaddrinfo");
		exit(EXIT_FAILURE);
	}
	
	int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sock == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	char buf[MAXSIZE];
	memset(buf, 0, MAXSIZE);
	buf[1] = 2; // On set l'écriture
	
	strcpy(buf + 2, argv[3]);
	size_t padding = strlen(buf+2);

	strcpy(buf + 2 + padding + 1, "octet");
	size_t padding2 = strlen(buf + 3 + padding);

	if ((n_bytes = sendto(sock, buf, padding + padding2 + 4, 0, res -> ai_addr, res -> ai_addrlen)) == -1){
		perror("send WRQ");
		return(EXIT_FAILURE);
	}

	printf("WRQ sent : OK \n");

	return(EXIT_SUCCESS);
}