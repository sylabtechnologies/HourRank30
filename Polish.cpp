// Polish.cpp - push all into stack
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;

#define _R1(x) x.begin(), x.end()
#define _RR1(x) x.rbegin(), x.rend()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter
#define _RR2(x) auto iter = x.rbegin(); iter != x.rend(); ++iter
#define PRN(x) cout << x << endl
void process_error(const string, const int);
#define ERR(X) process_error(X, __LINE__)

struct Expression
{
	char operation;			// mark 'N' if it is operand

	Expression* lhs;
	Expression* rhs;

	int lval;
	int rval;
	Expression() : operation('N'), lhs(NULL), rhs(NULL), lval(0), rval(0) {}
};


int main()
{
	string puzzle = "-?-??";

	Expression *current = NULL;
	list<Expression*> myStack;

	int count = 0;

	for (_RR2(puzzle))
	{
		if (*iter == '?')
		{
			count++;

			myStack.push_back(new Expression());

			if (count > 2) ERR("invalid token");
		}
		else
		{
			count = 0;

			switch (*iter)
			{
			case '-':
			case '+':
			case '*':
			case '/':
				current = new Expression;
				current->operation = *iter;
				current->lhs = myStack.back(); myStack.pop_back();
				current->rhs = myStack.back(); myStack.pop_back();
				myStack.push_back(current);
				break;

			default:
				ERR("invalid operation");
				break;
			}
		}
	}

    return 0;
}

void process_error(const string msg, const int line)
{
	cerr << __FILE__ << ", line " << line << endl;
	cerr << "Error: " << msg << endl;
	cerr << msg << endl;
	exit(EXIT_FAILURE);
}