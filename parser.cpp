//Sean Dela Pena
//File: parser.cpp

#include "parser.hpp"
#include "scanner.hpp"
#include "token.hpp"

static int index = -1;
static token tk;
//use myVector.at(vectorIndex)
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


	std::cout << "[" << expectedTokens[allTokens[index].type] << ", \"" << allTokens[index].tokenString
		<< "\", line " << allTokens[index].lineNum << ":" << allTokens[index].charNum << "]" << std::endl;


	return allTokens.at(index);
}

void parser() {

	tk = scanner();
	program();
	if (tk.type == EOFTK) {
		std::cout << "Parser Completed/Passed\n";
		exit(1);
		//end
	}
	else {
		error(tk, PROGRAMTK);
	}
}

// <vars> program <block>
void program() {

	std::cout << "Program called \n";
	vars();

	if (tk.type == PROGRAMTK) {
		tk = scanner();
		block();
	}
	else {
		error(tk, PROGRAMTK);
	}
}

//start <vars> <stats> stop
void block() {

	std::cout << "block called \n";
	if (tk.type == STARTTK) {
		tk = scanner();
		vars();
		stats();
		if (tk.type == STOPTK) {
			tk = scanner();
			return;
		}
		else {
			error(tk, STOPTK);
		}
	}
	else {
		std::cout << "error here \n";
		error(tk, STOPTK);
	}
}


// empty | declare Identifier =  Integer  ;  <vars> 
void vars() {
	std::cout << "vars called \n";
	if (tk.type == DECLARETK) {
		tk = scanner();

		if (tk.type == IDTK) {
			tk = scanner();

			if (tk.type == EQUALTK) {
				tk = scanner();

				if (tk.type == INTEGERTK) {
					tk = scanner();

					if (tk.type == SEMICOLONTK) {
						tk = scanner();
						vars();
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
		return;	//vars can be empty
	}
}

//<expr> -> <N> + <expr>  | <N>
void expr() {
	std::cout << "expr called \n";
	N();
	if (tk.type == PLUSTK) {
		tk = scanner();
		expr();

	}
	else {
		return;
	}

}

//<N> -> <A> / <N> | <A> *<N> | <A>
void N() {
	std::cout << "N called \n";
	A();

	if (tk.type == DIVIDETK || tk.type == MULTIPLYTK) {
		tk = scanner();
		N();
	}
	else {
		return;
	}
}


//<A> -> <M>-<A> | <M>
void A() {
	std::cout << "A called \n";
	M();

	if (tk.type == MINUSTK) {
		tk = scanner();
		A();
	}
	else {
		error(tk, MINUSTK);
	}
}

//not done
//<M> -> . <M> | <R>
void M() {
	if (tk.type == DOTTK) {
		tk = scanner();
		M();
	}
	else {
		R();
	}
}


//<R> -> ( <expr> ) | Identifier | Integer
void R() {
	if (tk.type == LEFTPARENTK) {
		tk = scanner();
		expr();

		if (tk.type == RIGHTPARENTK) {
			tk = scanner();
		}
		else {
			error(tk, RIGHTPARENTK);
		}
	}
	else if (tk.type == IDTK) {
		tk = scanner();
		return;
	}
	else if (tk.type == INTEGERTK) {
		tk = scanner();
		return;
	}
	else {
		return;
	}
}

//<stats> -> <stat>  <mStat>
void stats() {
	std::cout << "stats called \n";
	stat();
	mStat();
}


void mStat() {
	
	std::cout << "mstat called \n";
	if (tk.type == LISTENTK || tk.type == TALKTK || tk.type == STARTTK || tk.type == IFTK || tk.type == WHILETK 
		|| tk.type == ASSIGNTK || tk.type == JUMPTK || tk.type == LABELTK) {
		stat();
		mStat();
	}
	else {
		return;
	}

}

void stat() {
	std::cout << "stat called \n";
	if (tk.type == LISTENTK) {
		tk = scanner();
		in();
		
		//std::cout << "[2" << expectedTokens[tk.type] << ", \"" << tk.tokenString
		//	<< "\", line " << tk.lineNum << ":" << tk.charNum << "]" << std::endl;
		if (tk.type == SEMICOLONTK) {
			tk = scanner();
			
			return;
		}
		else {
			error(tk, SEMICOLONTK);
		}
	}
	else if (tk.type == TALKTK) {
		tk = scanner();
		out();

		if (tk.type == SEMICOLONTK) {
			tk = scanner();

			return;
		}
		else {
			error(tk, SEMICOLONTK);
		}
	} 
	else if (tk.type == STARTTK) {
		//tk = scanner();
		block();

	}
	else if (tk.type == IFTK) {
		tk = scanner();
		ifStat();

		if (tk.type == SEMICOLONTK) {
			tk = scanner();

			return;
		}
		else {
			error(tk, SEMICOLONTK);
		}
	}
	else if (tk.type == WHILETK) {
		tk = scanner();
		loop();

		if (tk.type == SEMICOLONTK) {
			tk = scanner();

			return;
		}
		else {
			error(tk, SEMICOLONTK);
		}
	}
	else if (tk.type == ASSIGNTK) {
		tk = scanner();
		assign();

		if (tk.type == SEMICOLONTK) {
			tk = scanner();

			return;
		}
		else {
			error(tk, SEMICOLONTK);
		}
	}
	else if (tk.type == JUMPTK) {
		tk = scanner();
		gotoFunc();

		if (tk.type == SEMICOLONTK) {
			tk = scanner();
			
			return;
		}
		else {
			error(tk, SEMICOLONTK);
		}
	}
	else if (tk.type == LABELTK) {
		tk = scanner();
		label();

		if (tk.type == SEMICOLONTK) {
			tk = scanner();
			
			return;
		}
		else {
			error(tk, SEMICOLONTK);
		}
	}
	else {
		std::cout << "got here somehow\n";
	}
}

void in() {
	std::cout << "in called \n";
	
	if (tk.type == IDTK) {
		tk = scanner();
		return;
	}
	else {
		std::cout << "Got here here1\n";
		error(tk, IDTK);
	}
}

void out() {
	std::cout << "out called\n";
	expr();

}

void ifStat() {

}

void loop() {

	if (tk.type == LEFTBRACKETTK) {
		tk = scanner();
		expr();
		RO();
		expr();
		if (tk.type == RIGHTBRACKETTK) {
			tk = scanner();
			stat();
		}
		else {
			error(tk, RIGHTBRACKET);
		}
	}
	else {
		error(tk, LEFTBRACKET);
	}
}

void assign() {

	if (tk.type == IDTK) {
		tk = scanner();

		if (tk.type == EQUALTK) {
			tk = scanner();
			expr();
		}
		else {
			error(tk, EQUALTK);
		}
	}
	else {
		error(tk, IDTK);
	}

}

void RO() {

	if (tk.type == GREATERTHANTK) {
		tk = scanner();
	}
	else if (tk.type == LESSTHANTK) {
		tk = scanner();
	}
	else if (tk.type == EQEQTK) {
		tk = scanner();
	}
	else if (tk.type == LEFTBRACETK) {
		tk = scanner();

		if (tk.type == EQEQTK) {
			tk = scanner();

			if (tk.type == RIGHTBRACETK) {
				tk = scanner();

			}
			else {
				error(tk, RIGHTBRACETK);
			}
		}
		else {
			error(tk, EQEQTK);
		}
	}
	else if (tk.type == MODULUSTK) {
		tk = scanner();

	}
	else {
		error(tk, GREATERTHANTK);
	}
}

void gotoFunc() {

	if (tk.type == IDTK) {
		tk = scanner();
	}
	else {
		error(tk, IDTK);
	}
}

void label() {
	
	if (tk.type == IDTK) {
		tk = scanner();
	}
	else {
		error(tk, IDTK);
	}
}

void error(token errorTk, int expectedToken) {
	std::cout << "Parser Error: There is an error! \n";
	std::cout << "Parser Error: ERROR in tk " << expectedTokens[errorTk.type] << " expected " << expectedTokens[expectedToken] <<
		" in line " << tk.lineNum << "\n";
	exit(1);
}
