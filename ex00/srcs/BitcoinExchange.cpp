/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:18:48 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/06 13:37:26 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "BitcoinExchange.hpp"

/* Constructors & Destructors */

/* Public */

BitcoinExchange::BitcoinExchange(void):
	_fileName(""),
	_CSV(NULL)
{
	std::cout << TCYAN;
	std::cout << "BitcoinExchange : Default constructor called";
	std::cout << WHITE << std::endl;
}

BitcoinExchange::BitcoinExchange(const std::string &fileName):
	_fileName(fileName)
{
	std::cout << TCYAN;
	std::cout << "BitcoinExchange : Constructor with file parameter called";
	std::cout << WHITE << std::endl;

	try
	{
		_CSV = openFile(_fileName);
		fillStocks();
	}
	catch (const std::exception &e)
	{
		_CSV = NULL;
		std::cerr << e.what() << std::endl;
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other):
	_fileName(other._fileName),
	_stocks(other._stocks)
{
	std::cout << TCYAN;
	std::cout << "BitcoinExchange : Copy constructor called";
	std::cout << WHITE << std::endl;

	try
	{
		_CSV = openFile(_fileName);
	}
	catch (const std::exception &e)
	{
		_CSV = NULL;
		std::cerr << e.what() << std::endl;
	}
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &other)
{
	std::cout << TCYAN;
	std::cout << "BitcoinExchange : Assignment operator called";
	std::cout << WHITE << std::endl;

	if (this != &other)
	{
		_fileName = other._fileName;
		_stocks = other._stocks;
		try
		{
			if (_CSV)
			{
				if (_CSV->is_open())
					_CSV->close();
				delete _CSV;
				_CSV = NULL;
			}
			_CSV = openFile(_fileName);
		}
		catch (const std::exception &e)
		{
			_CSV = NULL;
			std::cerr << e.what() << std::endl;
		}
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{
	std::cout << TCYAN;
	std::cout << "BitcoinExchange : Default destructor called";
	std::cout << WHITE << std::endl;

	if (_CSV)
	{
		if (_CSV->is_open())
			_CSV->close();
		delete _CSV;
		_CSV = NULL;
	}
}

/* Member Functions */

void	BitcoinExchange::printStocks(void) const
{
	std::map<std::string, double>::const_iterator it = _stocks.begin();
	std::map<std::string, double>::const_iterator it_end = _stocks.end();

	while (it != it_end)
	{
		std::cout << it->first << " " << it->second << std::endl;
		it++;
	}
}

/* Public */

// Getter functions

// Setter functions

/* Private */

/* Member Functions */

std::fstream	*BitcoinExchange::openFile(const std::string &fileName)
{
	std::fstream	*file = new std::fstream;

	file->open(fileName.c_str(), std::ios::in);
	if (file->fail())
	{
		delete file;
		if (errno == EACCES)
			throw std::runtime_error("Error: '"
				+ fileName + "' file isn't available (permission denied).");
		else
			throw std::runtime_error("Error: '"
				+ fileName + "' file isn't available.");
	}
	return (file);
}

void	BitcoinExchange::fillStocks(void)
{
	if (!_CSV || !_CSV->is_open())
		return ;

	std::string						line;
	std::string						date_str;
	std::string						rate_str;
	double							rate;
	bool							firstLine = true;

	while (std::getline(*_CSV, line))
	{
		std::istringstream	linestream(line);

		if (!std::getline(linestream, date_str, ','))
			throw std::runtime_error("Error: <"
				+ _fileName + " parsing> ',' expected.");
		if (!std::getline(linestream, rate_str))
			throw std::runtime_error("Error: <"
				+ _fileName + " parsing> no newline found at end of line.");
		if (firstLine
			&& date_str.compare(0, date_str.length(), "date") == 0
			&& rate_str.compare(0, rate_str.length(), "exchange_rate") == 0)
		{
			firstLine = false;
			continue ;
		}
		try
		{
			isValidDate(date_str, '-');
			isValidDouble(rate_str);
			rate = std::strtod(rate_str.c_str(), NULL);
			_stocks.insert(std::make_pair(date_str, rate));
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}
