//  542_hw8_smyth.cpp
//  CS 542 - Discrete Structures
//  Homework #8

#include <iostream>
#include <stack>
#include <string>
//#include "stdafx.h"
using namespace std;

stack <char> operators;
stack <int> operands;
char priority[] = { '!', '&', '^', '|', '(' , ')' };

bool evaluate(string exp);
void operation();
bool higherPriority(char a, char b);
int find(char c);

int main()
{
	//string exp;

	cout << "Input boolean expression: ";
	//cin >> exp;

	cout << evaluate("0&1|(1&!1)") << endl;

}


bool evaluate(string exp) {
	for (int i = 0; i < exp.length(); i++)
		switch (exp[i]) {
		case ' ': break;
		case '0': operands.push(0); break;
		case '1': operands.push(1); break;
		case '(': operators.push('('); break;
		case ')':
			while (operators.top() != '(')
				operation();
			operators.pop();
			break;
		default:
			while (!operators.empty() && !higherPriority(exp[i], operators.top()))
				operation();
			operators.push(exp[i]);
		}

	while (!operators.empty())
		operation();

	return operands.top();
}

void operation() {
	int a = operands.top();
	operands.pop();
	int b = -1;
	if (operators.top() != '!') { b = operands.top(); operands.pop(); }
	int op = operators.top(); operators.pop();

	switch (op) {
	case '!': operands.push(!a); break;
	case '&': operands.push(a & b); break;
	case '^': operands.push(a ^ b); break;
	case '|': operands.push(a | b); break;
	}


}

bool higherPriority(char a, char b) {
	if (find(a) < find(b)) return true;
	return false;
}

int find(char c) {
	for (int i = 0; i < 6; i++)
		if (c == priority[i]) return i;
	return -1;
}
