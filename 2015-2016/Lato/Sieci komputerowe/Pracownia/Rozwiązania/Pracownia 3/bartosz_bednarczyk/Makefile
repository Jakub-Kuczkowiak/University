# Bartosz Bednarczyk 273 479


Flags = -std=c++11 -Wextra -g -Wreturn-type -pedantic -pedantic-errors -Wundef -Wall -W
CPP = g++

client-udp : Makefile client-udp.o utils.o MySocket.o
	$(CPP) $(Flags) -o client-udp client-udp.o utils.o MySocket.o

client-udp.o : Makefile client-udp.cpp utils.o MySocket.o
	$(CPP) -c $(Flags) client-udp.cpp -o  client-udp.o

MySocket.o : Makefile MySocket.cpp MySocket.h utils.o
	$(CPP) -c $(Flags) MySocket.cpp -o MySocket.o	

utils.o : Makefile utils.cpp utils.h 
	$(CPP) -c $(Flags) utils.cpp -o utils.o	

clean:
		rm -rf *.o

distclean:
		rm -rf *.o client-udp .*.swp
