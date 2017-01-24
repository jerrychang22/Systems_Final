#ifndef GAME_H
#define GAME_H

#define MAX_PLAYER_LIMIT 8
#define NUM_COMPONENTS 3
#define CHAR_LIMIT 256
#define HEALTH 1
#define COMMAND 2
#define PANEL 3
#define TIMELIMIT 15

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
    time_t timer;

    
} clientpack;



void *clientWork(void *arg);

void *serverWork(void *arg);

int validateCommand(char in[]);

void issueCommand(int sd);

int contains(char *needle, char *hay[]);

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
                        "Fluxtrunions",
                        "Quantum bogosort",
                        "Photon hyperdrive"
};
#endif