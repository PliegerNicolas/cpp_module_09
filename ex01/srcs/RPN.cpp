/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:44:08 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/07 11:28:44 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "RPN.hpp"

/* Constructors & Destructors */

/* Public */

RPN::RPN(void)
{
	std::cout << TCYAN;
	std::cout << "RPN : Default constructor called";
	std::cout << WHITE << std::endl;
}

RPN::~RPN(void)
{
	std::cout << TCYAN;
	std::cout << "RPN : Default destructor called";
	std::cout << WHITE << std::endl;
}

/* Private */

RPN::RPN(const RPN &other):
	_stack(other._stack)
{
	std::cout << TCYAN;
	std::cout << "RPN : Copy constructor called";
	std::cout << WHITE << std::endl;

	(void)other;
}

RPN	&RPN::operator=(const RPN &other)
{
	std::cout << TCYAN;
	std::cout << "RPN : Assignment operator called";
	std::cout << WHITE << std::endl;

	if (this != &other)
	{
		_stack = other._stack;
	}
	return (*this);
}

/* Member Functions */

void	RPN::calculate(const std::string &expr)
{
	std::istringstream	exprStream(expr);
	std::string			token;
	double				number;

	double				operand1;
	double				operand2;

	try
	{
		verifyExpression(expr);

		while (exprStream >> token)
		{
			if (token == "+" || token == "-" || token == "*" || token == "/")
			{
				operand2 = _stack.top();
				_stack.pop();
				operand1 = _stack.top();
				_stack.pop();

				switch (token[0])
				{
					case '+':
						_stack.push(operand1 + operand2);
						break ;
					case '-':
						_stack.push(operand1 - operand2);
						break ;
					case '*':
						_stack.push(operand1 * operand2);
						break ;
					case '/':
						if (operand2 == 0)
							throw std::runtime_error("Error: divison by zero.");
						_stack.push(operand1 / operand2);
						break ;
				}
			}
			else
			{
				std::istringstream	convertToNumStream(token);
				convertToNumStream >> number;
				_stack.push(number);
			}
		}

		std::cout << _stack.top() << std::endl;
		_stack.pop();

	}
	catch (const std::exception &e)
	{
		std::cerr << RED << e.what() << WHITE << std::endl;
	}
}

/* Public */

// Getter functions

// Setter functions

/* Private */

void	RPN::verifyExpression(const std::string &expr)
{
	std::istringstream	exprStream(expr);
	std::string			token;
	int					operands_count;
	double				number;

	operands_count = 0;
	while (exprStream >> token)
	{
		if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			if (operands_count < 2)
				throw std::runtime_error("Error: too much operators.");
			operands_count--;
		}
		else
		{
			std::istringstream	convertToNumStream(token);
			if (!(convertToNumStream >> number))
				throw std::runtime_error("Error: expected a 'double' but found '"
					+ token + "'.");
			operands_count++;
		}
	}
	if (operands_count != 1)
		throw std::runtime_error("Error: not enough operators.");
}
