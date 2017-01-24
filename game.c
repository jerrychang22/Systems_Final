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
int playersd[MAX_PLAYER_LIMIT] = {};
char activePanelObjects[MAX_PLAYER_LIMIT * NUM_COMPONENTS][CHAR_LIMIT] = {};
char activeCommands[MAX_PLAYER_LIMIT][CHAR_LIMIT];

int shipStatus;

void takeInput(char buffer[], int sd) {
	printf("Enter command : ");
	fgets(buffer, sizeof(buffer), stdin);
	char *p = strchr(buffer, '\n');
	*p = 0;

	write(sd, buffer, sizeof(buffer));
}

//Each individual client thread's worker function
//Check commmand
void *clientWork(void *arg) {
	struct clientpack cpack= *((clientpack *) arg);
	struct packet packet;

	while (1) {
		read(cpack.sd, &packet, sizeof(packet));

		switch (packet.type) {
			case HEALTH:
				printf("Health\n");
				break;
			case COMMAND:
				printf("Command\n");
				strcpy(cpack.currentCommand, packet.commandUpdate);
				//Update time as well
				break;
			case PANEL:
				printf("Panel\n");
				//Fill next non-empty panel slot with a new component
				int i;
				for (i = 0; strlen(cpack.panelList[i]) > 0 && i < NUM_COMPONENTS; i++){
					printf("junk[%d] - '%s'\n",i, cpack.panelList[i]);
				}
				printf("%d\n", i);
				strcpy(cpack.panelList[i], packet.addPanel);
				printf("Updated panel to %s\n", cpack.panelList[i]);
				break;
			
			default:
				break;
		}
	}
}


void *serverWork(void *arg) {
	int sd = *((int *) arg);
	while (1) {
		char buffer[MESSAGE_BUFFER_SIZE] = {};
		read(sd, buffer, sizeof(buffer));
		if (strlen(buffer) > 0) {
			printf("[Client %d] %s\n", sd, buffer);
		}
		//validateCommand(buffer);
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
			strcpy(packet.addPanel, objectList[loop * NUM_COMPONENTS + i]);
			write(playersd[i], &packet, sizeof(packet));
		}
	}
}

int validateCommand(char in[]) {
	int i = 0;
	for (;i < MAX_PLAYER_LIMIT; i++) {
		if (strcmp(in, activeCommands[i]) == 0){
			issueCommand(playersd[i]);
		}
	}
}

void issueCommand(int sd) {
	int i = 0;
	for (i; i < MAX_PLAYER_LIMIT; i++){
		if (sd == playersd[i])
			break;
	}
	int r = rand() % playerIndex + rand() % NUM_COMPONENTS;
	char command[CHAR_LIMIT] = {};
	char *randomVerb = verbList[rand() % 4];
	char *randomObject = activePanelObjects[r];
	sprintf(command, "%s %s", randomVerb, randomObject);

	struct packet packet;
	packet.type = COMMAND;
	strncpy(packet.commandUpdate, command, sizeof(packet.commandUpdate));

	write(sd, &packet, sizeof(packet));
}


