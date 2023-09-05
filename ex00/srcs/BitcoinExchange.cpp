/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:18:48 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/05 15:14:24 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "BitcoinExchange.hpp"

/* Constructors & Destructors */

/* Public */

BitcoinExchange::BitcoinExchange(void)
{
	std::cout << TCYAN;
	std::cout << "BitcoinExchange : Default constructor called";
	std::cout << WHITE << std::endl;
}

BitcoinExchange::BitcoinExchange(std::ifstream &file)
{
	std::cout << TCYAN;
	std::cout << "BitcoinExchange : Constructor with file parameter called";
	std::cout << WHITE << std::endl;

	if (!file.is_open())
		throw std::runtime_error("File isn't open.");

	std::string						line;
	std::pair<std::string, double>	elements;
	bool							firstLine = true;

	try
	{
		while (std::getline(file, line))
		{
			if (firstLine)
			{
				firstLine = false;
				line = trim(line);
				if (line.compare(0, line.length(), "date,exchange_rate") == 0)
					continue ;
			}
			elements = splitLine(line, ',');
			_map.insert(elements);
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other): _map(other._map)
{
	std::cout << TCYAN;
	std::cout << "BitcoinExchange : Copy constructor called";
	std::cout << WHITE << std::endl;

	(void)other;
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &other)
{
	std::cout << TCYAN;
	std::cout << "BitcoinExchange : Assignment operator called";
	std::cout << WHITE << std::endl;

	if (this != &other)
	{
		_map = other._map;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{
	std::cout << TCYAN;
	std::cout << "BitcoinExchange : Default destructor called";
	std::cout << WHITE << std::endl;
}

/* Member Functions */

std::ifstream	BitcoinExchange::openFile(const std::string &fileName) const
{
	std::ifstream	file;

	file.open(fileName);
	if (file.fail())
	{
		if (errno == EACCES)
			throw std::runtime_error("Error: " + fileName + "isn't available.");
		else
			throw std::runtime_error("Error: " + fileName + "isn't available (permission denied).");
	}
	return (file);
}


void	BitcoinExchange::convertBitcoin(std::ifstream &file) const
{
	if (!file.is_open())
		throw std::runtime_error("File isn't open.");

	std::string						line;
	std::pair<std::string, double>	elements;
	bool							firstLine = true;

	while (std::getline(file, line))
	{
		try
		{
			if (firstLine)
			{
				firstLine = false;
				line = trim(line);
				if (line.compare(0, line.length(), "date,exchange_rate") == 0)
					continue ;
			}
			elements = splitLine(line, ',');
			//_map.insert(elements);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

/* Public */

// Getter functions

// Setter functions

/* Private */
