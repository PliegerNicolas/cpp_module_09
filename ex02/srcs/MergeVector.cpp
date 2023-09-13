/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MergeVector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:02:59 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 11:03:05 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "MergeVector.hpp"

/* Constructors & Destructors */

// Public

MergeVector::MergeVector(void):
	APmergeMe()
{
	std::cout << CYAN;
	std::cout << "MergeVector : default constructor called";
	std::cout << WHITE << std::endl;
}

MergeVector::MergeVector(const MergeVector &other):
	APmergeMe()
{
	std::cout << CYAN;
	std::cout << "MergeVector : copy constructor called";
	std::cout << WHITE << std::endl;

	(void)other;
}

MergeVector	&MergeVector::operator=(const MergeVector &other)
{
	std::cout << CYAN;
	std::cout << "MergeVector : assignment operator called";
	std::cout << WHITE << std::endl;

	if (this != &other)
	{
		(void)other;
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