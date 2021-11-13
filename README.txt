Student: Sean Dela Pena 
Professor: Mark Hauschild
Assignment: Project 2 - CS 4280
	Parser
Date: 11/13/21

USAGE: make		(makefile to compile, creates a parser executable)
	./parser [somefile]
	make clean	

Invocation:
	./parser somefile.txt [enter]


Any other invocations will result in an error.

Notes:
	The token structure is as shown
	[token, "string", line num:charNum]
	["IDTk, "example, line 1:1]

	The error structure is as shown
	Parser Error: There is an error!
	Parser Error: ERROR in tk [tokenthatwaschecked] expected [expectedToken] in line [lineNum]

Important:
	The way the program works is when the parser is called with a file parameter,
	it checks if the file exists, if it does, continue. getAllTokens is called which
	calls the testScanner that runs the FSADriver to get a vector of all the tokens 
	in the file. A scanner() function is made inside parser.cpp which pops the tokens
	one by one every time it is called. The rest is pretty much the same with how the pseudocode
	works. Node root is set to parser once the parser completes, the tree is printed.