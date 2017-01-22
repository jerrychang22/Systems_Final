#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "network.h"
#include "game.h"

int main() {

  int numPlayers = 0;
  int currentPlayers = 1;

  //Port
  printf("Port : ");
  char portinput[8];
  fgets(portinput, 8, stdin);
  //if () {} //Check for valid port
  int port = atoi(portinput);


  //Players
  printf("Number of players : ");
  char playercount[8];
  fgets(playercount, 8, stdin);
  //if () {} //Check for valid int
  numPlayers = atoi(playercount);

  //Setup connections
  int sd, connection;

  sd = server_setup(port);
  char buffer[MESSAGE_BUFFER_SIZE];
  char buffer2[MESSAGE_BUFFER_SIZE];


  //Connect users
  //While game has not started, allow connections
  while (currentPlayers < numPlayers) {

    connection = server_connect( sd );
    pthread_t clientInput;
    pthread_create(&clientInput, NULL, serverWork, &connection);

    //Fork and pipe
    int f = fork();
    if ( f == 0 ) {
	while(1){
		takeInput(buffer, connection);
	}

    }
    else {
      currentPlayers++;
      close( connection );
    }
  }

  while (1) {
  	takeInput(buffer2, sd);
  }


  return 0;
}


