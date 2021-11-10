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
		stat();
		if (tk.type == STOPTK) {
			tk = scanner();
			return;
		}
		else {
			error(tk, STOPTK);
		}
	}
	else {
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
						error(tk, SEMICOLONTK);	//semicolon
						//error(tk, HOLDERTK);
					}
				}
				else {
					error(tk, INTEGERTK);	//integer
				}
			}
			else {
				error(tk, EQUALTK);		//equal 
			}
		}
		else {
			error(tk, IDTK);	//identifier
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
	if (tk.type == LISTENTK || tk.type == TALKTK) {
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
		//tk = scanner();
		in();
		//tk = scanner();
		//std::cout << "[" << expectedTokens[tk.type] << ", \"" << tk.tokenString
		//	<< "\", line " << tk.lineNum << ":" << tk.charNum << "]" << std::endl;

		std::cout << "SOme phrase";
		if (tk.type == SEMICOLONTK) {
			std::cout << "Got here\n";
			tk = scanner();
			return;
		}
		else {
			std::cout << "Error here\n";
			error(tk, SEMICOLONTK);
		}
	}
	else if (tk.type == TALKTK) {
		tk = scanner();
		out();
	} 
	else if (tk.type == STARTTK) {
		tk = scanner();
		block();
	}
	else if (tk.type == IFTK) {
		tk = scanner();
		ifStat();
	}
	else if (tk.type == WHILETK) {
		tk = scanner();
		loop();
	}
	else if (tk.type == ASSIGNTK) {
		tk = scanner();
		assign();
	}
	else if (tk.type == JUMPTK) {
		tk = scanner();
		gotoFunc();
	}
	else if (tk.type == LABELTK) {
		tk = scanner();
		label();
	}
}

void in() {
	std::cout << "in called \n";
	tk = scanner();
	if (tk.type == IDTK) {
		tk = scanner();
		return;
	}
	else {
		error(tk, IDTK);
	}
}

void out() {

}

void ifStat() {

}

void loop() {

}

void assign() {

}

void gotoFunc() {

}

void label() {

}

void error(token errorTk, int expectedToken) {
	std::cout << "Parser Error: There is an error! \n";
	std::cout << "Parser Error: ERROR in tk " <<errorTk.type<< " expected " << expectedTokens[tk.type] << 
		" in line " << tk.lineNum << "\n";
}
