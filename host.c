#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "network.h"

void process( char * s );
void sub_server( int sd );

int main() {

  //-------------------------------------Setup host--------------------------//

  int gameStart = 1;

  //Port
  printf("Port : ");
  char portinput[8];
  fgets(portinput, 8, stdin);
  //if () {} //Check for valid port
  int port = atoi(portinput);


  //Setup connections
  int sd, connection;

  sd = server_setup(port);

  //Connect users
  //While game has not started, allow connections
  while (!gameStart) {

    connection = server_connect( sd );

    int f = fork();
    if ( f == 0 ) {

      close(sd);
      sub_server( connection );

      exit(0);
    }
    else {
      close( connection );
    }
  }
  //--------------------------------------------------------------------------------

  
  return 0;
}


void sub_server( int sd ) {

  char buffer[MESSAGE_BUFFER_SIZE];

  //while (!gameStart){  //Before game has started, allow chat
  while (read( sd, buffer, sizeof(buffer) )) {

    printf("[SERVER %d] received: %s\n", getpid(), buffer );
    chat( buffer );
    write( sd, buffer, sizeof(buffer));    
  }
  //}
}
void chat( char * s ) {
  
}


