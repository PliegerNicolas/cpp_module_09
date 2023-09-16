/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:15:58 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/16 12:20:40 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "PmergeMe.hpp"

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

template <typename T, template <typename, typename> class Container>
void	test(int argc, char **argv)
{
	PmergeMe<T, Container>	container;

	try
	{
		if (argc > 1)
			container.setUnsortedData(argc, argv);
		else
			container.setUnsortedData(*(argv + 1));

		container.fordJohnsonSort();
		std::cout << container.printUnsortedData() << std::endl;
		std::cout << container.printSortedData() << std::endl;
		std::cout << container.getElapsedTime() << "ms" << std::endl;
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

	test<size_t, std::vector>(argc, argv);
	test<double, std::deque>(argc, argv);
	test<int, std::list>(argc, argv);

	return (0);
}


















/*
template <typename T>
static void	displayResults(MergeVector<T> vect, MergeDeque<T> deque)
{
	std::cout << YELLOW << "std::vector" << WHITE << std::endl;
	std::cout << CYAN;
	std::cout << "Before:  " << WHITE << vect.printVector(vect.getData());
	std::cout << std::endl;
	std::cout << CYAN;
	std::cout << "After:   " << WHITE << vect.printVector(vect.getSorted());
	std::cout << std::endl;

	std::cout << YELLOW << "std::deque" << WHITE << std::endl;
	std::cout << CYAN;
	std::cout << "Before:  " << WHITE << deque.printDeque(deque.getData());
	std::cout << std::endl;
	std::cout << CYAN;
	std::cout << "After:   " << WHITE << deque.printDeque(deque.getSorted());
	std::cout << std::endl;

	std::cout << std::endl;

	std::cout << CYAN << "Time to process a range of ";
	std::cout << WHITE << std::setw(5) << vect.getDataSize();
	std::cout << CYAN << " elements with ";
	std::cout << WHITE << "std::vector" << CYAN << " : " << WHITE;
	std::cout << std::setprecision(8) << vect.getElapsedTime() << " ms";
	std::cout << CYAN << "." << WHITE << std::endl;

	std::cout << CYAN << "Time to process a range of ";
	std::cout << WHITE << std::setw(5) << deque.getDataSize();
	std::cout << CYAN << " elements with ";
	std::cout << WHITE << "std::deque" << CYAN << " : " << WHITE;
	std::cout << std::setprecision(8) << deque.getElapsedTime() << " ms";
	std::cout << CYAN << "." << WHITE << std::endl;
}
*/
