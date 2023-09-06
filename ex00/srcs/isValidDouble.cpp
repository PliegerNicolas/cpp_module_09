/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isValidDouble.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:58:30 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/06 19:56:29 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "utils.hpp"

void	isValidDouble(const std::string &str)
{
	bool	hasDecimalPoint = false;
	bool	hasDigits = false;
	bool	hasExponent = false;

	for (size_t i = 0; i < str.length(); i++)
	{
		if (i == 0 && (str[i] == '+' || str[i] == '-'))
			continue ;
		else if (isdigit(str[i]))
			hasDigits = true;
		else if (str[i] == '.')
		{
			if (hasDecimalPoint || hasExponent)
				throw std::runtime_error("Error: str cannot safely be converted to double");
			hasDecimalPoint = true;
		}
		else if (str[i] == 'e' || str[i] == 'E')
		{
			if (hasExponent || !hasDigits)
				throw std::runtime_error("Error: str cannot safely be converted to double");
			hasExponent = true;
		}
		else if (hasExponent
			&& (str[i] == '+' || str[i] == '-')
			&& (str[i - 1] == 'e' || str[i - 1] == 'E'))
			continue ;
		else
			throw std::runtime_error("Error: str cannot safely be converted to double");
	}
}
