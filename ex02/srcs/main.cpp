/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:15:58 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/14 23:15:28 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "MergeVector.hpp"
#include "MergeDeque.hpp"

static bool	verifyArguments(int argc, char **argv)
{
	if (argc != 1)
	{
		std::cerr << RED;
		std::cerr << "Error: 1 argument expected, " << argc << " received.";
		std::cerr << WHITE << std::endl;
		return (1);
	}
	(void)argv;
	return (0);
}

int	main(int argc, char **argv)
{
	if (verifyArguments(--argc, ++argv))
		return (1);

	MergeVector<size_t>	vect(*argv);
	MergeDeque<size_t>	deque(*argv);

	vect.fordJohnsonSort();
	deque.fordJohnsonSort();
	
	std::cout << "vect : " << vect.getElapsedTime() << "ms" << std::endl;
	std::cout << "deque : " << deque.getElapsedTime() << "ms" << std::endl;

	return (0);
}
