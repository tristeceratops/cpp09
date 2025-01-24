#include "RPN.hpp"

RPN::RPN() : _rpn("") {}

RPN::RPN(std::string rpn) : _rpn(rpn) {}

RPN::RPN(const RPN &rpn) : _rpn(rpn._rpn) {}

RPN::~RPN() {}

RPN &RPN::operator=(const RPN &rpn)
{
	if (this != &rpn)
	{
		_rpn = rpn._rpn;
	}
	return *this;
}

void RPN::setRPN(std::string rpn)
{
	_rpn = rpn;
}

std::string RPN::getRPN() const
{
	return _rpn;
}

void printStack(std::stack<int> stack)
{
	std::stack<int> tmp = stack;
	std::cout << "Stack: ";
	while (!tmp.empty())
	{
		std::cout << tmp.top() << " ";
		tmp.pop();
	}
	std::cout << std::endl;
}

std::string trim(const std::string &str) {
	std::string::const_iterator it = str.begin();
	while (it != str.end() && std::isspace(*it)) {
		++it;
	}

	std::string::const_reverse_iterator rit = str.rbegin();
	while (rit.base() != it && std::isspace(*rit)) {
		++rit;
	}

	return std::string(it, rit.base());
}

int RPN::calculate()
{

	std::string rpn = trim(_rpn);
	std::string token;
	int a, b;

	//check if rpn respect the standard
	//no charactere except numbers and operators +-*/
	
	for (size_t i = 0; i < rpn.size(); i++)
	{
		if (!std::isdigit(rpn[i]) && rpn[i] != ' ' && rpn[i] != '+' && rpn[i] != '-' && rpn[i] != '*' && rpn[i] != '/')
			throw wrongArgumentException();
	}

	while (rpn.find(" ") != std::string::npos || rpn.size() > 0)
	{
		
		token = rpn.substr(0, rpn.find(" "));
		if (rpn.find(" ") != std::string::npos)
			rpn = rpn.substr(rpn.find(" ") + 1);
		else
			rpn.clear();
		// std::cout << "Token: \"" << token << "\"" << std::endl;
		// std::cout << "RPN: \"" << rpn << "\"" << std::endl;

		if (token == "+")
		{
			a = _stack.top();
			_stack.pop();
			b = _stack.top();
			_stack.pop();
			_stack.push(b + a);
		}
		else if (token == "-")
		{
			a = _stack.top();
			_stack.pop();
			b = _stack.top();
			_stack.pop();
			_stack.push(b - a);
		}
		else if (token == "*")
		{
			a = _stack.top();
			_stack.pop();
			b = _stack.top();
			_stack.pop();
			_stack.push(b * a);
		}
		else if (token == "/")
		{
			a = _stack.top();
			_stack.pop();
			b = _stack.top();
			_stack.pop();
			if (a == 0)
				throw divideByZeroException();
			_stack.push(b / a);
		}
		else
		{
			std::stringstream ss(token);
			ss >> a;
			_stack.push(a);
		}
		// printStack(_stack);
	}
	if (_stack.size() != 1)
		throw wrongCalculException();
	return _stack.top();
}