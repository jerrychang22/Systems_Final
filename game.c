#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <time.h>

#include "network.h"
#include "game.h"

int playerIndex =  0;
int playersd[8];
char activePanelObjectList[8 * 4][256];
//Numplayers * num commands per player
char activeCommands[8][256];

char verbList[256][256];
char objectList[256][256];
srand(time(NULL));

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
		//Reads info from server
	}	
}


void *serverWork(void *arg){
	int sd = *((int *) arg);
	char buffer[MESSAGE_BUFFER_SIZE];
	while (1) {
		read(sd, buffer, sizeof(buffer));
		//validateCommand(buffer);
	}
}

void addNewPlayer(int sd){
	playersd[playerIndex] = sd;
	playerIndex++;
	printf("Player[%d], sd : %d\n", playerIndex, sd);
}

void initializePanels(){}

int validateCommand(char in[]){
	int i = 0;
	for (i; i < 8; i++) {
		if (strcmp(in, activeCommands[i]) == 0){
			issueCommand(playersd[i]);
			resetTimer(playersd[i]);
		
		}
	}

}

void issueCommand(int sd){
	int i = 0;
	for (i; i < 8; i++){
		if (sd == playersd[i])
			break;
	}
	int rand = rand();




}

void resetTimer(int sd){

}
