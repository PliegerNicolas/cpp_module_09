/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:18:48 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/06 20:18:43 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "BitcoinExchange.hpp"

/* Constructors & Destructors */

/* Public */

BitcoinExchange::BitcoinExchange(void):
	_stocksFileName("data.csv"),
	_CSV(NULL)
{
	std::cout << TCYAN;
	std::cout << "BitcoinExchange : Default constructor called";
	std::cout << WHITE << std::endl;

	try
	{
		_CSV = openFile(_stocksFileName);

		ProcessFunction	func;
		BitcoinExchange::readFileData	rfd;
		
		func = &BitcoinExchange::fillStocks;
		rfd.dateTitle = "date";
		rfd.valueTitle = "exchange_rate";
		rfd.separator = ',';

		readAndExecuteOnFile(_CSV, func, rfd);
	}
	catch (const std::exception &e)
	{
		_CSV = NULL;
		std::cerr << e.what() << std::endl;
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other):
	_stocksFileName(other._stocksFileName),
	_stocks(other._stocks)
{
	std::cout << TCYAN;
	std::cout << "BitcoinExchange : Copy constructor called";
	std::cout << WHITE << std::endl;

	try
	{
		_CSV = openFile(_stocksFileName);
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
			_CSV = openFile(_stocksFileName);
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

void	BitcoinExchange::convert(const std::string &fileName)
{
	ProcessFunction	func;
	BitcoinExchange::readFileData	rfd;
	std::fstream	*file;

	try
	{
		file = openFile(fileName);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		func = &BitcoinExchange::getAndPrintPrice;
		rfd.dateTitle = "date";
		rfd.valueTitle = "value";
		rfd.separator = '|';

		readAndExecuteOnFile(file, func, rfd);
	}
	catch (const std::exception &e)
	{
		if (file)
		{
			if (file->is_open())
				file->close();
			delete file;
		}
		std::cerr << e.what() << std::endl;
	}

	if (file)
	{
		if (file->is_open())
			file->close();
		delete file;
	}
}

/* Public */

// Getter functions

// Setter functions

/* Private */

/* Member Functions */

std::fstream	*BitcoinExchange::openFile(const std::string &fileName) const
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

void	BitcoinExchange::readAndExecuteOnFile(std::fstream *file, ProcessFunction func,
	const BitcoinExchange::readFileData &rfd)
{
	if (!file || !file->is_open())
		return ;

	std::string						line;
	bool							firstLine;

	std::string						dateStr;
	std::string						valueStr;
	
	firstLine = true;
	while (std::getline(*file, line))
	{
		std::istringstream	linestream(line);

		try
		{
			// verify if dateStr and valueStr retrieval successful
			if (!std::getline(linestream, dateStr, rfd.separator))
				throw std::runtime_error("Error: bad input => '" + line + "'.");
			if (!std::getline(linestream, valueStr))
				throw std::runtime_error("Error: bad input => '" + line + "'.");
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			continue ;
		}

		// trim retrieved strings
		trimString(dateStr);
		trimString(valueStr);

		// filter out first line if needed
		if (firstLine
			&& dateStr.compare(0, dateStr.length(), rfd.dateTitle) == 0
			&& valueStr.compare(0, valueStr.length(), rfd.valueTitle) == 0)
		{
			firstLine = false;
			continue ;
		}

		// convert valueStr to double and execute passed function
		try
		{
			(this->*func)(dateStr, valueStr);
		}
		catch(const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

void	BitcoinExchange::fillStocks(const std::string &dateStr, const std::string &valueStr)
{
	double	value;

	isValidDate(dateStr, '-', false);
	isValidDouble(valueStr);
	value = std::strtod(valueStr.c_str(), NULL);
	_stocks.insert(std::make_pair(dateStr, value));
}

void	BitcoinExchange::getAndPrintPrice(const std::string &dateStr, const std::string &valueStr)
{
	double	value;
	std::map<std::string, double>::const_iterator	it;

	isValidDate(dateStr, '-', true);
	isValidDouble(valueStr);
	value = std::strtod(valueStr.c_str(), NULL);
	if (value < 0)
		throw std::runtime_error("Error: not a positive number.");
	else if (value > 1000)
		throw std::runtime_error("Error: too large a number (max 999).");

	it = _stocks.find(dateStr);
	if (it != _stocks.end())
	{
		// exact date found.
		std::cout << dateStr << " => " << value << " = " << value * it->second << std::endl;
	}
	else
	{
		it = _stocks.lower_bound(dateStr);
		if (it != _stocks.begin())
		{
			// previous date found.
			std::cout << dateStr << " => " << value << " = " << value * it->second << std::endl;
		}
		else
		{
			throw std::runtime_error("Error: couldn't find related date data.");
		}
	}
}
