#ifndef NETWORK_H
#define NETWORK_H

#define MESSAGE_BUFFER_SIZE 1000

void error_check( int i, char *s );

int server_setup(int port);
int server_connect(int sd);

int client_connect( char *host, int port );

char *promptIP();
int promptPort();
int promptNumPlayers();

#endif
