#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "network.h"
#include "game.h"

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
  

  //----------------------------Socket and Connect----------------------------------
  
  int sd;

  sd = client_connect(ipinput, port );
  printf("Connected to %s:%d\n", ipinput, port);

  pthread_t serverRead;
  pthread_create(&serverRead, NULL, clientWork, &sd);

  char buffer[MESSAGE_BUFFER_SIZE];

  while (1) {
    takeInput(buffer, sd);
  }
  
  

  return 0;
}
