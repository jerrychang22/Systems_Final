all : host client

host: host.o network.o game.o
	gcc -o host host.o network.o game.o -lpthread

client: client.o network.o game.o
	gcc -o client client.o network.o game.o -lpthread

host.o: host.c network.h game.h
	gcc -c host.c

client.o: client.c network.h game.h
	gcc -c client.c 

network.o: network.c network.h
	gcc -c network.c

game.o : game.c game.h network.h
	gcc -c game.c

clean:
	rm *.o
	rm *~
