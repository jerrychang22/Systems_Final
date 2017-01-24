LIBS = -lpthread -lncurses

all : host client

host: host.o network.o game.o window.o
	gcc -Wall -o host host.o network.o game.o window.o $(LIBS)

client: client.o network.o game.o window.o
	gcc -Wall -o client client.o network.o game.o window.o $(LIBS)

host.o: host.c
	gcc -Wall -c host.c

client.o: client.c
	gcc -Wall -c client.c 

network.o: network.c
	gcc -Wall -c network.c

game.o : game.c window.h
	gcc -Wall -c game.c

window.o: window.c
	gcc -Wall -c window.c

clean:
	rm -f *.o
	rm -f *~