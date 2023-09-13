/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MergeVector.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:58:08 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 21:22:51 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "APmergeMe.hpp"

#include <sstream>
#include <vector>

template <typename T>
class    MergeVector: public APmergeMe<T>
{
    private:
        /* Attributs */
		std::vector<T>					_data;
		std::vector<T>					_sorted;
		std::vector<std::pair<T, T> >	_pairs;
		std::vector<std::pair<T, T> >	_pendElements;

        /* Constructors & Destructors */
        MergeVector(void);

        /* Member functions */

    protected:
        /* Attributs */

        /* Constructors & Destructors */

        /* Member functions */

		void	toSortedPairs(void);

		void	sortMainChain(unsigned long int low, unsigned long int high);
		void	mergeMainChain(unsigned long int low, unsigned long int middle,
					unsigned long int high);
		void	insertPendElements(void);

    public:
        /* Attributs */

        /* Constructors & Destructors */
		MergeVector(const std::string &values);

        MergeVector(const MergeVector &other);
        MergeVector    &operator=(const MergeVector &other);

        ~MergeVector(void);

        /* Member functions */
		void	fordJohnsonSort(void);
};

#include "MergeVector.tpp"
