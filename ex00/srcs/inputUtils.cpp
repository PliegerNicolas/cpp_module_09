/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputUtils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 08:39:24 by nplieger          #+#    #+#             */
/*   Updated: 2023/09/05 14:59:50 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "inputUtils.hpp"

std::string	&trim(std::string &str)
{
	size_t	pos;

	pos = str.find_first_not_of(" \t\n\r");
	if (pos != std::string::npos)
		str.erase(0, pos);
	pos = str.find_last_not_of(" \t\n\r");
	if (pos != std::string::npos)
		str.erase(pos + 1);
	return (str);
}

static double	stringToDouble(std::string str)
{
	return (strtod(str.c_str(), NULL));
}

std::pair<std::string, double>	splitLine(const std::string &line, const char c)
{
	std::pair<std::string, double>	elements;
	std::string						date;
	std::string						rate;
	std::istringstream				ss(line);

	if (std::getline(ss, date, c))
	{
		date = trim(date);
		if (std::getline(ss, rate, c))
			rate = trim(rate);
		elements.first = date;
		elements.second = stringToDouble(rate);
	}
	return (elements);
}
