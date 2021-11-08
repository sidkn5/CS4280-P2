CC=gcc
CFLAGS= -I -g -lstdc++ -std=c++11

scanner: main.cpp scanner.cpp scanner.hpp character.hpp token.hpp
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o scanner
	rm -f *.gch
	rm fileCreated.txt
