//Sean Dela Pena
//File: parser.cpp

static int vectorIndex = 0;
//use myVector.at(vectorIndex)
std::string filename;
std::vector<token> tks = testScanner(filename);

void scanner(int index) {
	return tks.at(index);
}

void parser() {

	tk = scanner(vectorIndex);
	program();
	if (tk.type == EOFTK) {

	}
	else {
		error();
	}
}

void program() {
	
}

void error() {
	std::cout << "Parser Error: There is an error! \n";
}
