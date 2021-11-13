//Sean Dela Pena
//File: parser.cpp

#include "parser.hpp"
#include "scanner.hpp"
#include "token.hpp"
#include "node.hpp"

static int index = -1;
static token tk;
//use myVector.at(index)
std::string filename;
std::vector<token> allTokens;


std::string expectedTokens[] = {
	"HolderTk", "IDTk", "INTEGERTk", "WSTk", "EQUALTk", "EQEQTk", "GREATERTHANTk", "LESSTHANTk", "COLONTk",
	"COLONEQTk", "PLUSTk", "MINUSTk", "MULTIPLYTk", "DIVIDETk", "MODULUSTk", "DOTTk", "LEFTPARENTK",
	"RIGHTPARENTk", "COMMATk", "LEFTBRACETk", "RIGHTBRACETk", "SEMICOLONTk", "LEFTBRACKETTk", "RIGHTBRACKETTk",
	"EOFTk", "KEYWORDTk", "STARTTk", "STOPTk", "LOOPTk", "WHILETk", "FORTk", "LABELTk", "EXITTk", "LISTENTk",
	"TALKTk", "PROGRAMTk", "IFTk", "THENTk", "ASSIGNTk", "DECLARETk", "JUMPTk", "ELSETk"
};

void getAllTokens(std::string filename) {
	allTokens = testScanner(filename);
}

token scanner() {
	index++;
	//return tks.at(index);

	//std::cout << "[" << expectedTokens[allTokens[index].type] << ", \"" << allTokens[index].tokenString
		//<< "\", line " << allTokens[index].lineNum << ":" << allTokens[index].charNum << "]" << std::endl;


	return allTokens.at(index);
}

Node* parser() {

	Node* root;

	tk = scanner();
	root = program();
	if (tk.type == EOFTK) {
		std::cout << "Parser Completed/Passed\n";
		//exit(1);
		//end
	}

	return root;
	//else {
	//	error(tk, PROGRAMTK);
	//}
}

// <vars> program <block>
Node* program() {
	
	std::cout << "Program called \n";
	Node* node = getNode(PROGRAMNODE);
	node->child1 = vars();

	if (tk.type == PROGRAMTK) {
		tk = scanner();
		node->child2 = block();
	}
	else {
		error(tk, PROGRAMTK);
	}
	return node;
}

//start <vars> <stats> stop
Node* block() {

	Node* node = getNode(BLOCKNODE);
	std::cout << "block called \n";

	if (tk.type == STARTTK) {
		tk = scanner();
		node->child1 = vars();
		node->child2 = stats();
		if (tk.type == STOPTK) {
			tk = scanner();
			return node;
		}
		else {
			error(tk, STOPTK);
		}
	}
	else {
		std::cout << "error here \n";
		error(tk, STOPTK);
	}

	return NULL;
}


// empty | declare Identifier =  Integer  ;  <vars> 
Node* vars() {
	std::cout << "vars called \n";

	Node* node = getNode(VARSNODE);

	if (tk.type == DECLARETK) {
		tk = scanner();

		if (tk.type == IDTK) {
			node->token1 = tk;
			tk = scanner();

			if (tk.type == EQUALTK) {
				tk = scanner();

				if (tk.type == INTEGERTK) {
					node->token2 = tk;
					tk = scanner();

					if (tk.type == SEMICOLONTK) {
						tk = scanner();
						node->child1 = vars();
						return node;
					}
					else {
						error(tk, SEMICOLONTK);	//expected semicolon
					}
				}
				else {
					error(tk, INTEGERTK);	//expected integer
				}
			}
			else {
				error(tk, EQUALTK);		//expected equal 
			}
		}
		else {
			error(tk, IDTK);	//expected identifier
		}
	}
	else {
		return node;	//vars can be empty
	}

	return node;
}

//<expr> -> <N> + <expr>  | <N>
Node* expr() {

	Node* node = getNode(VARSNODE);
	std::cout << "expr called \n";
	node->child1 = N();
	if (tk.type == PLUSTK) {
		node->token1 = tk;
		tk = scanner();
		node->child2 = expr();

	}
	else {
		return node;
	}
	return node;

}

//<N> -> <A> / <N> | <A> *<N> | <A>
Node* N() {
	std::cout << "N called \n";

	Node* node = getNode(NNODE);
	node->child1 = A();

	if (tk.type == DIVIDETK || tk.type == MULTIPLYTK) {
		node->token1 = tk;
		tk = scanner();
		node->child2 = N();
	}
	else {
		return node;
	}

	return node;
}


//<A> -> <M>-<A> | <M>
Node* A() {
	std::cout << "A called \n";
	Node* node = getNode(ANODE);
	node->child1 = M();

	if (tk.type == MINUSTK) {
		node->token1 = tk;
		tk = scanner();
		node->child2 = A();
	}
	else {
		//error(tk, MINUSTK);
		return node;
	}

	return node;
}

//<M> -> . <M> | <R>
Node* M() {

	Node* node = getNode(MNODE);
	if (tk.type == DOTTK) {
		node->token1 = tk;
		tk = scanner();
		node->child1 = M();
		return node;
	}
	else {
		node->child1 = R();
		return node;
	}

	return node;
}


//<R> -> ( <expr> ) | Identifier | Integer
Node* R() {

	Node* node = getNode(RNODE);
	if (tk.type == LEFTPARENTK) {
		tk = scanner();
		node->child1 = expr();

		if (tk.type == RIGHTPARENTK) {
			tk = scanner();
		}
		else {
			error(tk, RIGHTPARENTK);
		}
	}
	else if (tk.type == IDTK) {
		node->token1 = tk;
		tk = scanner();
		return node;
	}
	else if (tk.type == INTEGERTK) {
		node->token1 = tk;
		tk = scanner();
		return node;
	}
	else {
		return node;
	}

	return NULL;
}

//<stats> -> <stat>  <mStat>
Node* stats() {
	std::cout << "stats called \n";

	Node* node = getNode(STATSNODE);
	node->child1 = stat();
	node->child2 = mStat();

	return node;
}

//<mStat> -> empty |  <stat>  <mStat>
Node* mStat() {
	
	std::cout << "mstat called \n";

	Node* node = getNode(MSTATNODE);
	if (tk.type == LISTENTK || tk.type == TALKTK || tk.type == STARTTK || tk.type == IFTK || tk.type == WHILETK 
		|| tk.type == ASSIGNTK || tk.type == JUMPTK || tk.type == LABELTK) {
		node->child1 = stat();
		node->child2 = mStat();

		return node;
	}
	else {
		//is this NULL?
		return node;
	}

}


Node* stat() {
	std::cout << "stat called \n";

	Node* node = getNode(STATNODE);
	if (tk.type == LISTENTK) {
		tk = scanner();
		node->child1 = in();
		
		//std::cout << "[2" << expectedTokens[tk.type] << ", \"" << tk.tokenString
		//	<< "\", line " << tk.lineNum << ":" << tk.charNum << "]" << std::endl;

		if (tk.type == SEMICOLONTK) {
			tk = scanner();
			
			return node;
		}
		else {
			error(tk, SEMICOLONTK);
			return NULL;
		}
	}
	else if (tk.type == TALKTK) {
		tk = scanner();
		node->child1 = out();

		if (tk.type == SEMICOLONTK) {
			tk = scanner();

			return node;
		}
		else {
			error(tk, SEMICOLONTK);
		}
	} 
	else if (tk.type == STARTTK) {
		//tk = scanner();
		node->child1 = block();
		return node;

	}
	else if (tk.type == IFTK) {
		tk = scanner();
		node->child1 = ifStat();

		if (tk.type == SEMICOLONTK) {
			tk = scanner();

			return node;
		}
		else {
			error(tk, SEMICOLONTK);
			return NULL;
		}
	}
	else if (tk.type == WHILETK) {
		tk = scanner();
		node->child1 = loop();

		if (tk.type == SEMICOLONTK) {
			tk = scanner();

			return node;
		}
		else {
			error(tk, SEMICOLONTK);
			return NULL;
		}
	}
	else if (tk.type == ASSIGNTK) {
		tk = scanner();
		node->child1 = assign();

		if (tk.type == SEMICOLONTK) {
			tk = scanner();

			return node;
		}
		else {
			error(tk, SEMICOLONTK);
			return NULL;
		}
	}
	else if (tk.type == JUMPTK) {
		tk = scanner();
		node->child1 = gotoFunc();

		if (tk.type == SEMICOLONTK) {
			tk = scanner();
			
			return node;
		}
		else {
			error(tk, SEMICOLONTK);
			return NULL;
		}
	}
	else if (tk.type == LABELTK) {
		tk = scanner();
		node->child1 = label();

		if (tk.type == SEMICOLONTK) {
			tk = scanner();
			
			return node;
		}
		else {
			error(tk, SEMICOLONTK);
			return NULL;
		}
	}
	else {
		std::cout << "got here somehow\n";
		return NULL;
	}

	return NULL;
}

//<in>->listen  Identifier
Node* in() {
	std::cout << "in called \n";

	Node* node = getNode(INNODE);
	
	if (tk.type == IDTK) {
		node->token1 = tk;
		tk = scanner();
		return node;
	}
	else {
		error(tk, IDTK);
		return NULL;
	}
}


//<out> -> talk <expr>
Node* out() {
	std::cout << "out called\n";
	Node* node = getNode(OUTNODE);
	
	node->child1 = expr();
	return node;
}

Node* ifStat() {

	Node* node = getNode(IFSTATNODE);
	if (tk.type == LEFTBRACKETTK) {
		tk = scanner();

		node->child1 = expr();
		node->child2 = RO();
		node->child3 = expr();

		if (tk.type == RIGHTBRACKETTK) {
			tk = scanner();
			
			if (tk.type == THENTK) {
				tk = scanner();
				node->child4 = stat();

				if (tk.type == ELSETK) {
					tk = scanner();
					node->child5 = stat();
				}
				return node;
			}
			else {
				error(tk, THENTK);
				return NULL;
			}
		}
		else {
			error(tk, RIGHTBRACKET);
			return NULL;
		}

	}
	else {
		error(tk, LEFTBRACKET);
		return NULL;
	}

}


// <loop> -> while[<expr> <RO> <expr>]  <stat>
Node* loop() {
	std::cout << "loop called \n";
	Node* node = getNode(LOOPNODE);

	if (tk.type == LEFTBRACKETTK) {
		tk = scanner();
		node->child1 = expr();
		node->child2 = RO();
		node->child3 = expr();
		if (tk.type == RIGHTBRACKETTK) {
			tk = scanner();
			node->child4 = stat();
			return node;
		}
		else {
			error(tk, RIGHTBRACKET);
			return NULL;
		}
	}
	else {
		error(tk, LEFTBRACKET);
		return NULL;
	}

	return NULL;
}


//<assign> -> assign Identifier  = <expr>  
Node* assign() {
	std::cout << "assign called \n";

	Node* node = getNode(LOOPNODE);
	if (tk.type == IDTK) {
		node->token1 = tk;
		tk = scanner();

		if (tk.type == EQUALTK) {
			tk = scanner();
			node->child1 = expr();

		}
		else {
			error(tk, EQUALTK);
		}
	}
	else {
		error(tk, IDTK);
	}

	return NULL;

}


//<RO> -> > | < | == | { == }  (three tokens) | %
Node* RO() {
	std::cout << "RO called\n";
	Node* node = getNode(RONODE);

	if (tk.type == GREATERTHANTK) {
		node->token1 = tk;
		tk = scanner();

		return node;
	}
	else if (tk.type == LESSTHANTK) {
		node->token1 = tk;
		tk = scanner();

		return node;
	}
	else if (tk.type == EQEQTK) {
		node->token1 = tk;
		tk = scanner();

		return node;
	}
	else if (tk.type == LEFTBRACETK) {
		tk = scanner();

		if (tk.type == EQEQTK) {
			node->token1 = tk;
			tk = scanner();

			if (tk.type == RIGHTBRACETK) {
				tk = scanner();

			}
			else {
				error(tk, RIGHTBRACETK);
				return NULL;
			}
		}
		else {
			error(tk, EQEQTK);
			return NULL;
		}
	}
	else if (tk.type == MODULUSTK) {
		node->token1 = tk;
		tk = scanner();
		return node;

	}
	else {
		error(tk, GREATERTHANTK);
		return NULL;
	}

	return NULL;
}


//<goto> -> jump Identifier
Node* gotoFunc() {

	std::cout << "goto called\n";

	Node* node = getNode(GOTOFUNCNODE);

	if (tk.type == IDTK) {
		node->token1 = tk;
		tk = scanner();

		return node;
	}
	else {
		error(tk, IDTK);
		return NULL;
	}
}


//<label> -> label Identifier
Node* label() {
	std::cout << "label called\n";
	Node* node = getNode(GOTOFUNCNODE);

	if (tk.type == IDTK) {
		node->token1 = tk;
		tk = scanner();
		return node;
	}
	else {
		error(tk, IDTK);
		return NULL;
	}
}

void error(token errorTk, int expectedToken) {
	std::cout << "Parser Error: There is an error! \n";
	std::cout << "Parser Error: ERROR in tk " << expectedTokens[errorTk.type] << " expected " << expectedTokens[expectedToken] <<
		" in line " << tk.lineNum << "\n";
	exit(1);
}
