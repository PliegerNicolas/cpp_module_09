/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:43:50 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/07 11:10:10 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "Colors.hpp"

#include <iostream>
#include <sstream>
#include <stack>
#include <exception>

class	RPN
{
	private:
		/* Types */

		/* Attributs */
		std::stack<double>	_stack;

		/* Constructors & Destructors */
		RPN(const RPN &other);
		RPN	&operator=(const RPN &other);

		/* Member functions */
		void	verifyExpression(const std::string &expr);

	protected:
		/* Attributs */

		/* Constructors & Destructors */

		/* Member functions */

	public:
		/* Attributs */

		/* Constructors & Destructors */
		RPN(void);
		~RPN(void);

		/* Member functions */
		void	calculate(const std::string &expr);
};
