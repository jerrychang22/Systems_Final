#ifndef GAME_H
#define GAME_H

#define MAX_PLAYER_LIMIT 8
#define NUM_COMPONENTS 4
#define CHAR_LIMIT 256
#define HEALTH 0
#define COMMAND 1
#define PANEL 2

typedef struct packet {
    int type;
    int healthUpdate;
    char commandUpdate[CHAR_LIMIT];
    char addPanel[CHAR_LIMIT];
} packet;

typedef struct clientpack {
    int sd;
    char currentCommand[CHAR_LIMIT];
    char panelList[NUM_COMPONENTS][CHAR_LIMIT];
    
} clientpack;

void takeInput(char buffer[], int sd);

void *clientWork(void *arg);

void *serverWork(void *arg);

int validateCommand(char in[]);

void issueCommand(int sd);

void resetTimer(int sd);


//Large list of stuff
static char *verbList[12] = {"Engage the",
                      "Activate the",
                      "Turn on the",
                      "Turn off the",
                      "Set the", 
                      "Press the",
                      "Switch on the",
                      "Switch off the",
                      "Flip the"
};

static char *objectList[24] = {"Sensor array",
                        "Gravity dampener",
                        "Subsonic phaser",
                        "Nanosphere splitter",
                        "Quark accelerator",
                        "Eigenthrottle",
                        "Field generator",
                        "Crystal capacitators",
                        "Vortex fluctuators",
                        "Fluxtrunions"
};
#endif