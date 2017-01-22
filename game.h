#ifndef GAME_H
#define GAME_H

//Server
//list of verbs (to add in front of command or object)
//list of commands available

//list of pids

//list of commands for a pid

//list of times per pid
//handle time


//handle commands
//void issueCommand(int pid);    //must be unique

//validateCommand

//



//Client
//void checkCommandCompletion(int pid);
//


void takeInput(char buffer[], int sd);

void *clientWork(void *arg);

void *serverWork(void *arg);


#endif
