#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#include "network.h"
#include "game.h"

int main() {
  srand(time(NULL));

  //printf("%d\n", NUM_COMPONENTS);

  int numPlayers = 0;
  int currentPlayers = 0;

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

  //Connect users
  //While game has not started, allow connections
  
  while (currentPlayers < numPlayers) {

    connection = server_connect( sd );
    pthread_t clientInput;
    pthread_create(&clientInput, NULL, serverWork, &connection);

    int f = fork();
    if ( f != 0 ) {
      currentPlayers++;
      printf("Current players : %d\n", currentPlayers);
      addNewPlayer( connection );
    } else {
      exit(0);
    }
  }

  /*
  int x;
  if (fork() == 0) {
    connection = server_connect(sd);
    pthread_t clientInput;
    pthread_create(&clientInput, NULL, serverWork, &connection);
    addNewPlayer(connection);
    exit(0);
  } else {
    x = client_connect("127.0.0.1", port);
    addNewPlayer(x);
    
    struct clientpack args;
    args.sd = x;
    pthread_t serverRead;
    pthread_create(&serverRead, NULL, clientWork, &args);

  }
  */

  initializePanels();
  initializeCommands();
  while (1) {}

  return 0;
}