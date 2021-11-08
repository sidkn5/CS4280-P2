//Sean Dela Pena
//File: parser.hpp
//

#ifndef PARSER_HPP
#define PARSER_HPP
#include "scanner.hpp"

void scanner(int index);		//holds all the tokens and returns the token that is being worked on
void parser();
void program();
void block();
void vars();
void expr();
void N();
void A();
void M();
void R();
void stats();
void mStat();
void stat();
void in();
void out();
void ifStat();
void loop();
void assign();
void RO();
void label();
void gotoFunc();


void error();

#endif