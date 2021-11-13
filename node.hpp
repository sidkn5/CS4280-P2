//Sean Dela Pena
//FILE: node.hpp

#ifndef NODE_HPP
#define NODE_HPP
#include"token.hpp"

struct Node {

	token token1;
	token token2;

	Node* child1;
	Node* child2;
	Node* child3;
	Node* child4;
	Node* child5;

	int funcCalled;
};

#endif
