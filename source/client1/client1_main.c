/*
 * TEMPLATE 
 */
#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <ctype.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <rpc/xdr.h>

#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../errlib.h"
#include "../sockwrap.h"
#include "../msg.h"

#define BUFLEN 4096
#define N_ARG 4

char *prog_name;
char buf[BUFLEN];

int RiceviFile(int s, int argc);

int main (int argc, char *argv[])
{
	/*
		Gestione argc e argv
	*/
	prog_name = argv[0];
	if (argc < N_ARG){
		printf("Numero di argomenti incorretto: ./client1 [IPv4 (0.0.0.0)] [port (usare quella del server)] [files ... ]\n");
		exit(1);
	}
		
	/*
		Creazione del socket in IPv4
	*/
	int s = Socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (s < 0){
	//	printf("errore creazione socket");
		exit(1);
	}
	
	/*
		Creazione struct di endpoint IPv4 (sockaddr_in) DESTINAZIONE
	*/	
	struct sockaddr_in 		adds;
	
	//adds.sin_len=sizeof(struct sockaddr_in);		NON presente in linux
	adds.sin_family=AF_INET;					// address family (AF_INET per IPv4)
	adds.sin_port=htons(atoi(argv[2]));			// porta in formato uint16_t
	
	if (inet_aton(argv[1], (struct in_addr*) &adds.sin_addr) != 1){	
	// funzione di conversione da IP puntato 
	// inet_aton("20.20.20.20", (strcut sockaddr_in->in_addr*) &adds);
		printf("errore assegnare indirizzo server\n");
		exit(1);
	}
	
	/*
		Connessione del socket all'indirizzo destinazione
	*/
	if (Connect(s, (struct sockaddr*) &adds, sizeof(adds)) != 0){
	// funzione di connessione all'indirizzo e porta in sockaddr_in
		printf("errore connessione\n");
		exit(1);
	}
	else{
	// 	DEBUG
		printf("connesso\n");
	}
	
	/*
		Scambio dati con server
	*/
	char c[128];
	
	for(int i=3;i<argc;i++){
		if(strlen(argv[i])>122){
			printf("nome file troppo grande\n");
			break;
		}
		strcpy(c, GET);
		strcat(c, argv[i]);
		strcat(c, "\r\n");
		
		if(Send (s, c, strlen(c), 0)!=strlen(c))
			exit(1);
	}
	
	int bletti;
	
	const char str[] = "+Oasdwefdfs+Osfsadf\0";
	const char st[] = "+OK";
	char *res;
	
	res = strstr(str, st);
	if (res != NULL)
	printf("%s\n", res);
	
	return 0;
}


int RiceviFile(int s, int argc){
	int rec, idx = N_ARG;//4
	int n = 0;
	
	/*
		Leggo buf, cerco +OK, leggo B1-B4 = dim_file
		dim_rest = dim_file;
		se dim_file > BUF {
			scrivo il file
			dim_rest = dim_rest - BUF - 10c - pos_OK 
			
		}
	*/
	
	while (idx < argc){
		
		// leggo buf di 4096 max
		if ( (rec = Recv (s, buf, BUFLEN,0)) < 0){
		// errore
		}
		
		// cerco pos +OK
		
	}
	



	return n;
}