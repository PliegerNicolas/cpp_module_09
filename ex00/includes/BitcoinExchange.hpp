/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:48:54 by nplieger          #+#    #+#             */
/*   Updated: 2023/09/05 15:12:33 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "Colors.hpp"
#include "inputUtils.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

class	BitcoinExchange
{
	private:
		/* Attributs */
		std::map<std::string, float>	_map;

		/* Constructors & Destructors */

		/* Member functions */

	protected:
		/* Attributs */

		/* Constructors & Destructors */

		/* Member functions */

	public:
		/* Attributs */

		/* Constructors & Destructors */
		BitcoinExchange(void);
		BitcoinExchange(std::ifstream &file);

		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange	&operator=(const BitcoinExchange &other);

		~BitcoinExchange(void);

		/* Member functions */

		std::ifstream	openFile(const std::string &fileName) const;
		void	convertBitcoin(std::ifstream &file) const;
};
