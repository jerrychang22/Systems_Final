#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "network.h"

void takeInput(char buffer[], int sd){
	printf("Enter command : ");
	fgets(buffer, sizeof(buffer), stdin);
	char *p = strchr(buffer, '\n');
	*p = 0;

	write(sd, buffer, sizeof(buffer));
}

//Each individual client thread's worker function
//Check commmand
void *clientWork(void *arg){
	int sd = *((int *) arg);
	char buffer[MESSAGE_BUFFER_SIZE];
	
	while (1) {
		read(sd, buffer, sizeof(buffer));
	}	
}


void *serverWork(void *arg){
	int sd = *((int *) arg);
	char buffer[MESSAGE_BUFFER_SIZE];

	while (1) {
		read(sd, buffer, sizeof(buffer));
	}
}



