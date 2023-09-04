/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:18:48 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/04 18:37:13 by nicolas          ###   ########.fr       */
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

	std::string	line;

	while (std::getline(file, line))
	{
		std::cout << line << std::endl;
		// temp
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
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
		(void)other;
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

/* Public */

// Getter functions

// Setter functions

/* Private */
