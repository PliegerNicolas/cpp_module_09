/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:29:55 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/06 20:29:18 by nicolas          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	if (verifyArguments(--argc, ++argv))
		return (1);
	
	BitcoinExchange	bt1;
	bt1.convert(*argv);
	/*
	BitcoinExchange	bt2(bt1);
	BitcoinExchange bt3;
	bt3 = bt2;
	bt3.convert(*argv);
	*/

	return (0);
}
