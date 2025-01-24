#pragma once
#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <exception>

class RPN
{
	private:
		std::string _rpn;
		std::stack<int> _stack;
	public:
		RPN();
		RPN(std::string rpn);
		RPN(const RPN &rpn);

		RPN &operator=(const RPN &rpn);

		void setRPN(std::string rpn);
		std::string getRPN() const;

		int calculate();

		~RPN();

		class divideByZeroException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return "Division by zero";
				}
		};

		class wrongArgumentException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return "Wrong argument, only numbers and operators (+-*/) are allowed";
				}
		};

		class wrongCalculException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return "Not respect RPN standard";
				}
		};

};