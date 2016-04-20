# Bartosz Bednarczyk (273 479)

Flags = -std=c++11 -Wextra -g -Werror -Wreturn-type -pedantic -pedantic-errors -Wundef -Wall -W
CPP = g++

router : Makefile router.o utils.o networkinfo.o web.o
	$(CPP) $(Flags) -o router router.o utils.o networkinfo.o web.o

router.o : Makefile router.cpp utils.o networkinfo.o web.o	
	$(CPP) -c $(Flags) router.cpp -o  router.o

web.o : Makefile web.cpp web.h utils.o networkinfo.o
	$(CPP) -c $(Flags) web.cpp -o web.o		

networkinfo.o : Makefile networkinfo.cpp networkinfo.h utils.o
	$(CPP) -c $(Flags) networkinfo.cpp -o networkinfo.o	

utils.o : Makefile utils.cpp utils.h 
	$(CPP) -c $(Flags) utils.cpp -o utils.o	

clean:
	rm -rf *.o

distclean:
	rm -rf *.o router .*.swp