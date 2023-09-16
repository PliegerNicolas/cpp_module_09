/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:15:58 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/16 19:41:33 by nicolas          ###   ########.fr       */
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
static void	displayResults(Container &container, const std::string &containerType)
{
	std::cout << YELLOW << containerType << WHITE << std::endl;
	std::cout << YELLOW << "{" << WHITE << std::endl;

	std::cout << CYAN;
	std::cout << "	Before:  " << WHITE << container.printUnsortedData();
	std::cout << std::endl;
	std::cout << CYAN;
	std::cout << "	After:   " << WHITE << container.printSortedData();
	std::cout << std::endl;

	std::cout << CYAN << "	Time to process a range of ";
	std::cout << WHITE << std::setw(5) << container.getUnsortedData().size();
	std::cout << CYAN << " elements with ";
	std::cout << WHITE << containerType << CYAN << " : " << WHITE;
	std::cout << std::setprecision(8) << container.getElapsedTime() << " ms";
	std::cout << CYAN << "." << WHITE << std::endl;

	std::cout << YELLOW << "}" << WHITE << std::endl;
}

template <typename Container>
static void	execPmergeMe(Container &container, const int &argc, char **argv, const std::string &containerType)
{
	try
	{
		if (argc > 1)
			container.setUnsortedData(argc, argv);
		else
			container.setUnsortedData(argv[1]);
		container.fordJohnsonSort();
		displayResults(container, containerType);
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

	execPmergeMe(vect, argc, argv, "std::vector");
	std::cout << std::endl;
	execPmergeMe(dequ, argc, argv, "std::deque");
	std::cout << std::endl;
	execPmergeMe(list, argc, argv, "std::list");

	return (0);
}
