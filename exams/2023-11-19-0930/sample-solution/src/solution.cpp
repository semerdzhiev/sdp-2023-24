#include "solution.h"

#include <cassert>
#include <stdexcept>
#include <stack>

bool verify(const std::string& expression)
{
	if(expression.empty()) // "" is a valid expression
		return true;

	if( ! isDigit(expression[0])) // the first symbol in an expression must be a digit
		return false;

	if( expression.size() % 2 == 0 ) // valid expressions are with odd lengths
		return false;

	for(size_t i = 1; i < expression.size(); i += 2) {
		if( ! isOperation(expression[i]) || ! isDigit(expression[i+1]) ) // incorrect sequence
			return false;
	}
	
	return true;
}

bool needToReduce(const std::stack<char>& ops, char nextOp, Associativity associativity)
{
	if(associativity == Associativity::Left)
		return ! ops.empty() && priority(nextOp) <= priority(ops.top());
	else
		return ! ops.empty() && priority(nextOp) < priority(ops.top());
}

std::string toRpn(const std::string& expression, Associativity associativity)
{
	if( ! verify(expression))
		throw std::invalid_argument("invalid expression");

	if(expression.empty())
		return expression;

	std::stack<char> ops;
	std::string result;

	result += expression[0];

	for(size_t i = 1; i < expression.size(); i+=2) {
		const char& op = expression[i];
		const char& arg = expression[i+1];

		while(needToReduce(ops, op, associativity)) {
			result += ops.top();
			ops.pop();
		}

		result += arg;
		ops.push(op);
	}

	while(!ops.empty()) {
		result += ops.top();
		ops.pop();
	}

	return result;
}
