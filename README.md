# Systems_Final

 This should list project members, how to compile and use your project and
 a list of all the files that should be in the repository.
 
 Project members : Jerry Chang, Period 10
 
 Required libraries : 
 
 ncurses
 sudo apt-get install libncurses5-dev libncursesw5-dev
 
 Program instructions:
 Run one ./host and as many ./client as declared.
 Running ./host will prompt the user to input a port and input the number of 
 players in a game
 
 Clients will be prompted to input an ip to connect to and a port. The game will
 not start until the declared number of players join
 
 Each player is given a unique panel of four components and a command
 Players must work together to complete every command possible.
 Players are to shout out their command to tell other players which components
 need to be activated. When a command is shouted that exists on a player's 
 panel, they must type the command (case insensitive) to complete it.
 
 Unfinished systems : 
 Timer (Could not figure out a way to keep a timer up that 
 continuously sent signals to all clients)
 Health (Directly tied to timer)
 
 NOTE : For some reason, in ncurses thet text may not appear unless your terminal
 size is large enough. Some of my tests show text at around 200columns? (echo $COLUMNS)
 
 
 
 FILES IN REPO :
  - client.c
  - host.c
  - game.c
  - network.c
  - window.c
  - game.h
  - network.h
  - window.h
  - makefile
  