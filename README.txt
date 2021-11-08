Student: Sean Dela Pena 
Professor: Mark Hauschild
Assignment: Project 2 - CS 4280
	Parser
Date: 11/12/21

OPTION 3: FSA table with FSA Driver, the table and the driver will be found in scanner.cpp file.

USAGE: make		(makefile to compile, creates a scanner executable)
	./scanner [somefile] [keyboard input] [< somefile]
	make clean	

Three example invocations:
	./scanner somefile.txt [enter]

	./scanner [enter]
	this 
	is an 
	example
	of keyboard
	input
	[ctrl + d]

	./scanner < somefile.txt [enter]

Any other invocations will result in an error.

Notes:
	The token structure is as shown
	[token, "string", line num:charNum]
	["IDTk, "example, line 1:1]

Important:
	FSA table with FSA Driver, the table and the driver will be found in scanner.cpp file.

	The testScanner can be found in scanner.cpp file. The way the program works
	is that main.cpp, processes the arguments, then calls the testScanner function. The
	testScanner function then calls the fsaDriver to get the tokens and calls the
	printTokenVector to print out the tokens.

	The FSA driver goes through the file line by line. It filters that line (get rid of comments
	and check for invalid characters). Once the line is filtered and no errors are found it tokenizes
	every string in that line and pushes it in a vector. It does that process until EOF and returns 
	the tokens. Now all that is left to do is for the testScanner to call the print function.

	The FSA driver is highly based on the pseudocode given in the powerpoint.