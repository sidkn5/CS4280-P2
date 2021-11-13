/*Student: Sean Dela Pena
 *Assignment P2 - Parser
 *Professor: Mark Hauschild
 *Class: CS 4280
 *Date: 11-13-21
 * 
 * File: main.cpp
 * This file handles the arguments, calls the scanner, calls the parser then prints out the tree.
 */

#include "scanner.hpp"
#include "parser.hpp"
#include "tree.hpp"

int main(int argc, char* argv[]){

	std::string filename = "";
	std::ifstream file;
	//std::ofstream createdFile;
	//std::string userInput = "";
	
	
	if (argc > 2) {
		printf("ERROR: Incorrect use of the program.\n");
		exit(0);
	}
	//filename given
	else if (argc == 2) {
		filename = argv[1];
		file.open(filename);
		if (file) {
			std::cout << "Opening and working with the file...\n";
			
			getAllTokens(filename);
			Node* root = parser();
			printNode(root, 0);
		}
		else {
			std::cout << "The file does not exist! Terminating...\n";
			exit(0);
		}
	}
	//read from stdin, not needed for parser so error
	else {
		printf("ERROR: Incorrect use of the program.\n");
		exit(0);
		/*
		std::cout << "Will read from stdin...\n";
		createdFile.open("fileCreated.txt");
		filename = "fileCreated.txt";
		if (createdFile) {
			while (std::getline(std::cin, userInput)) {
				createdFile << userInput << "\n";
			}
			
		}
		else {
			std::cout << "ERROR: failed to create file...\n";
			exit(1);
		}
		createdFile.close();
		testScanner(filename);*/
		
	}

	
	//createdFile.close();
	file.close();

	return 0;
}
