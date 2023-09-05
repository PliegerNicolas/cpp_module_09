/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 08:39:24 by nplieger          #+#    #+#             */
/*   Updated: 2023/09/05 14:58:16 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "outputUtils.hpp"

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

static void	isValidDate(const std::string &date)
{
	if (date.length() != 10)
		throw std::runtime_error("Error: bad input => " + date);
	if (date[4] != '-' || date[7] != '-')
		throw std::runtime_error("Error: bad input => " + date);

	for (size_t	i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue ;
		else if (!std::isdigit(date[i]))
			throw std::runtime_error("Error: bad input => " + date);
	}

	int	year = std::atoi(date.substr(0, 4).c_str());
	int	month = std::atoi(date.substr(5, 2).c_str());
	int	day = std::atoi(date.substr(8, 2).c_str());

	if (year < 2009 && month < 1 && day < 3)
		throw std::runtime_error("Error: bad input => " + date + " | BitCoin didn't exist yet.");

}

static void	isValidRate(const std::string &rate)
{
	const double	double_rate = stringToDouble(rate);

	if (double_rate <= 0)
		throw std::runtime_error("Error: not a positive number => " + rate);
	else if ( double_rate >= 1000)
		throw std::runtime_error("Error: too large a number => " + rate);
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
		else
			throw std::runtime_error("Error: invalid line format, expected two elements");
		isValidDate(date);
		isValidRate(rate);
		elements.first = date;
		elements.second = stringToDouble(rate);
	}
	else
		throw std::runtime_error("Error: invalid line format, expected at least one element");
	return (elements);
}
