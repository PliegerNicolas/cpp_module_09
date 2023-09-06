/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:48:54 by nplieger          #+#    #+#             */
/*   Updated: 2023/09/06 19:47:52 by nicolas          ###   ########.fr       */
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
		/* Struct */
		typedef void (BitcoinExchange::*ProcessFunction)(const std::string &, const std::string &);
	
		struct readFileData
		{
			std::string	dateTitle;
			std::string	valueTitle;
			char		separator;
		};

		/* Attributs */
		const std::string				_stocksFileName;
		std::fstream					*_CSV;
		std::map<std::string, double>	_stocks;

		/* Constructors & Destructors */
		

		/* Member functions */

		std::fstream	*openFile(const std::string &fileName) const;
		void			readAndExecuteOnFile(std::fstream *file, ProcessFunction func,
							const BitcoinExchange::readFileData &rfd);

		void			fillStocks(const std::string &dateStr, const std::string &valueStr);
		void			getAndPrintPrice(const std::string &dateStr, const std::string &valueStr);


	protected:
		/* Attributs */

		/* Constructors & Destructors */

		/* Member functions */

	public:
		/* Attributs */

		/* Constructors & Destructors */
		BitcoinExchange(void);

		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange	&operator=(const BitcoinExchange &other);

		~BitcoinExchange(void);

		/* Member functions */

		void	printStocks(void) const;
		void	convert(const std::string &fileName);
};
