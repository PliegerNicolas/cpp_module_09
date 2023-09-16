/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:15:58 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/16 19:27:09 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "PmergeMe.hpp"
#include <iomanip>

static bool	verifyArguments(int argc, char **argv)
{
	if (argc <= 0)
	{
		std::cerr << RED;
		std::cerr << "Error: 1 argument expected, " << argc << " received.";
		std::cerr << WHITE << std::endl;
		return (1);
	}
	(void)argv;
	return (0);
}

template <typename Container>
static void	displayData(Container &container)
{
	std::cout << CYAN;
	std::cout << "Before:  " << WHITE << container.printUnsortedData();
	std::cout << std::endl;
	std::cout << CYAN;
	std::cout << "After:   " << WHITE << container.printSortedData();
	std::cout << std::endl;
}

template <typename Container>
static void	displayTime(Container &container, const std::string &containerType)
{
	std::cout << CYAN << "Time to process a range of ";
	std::cout << WHITE << std::setw(5) << container.getUnsortedData().size();
	std::cout << CYAN << " elements with ";
	std::cout << WHITE << containerType << CYAN << " : " << WHITE;
	std::cout << std::setprecision(8) << container.getElapsedTime() << " ms";
	std::cout << CYAN << "." << WHITE << std::endl;
}

template <typename Container>
static void	initializePmergeMe(Container &container, const int &argc, char **argv)
{
	try
	{
		if (argc > 1)
			container.setUnsortedData(argc, argv);
		else
			container.setUnsortedData(argv[1]);
		container.fordJohnsonSort();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

int	main(int argc, char **argv)
{
	if (verifyArguments(argc, argv))
		return (1);
	
	PmergeMe<size_t, std::vector>	vect;
	PmergeMe<double, std::deque>	dequ;
	PmergeMe<int, std::list>		list;

	initializePmergeMe(vect, argc, argv);
	initializePmergeMe(dequ, argc, argv);
	initializePmergeMe(list, argc, argv);

	displayData(vect);
	displayTime(vect, "std::vector");
	displayTime(dequ, "std::deque");
	displayTime(list, "std::list");

	return (0);
}
