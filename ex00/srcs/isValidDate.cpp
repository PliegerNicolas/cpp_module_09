/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isValidDate.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:27:05 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/18 04:08:35 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "utils.hpp"

static int	parseDate(std::istringstream &iss, const char separator)
{
	int		date;
	char	sep;

	if (!(iss >> date))
		throw std::runtime_error("Error: unsuccessful date parse.");

	if (!(iss >> sep))
	{
		iss.clear();
		iss.seekg(-1, std::ios::cur);
	}
	else if (sep != separator)
		throw std::runtime_error("Error: invalid separator.");

	return (date);
}

static bool	isBeforeBitcoinCreationDate(int &year, int &month, int &day)
{
	return ((year < 2009)
		|| (year == 2009 && month < 1)
		|| (year == 2009 && month == 1 && day < 3));
}

void	isValidDate(const std::string &date, const char separator, const bool &moreChecks)
{
	std::istringstream	iss(date);
	int					year = parseDate(iss, separator);
	int					month = parseDate(iss, separator);
	int					day = parseDate(iss, separator);

	if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
		throw std::runtime_error("Error: invalid year, month, or day.");

	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
        	throw std::runtime_error("Error: invalid day.");
	}
	else if (month == 2)
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			if (day > 29)
        		throw std::runtime_error("Error: invalid day.");
		}
		else
		{
			if (day > 28)
        		throw std::runtime_error("Error: invalid day.");
		}
	}

	if (moreChecks && isBeforeBitcoinCreationDate(year, month, day))
    	throw std::runtime_error("Error: given date before Bitcoin creation date.");
}
