/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:48:54 by nplieger          #+#    #+#             */
/*   Updated: 2023/09/06 13:35:37 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "Colors.hpp"
#include "utils.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>

class	BitcoinExchange
{
	private:
		/* Attributs */
		std::string						_fileName;
		std::fstream					*_CSV;
		std::map<std::string, double>	_stocks;

		/* Constructors & Destructors */
		
		BitcoinExchange(void);

		/* Member functions */

		std::fstream	*openFile(const std::string &fileName);
		void			fillStocks(void);

	protected:
		/* Attributs */

		/* Constructors & Destructors */

		/* Member functions */

	public:
		/* Attributs */

		/* Constructors & Destructors */
		BitcoinExchange(const std::string &fileName);

		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange	&operator=(const BitcoinExchange &other);

		~BitcoinExchange(void);

		/* Member functions */

		void	printStocks(void) const;
};
