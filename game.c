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
#include "window.h"

int playerIndex =  0;
int playersd[MAX_PLAYER_LIMIT] = {};
char activePanelObjects[MAX_PLAYER_LIMIT * NUM_COMPONENTS][CHAR_LIMIT] = {};
char activeCommands[MAX_PLAYER_LIMIT][CHAR_LIMIT] = {};
int timeTable[MAX_PLAYER_LIMIT] = {};

int shipStatus;

//Each individual client thread's worker function
//Check commmand
void *clientWork(void *arg) {
	struct clientpack cpack= *((clientpack *) arg);
	struct packet packet;

	while (read(cpack.sd, &packet, sizeof(packet)) != -1) {
		/*if (read(cpack.sd, &packet, sizeof(packet)) == -1) {
			printf("Error: %s", strerror(errno));
			continue;
		}*/

		switch (packet.type) {
			case HEALTH:
				break;
			case COMMAND:
				strcpy(cpack.currentCommand, packet.commandUpdate);
				update_screen(-1, cpack.currentCommand);
				int k;
				for (k = 0; k < MAX_PLAYER_LIMIT; k++){
					if (cpack.sd == playersd[k])
						break;
				}
				timeTable[k] = TIMELIMIT;
				break;
			case PANEL:
				;
				//Fill next non-empty panel slot with a new component
				int i = 0;
				for (; strlen(cpack.panelList[i]) > 0 && i < NUM_COMPONENTS; i++);
				strcpy(cpack.panelList[i], packet.addPanel);
				addPanels(cpack.panelList[i]);
				/*
				printf("Updated panel to %s\n", cpack.panelList[i]);
				for (i = 0; strlen(cpack.panelList[i]) > 0 && i < NUM_COMPONENTS; i++) {
					printf("panel[%d] - '%s'\n", i, cpack.panelList[i]);
				}*/
				break;
			default:
				break;
		}
	}
	printf("Error: %s\n", strerror(errno));
}


void *serverWork(void *arg) {
	int sd = *((int *) arg);
	while (1) {
		char buffer[MESSAGE_BUFFER_SIZE] = {};
		read(sd, buffer, MESSAGE_BUFFER_SIZE);
		if (strlen(buffer) > 0) {
			printf("[Client %d] %s\n", sd, buffer);
			validateCommand(buffer);
		}
	}
}

void addNewPlayer(int sd) {
	playersd[playerIndex] = sd;
	playerIndex++;
	printf("Player[%d], sd : %d\n", playerIndex, sd);
}

void initializePanels() {
	int i, loop;
	struct packet packet;
	packet.type = PANEL;
	for (loop = 0; loop < NUM_COMPONENTS; loop++) {
		for (i= 0; i < playerIndex; i++) {
			//random object
			int r = loop * NUM_COMPONENTS + i;
			strcpy(packet.addPanel, objectList[r]);
			if (write(playersd[i], &packet, sizeof(packet)) == -1) {
				printf("Error: %s\n", strerror(errno));
			}
			
			int j;
			for (j = 0; strlen(activePanelObjects[j]) > 0; j++);
			strcpy(activePanelObjects[j], objectList[r]);
		}
	}
}

void initializeCommands() {
	int i;
	for (i= 0; i < playerIndex; i++) {
		issueCommand(playersd[i]);
	}
}

int validateCommand(char in[]) {
	int i;
	for (i = 0; i < playerIndex; i++) {
		if (strcasecmp(in, activeCommands[i]) == 0) {
			//printf("Issuing new command\n");
			issueCommand(playersd[i]);
			//printf("Past issueCommand\n");
		}
	}
}

void issueCommand(int sd) {
	int i;
	for (i = 0; i < MAX_PLAYER_LIMIT; i++){
		if (sd == playersd[i])
			break;
	}

	int r = rand() % playerIndex + rand() % NUM_COMPONENTS;; 
	char command[CHAR_LIMIT] = {};
	char *randomVerb = verbList[rand() % 9];
	char *randomObject = activePanelObjects[r];
	
	//check for existing command
	// while (contains(randomObject, activeCommands)) {
	// 	r = rand() % playerIndex + rand() % NUM_COMPONENTS;
	// 	randomObject = activePanelObjects[r];
	// }
	sprintf(command, "%s %s", randomVerb, randomObject);
	
	strcpy(activeCommands[i], command);

	struct packet packet;
	packet.type = COMMAND;
	strncpy(packet.commandUpdate, command, sizeof(packet.commandUpdate));
	write(sd, &packet, sizeof(packet));
}

void timeUpdate(){
	int i = 0;
	for (i; i < playerIndex; i++){
		timeTable[i] -= 1;
		
		if (timeTable[i] <= 0){
			shipStatus -= 1;
			
			
		}
		
	}
	
}

int contains(char *needle, char *hay[]) {
	int i;
	for (i = 0; hay[i] != NULL; i++) {
		printf("hay[%d] : %s\n", i, hay[i]);
		if (strcmp(needle, hay[i]) == 0)
			return 1;
	}
	return 0;
}