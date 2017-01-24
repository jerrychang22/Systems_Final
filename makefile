all : host client

host: host.o network.o game.o
	gcc -Wall -o host host.o network.o game.o -lpthread

client: client.o network.o game.o
	gcc -Wall -o client client.o network.o game.o -lpthread

host.o: host.c network.h game.h
	gcc -Wall -c host.c

client.o: client.c network.h game.h
	gcc -Wall -c client.c 

network.o: network.c network.h
	gcc -Wall -c network.c

game.o : game.c game.h network.h
	gcc -Wall -c game.c

clean:
	rm -f *.o
	rm -f *~