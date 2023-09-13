/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MergeDeque.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:03:08 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 17:07:56 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "MergeDeque.hpp"

/* Constructors & Destructors */

// Public

MergeDeque::MergeDeque(const std::string &values):
	APmergeMe()
{
	std::cout << CYAN;
	std::cout << "MergeDeque : constructor with values parameter called";
	std::cout << WHITE << std::endl;

	std::istringstream	iss(values);
	unsigned long int	nbr;

	while (iss >> nbr)
		_data.push_back(nbr);
}

MergeDeque::MergeDeque(const MergeDeque &other):
	APmergeMe(other)
{
	std::cout << CYAN;
	std::cout << "MergeDeque : copy constructor called";
	std::cout << WHITE << std::endl;
}

MergeDeque	&MergeDeque::operator=(const MergeDeque &other)
{
	std::cout << CYAN;
	std::cout << "MergeDeque : assignment operator called";
	std::cout << WHITE << std::endl;

	if (this != &other)
	{
		APmergeMe::operator=(other);
	}
	return (*this);
}

MergeDeque::~MergeDeque(void)
{
	std::cout << CYAN;
	std::cout << "MergeDeque : default destructor called";
	std::cout << WHITE << std::endl;
}

// Protected

// Private

MergeDeque::MergeDeque(void):
	APmergeMe()
{
	std::cout << CYAN;
	std::cout << "MergeDeque : default constructor called";
	std::cout << WHITE << std::endl;
}
