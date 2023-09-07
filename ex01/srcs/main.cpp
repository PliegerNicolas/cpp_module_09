/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:42:35 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/07 11:44:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "RPN.hpp"

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

// https://paodayag.dev/reverse-polish-notation-js-parser/
// Link can be useful to check but it's not sure if it's fail proof
int	main(int argc, char **argv)
{
	if (verifyArguments(--argc, ++argv))
		return (1);

	RPN	a;
	a.calculate(*argv);

	return (0);
}
