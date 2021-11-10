CC=gcc
CFLAGS= -I -g -lstdc++ -std=c++11

parser: main.cpp scanner.cpp scanner.hpp character.hpp token.hpp parser.cpp parser.hpp
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o parser
	rm -f *.gch
	rm fileCreated.txt
