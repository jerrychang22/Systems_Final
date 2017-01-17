#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "network.h"

void process( char * s );
void sub_server( int sd );

int main() {

  //-------------------------------------Setup host--------------------------//

  int gameStart = 1;
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

  //Connect users
  //While game has not started, allow connections
  while (currentPlayers < numPlayers) {

    connection = server_connect( sd );

    int f = fork();
    if ( f == 0 ) {

      close(sd);
      sub_server( connection );

      exit(0);
    }
    else {
      currentPlayers++;
      //Add pid of child to list to access later
      close( connection );
    }
  }
  
  gameStart = 1; //End listening and start game
  //--------------------------------------------------------------------------------

  
  return 0;
}


void sub_server( int sd ) {

  char buffer[MESSAGE_BUFFER_SIZE];

  //while (!gameStart){  //Before game has started
  while (read( sd, buffer, sizeof(buffer) )) {

    printf("[SERVER %d] received: %s\n", getpid(), buffer );
    chat( buffer );
    write( sd, buffer, sizeof(buffer));    
  }
  //}
}

void chat( char * s ) {
  
}


