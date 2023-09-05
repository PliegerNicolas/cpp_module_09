/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:29:55 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/05 15:10:34 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "BitcoinExchange.hpp"

static bool	verifyArguments(int argc, char **argv)
{
	if (argc != 1)
	{
		std::cerr << RED;
		std::cerr << "Error: 1 argument expected, " << argc << " received.";
		std::cerr << WHITE << std::endl;
		return (1);
	}
	else if (!argv || !**argv)
	{
		std::cerr << RED;
		std::cerr << "Error: empty argument passed.";
		std::cerr << WHITE << std::endl;
		return (1);
	}
	return (0);
}

static bool	openFile(std::ifstream &file, char *filename)
{
	file.open(filename);
	if (file.fail())
	{
		std::cerr << RED;
		std::cerr << "Error: " << filename << " isn't available";
		if (errno == EACCES)
			std::cerr << " (Permission denied)";
		std::cerr << "." << WHITE << std::endl;
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	std::ifstream	file;

	if (verifyArguments(--argc, ++argv))
		return (1);
	if (openFile(file, *argv))
		return (1);

	BitcoinExchange	bt(file);
	bt.convertBitcoin(file);

	file.close();
	return (0);
}
