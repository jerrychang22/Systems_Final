all : host client

host: host.o network.o
	gcc -o host host.o network.o

client: client.o network.o
	gcc -o client client.o network.o

host.o: host.c network.h
	gcc -c host.c

client.o: client.c network.h
	gcc -c client.c

network.o: network.c network.h
	gcc -c network.c

clean:
	rm *.o
	rm *~
