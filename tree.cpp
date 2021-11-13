//Sean Dela Pena
//FILE: tree.cpp
//
//
#include "tree.hpp"
#include "node.hpp"
#include "token.hpp"


std::string tokenNames2[] = {
	"HolderTk", "IDTk", "INTEGERTk", "WSTk", "EQUALTk", "EQEQTk", "GREATERTHANTk", "LESSTHANTk", "COLONTk",
	"COLONEQTk", "PLUSTk", "MINUSTk", "MULTIPLYTk", "DIVIDETk", "MODULUSTk", "DOTTk", "LEFTPARENTK",
	"RIGHTPARENTk", "COMMATk", "LEFTBRACETk", "RIGHTBRACETk", "SEMICOLONTk", "LEFTBRACKETTk", "RIGHTBRACKETTk",
	"EOFTk", "KEYWORDTk", "STARTTk", "STOPTk", "LOOPTk", "WHILETk", "FORTk", "LABELTk", "EXITTk", "LISTENTk",
	"TALKTk", "PROGRAMTk", "IFTk", "THENTk", "ASSIGNTk", "DECLARETk", "JUMPTk", "ELSETk"
};

std::string funcNames[] = {
	"<PROGRAM>", "<BLOCK>", "<VARS>", "<EXPR>", "<N>", "<A>", "<M>",
	"<R>", "<STAT>", "<MSTAT>", "<STAT>", "<IN>", "<OUT>", "<IFSTAT>",
	"<LOOP>", "<ASSIGN>", "<RO>", "<LABEL>", "<GOTOFUNC>"
};


//int nodeType
Node* getNode(int nodeType) {

	Node* node = new Node;

	node->funcCalled = nodeType;

	node->child1 = NULL;
	node->child2 = NULL;
	node->child3 = NULL;
	node->child4 = NULL;
	node->child5 = NULL;

	token newToken1;
	token newToken2;

	//the holdertk is not used in the parser/scanner but is a tokentype
	newToken1 = { .type = HOLDERTK, .tokenString = "", .lineNum = 0, .charNum = 0 };
	newToken2 = { .type = HOLDERTK, .tokenString = "", .lineNum = 0, .charNum = 0 };

	node->token1 = newToken1;
	node->token2 = newToken2;

	return node;
}

void printNode(Node *node, int depth, int indent) {
	//std::cout << "print called\n";
	
	if (node == NULL )
		return;

	
	std::cout << funcNames[node->funcCalled] << std::endl;

	//HOLDERTK is equivalent to a NULL in token form
	if(node->token1.type != HOLDERTK){
	std::cout << "[" << tokenNames2[node->token1.type] << ", \"" << node->token1.tokenString
		<< "\", line " << node->token1.lineNum << ":" << node->token1.charNum << "]" << std::endl;
	}
	if (node->token2.type != HOLDERTK) {
		std::cout << "[" << tokenNames2[node->token2.type] << ", \"" << node->token2.tokenString
			<< "\", line " << node->token2.lineNum << ":" << node->token2.charNum << "]" << std::endl;
	}
	

	//traverses the tree
	printNode(node->child1, depth+1, indent+1);
	printNode(node->child2, depth+1, indent + 1);
	printNode(node->child3, depth+1, indent + 1);
	printNode(node->child4, depth+1, indent + 1);
	printNode(node->child5, depth+1, indent + 1);

	//for (int i = 0; i < indent; i++) {
	//	std::cout << "\t";
	//}

}