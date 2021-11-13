//Sean Dela Pena
//File: parser.hpp
//

#ifndef PARSER_HPP
#define PARSER_HPP
#include "scanner.hpp"
#include "token.hpp"
#include "node.hpp"
#include "tree.hpp"

void getAllTokens(std::string filename);
token scanner();		//holds all the tokens and returns the token that is being worked on
Node* parser();
Node* program();
Node* block();
Node* vars();
Node* expr();
Node* N();
Node* A();
Node* M();
Node* R();
Node* stats();
Node* mStat();
Node* stat();
Node* in();
Node* out();
Node* ifStat();
Node* loop();
Node* assign();
Node* RO();
Node* label();
Node* gotoFunc();


void error(token errorTk, int expectedToken);

#endif