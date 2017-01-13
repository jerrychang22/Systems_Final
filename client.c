#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "network.h"

int main(){


  //----------------------Wait for user to input ip and port-----------------------

  //IP
  printf("Host IP Address (IPv4) : ");
  char ipinput[32];
  fgets(ipinput, 32, stdin);
  //if () {} //Check for valid IPv4 address

  //Port
  printf("Port : ");
  char portinput[8];
  fgets(portinput, 8, stdin);
  //if () {} //Check for valid port
  int port = atoi(portinput);
  
  //--------------------------------------------------------------------------------

  
  
  //----------------------------Socket and Connect----------------------------------
  
  int sd;

  sd = client_connect( host, port );

  char buffer[MESSAGE_BUFFER_SIZE];
  
  while (1) {
    printf("enter message: ");
    fgets( buffer, sizeof(buffer), stdin );
    char *p = strchr(buffer, '\n');
    *p = 0;
  
    write( sd, buffer, sizeof(buffer) );
    read( sd, buffer, sizeof(buffer) );
    printf( "received: %s\n", buffer );
  }
  






  //--------------------------------------------------------------------------------


  //-------------------------------Client-side functions---------------------------



  //-------------------------------------------------------------------------------
  
  
  

  return 0;
}
