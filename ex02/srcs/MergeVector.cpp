/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MergeVector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:02:59 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 17:07:45 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "MergeVector.hpp"

/* Constructors & Destructors */

// Public

MergeVector::MergeVector(const std::string &values):
	APmergeMe()
{
	std::cout << CYAN;
	std::cout << "MergeVector : constructor with values parameter called";
	std::cout << WHITE << std::endl;

	std::istringstream	iss(values);
	unsigned long int	nbr;

	while (iss >> nbr)
		_data.push_back(nbr);
}

MergeVector::MergeVector(const MergeVector &other):
	APmergeMe(other)
{
	std::cout << CYAN;
	std::cout << "MergeVector : copy constructor called";
	std::cout << WHITE << std::endl;
}

MergeVector	&MergeVector::operator=(const MergeVector &other)
{
	std::cout << CYAN;
	std::cout << "MergeVector : assignment operator called";
	std::cout << WHITE << std::endl;

	if (this != &other)
	{
		APmergeMe::operator=(other);
	}
	return (*this);
}

MergeVector::~MergeVector(void)
{
	std::cout << CYAN;
	std::cout << "MergeVector : default destructor called";
	std::cout << WHITE << std::endl;
}

// Protected

// Private

MergeVector::MergeVector(void):
	APmergeMe()
{
	std::cout << CYAN;
	std::cout << "MergeVector : default constructor called";
	std::cout << WHITE << std::endl;
}

