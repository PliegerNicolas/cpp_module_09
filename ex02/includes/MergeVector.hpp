/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MergeVector.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:58:08 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/14 19:54:55 by nicolas          ###   ########.fr       */
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
		std::vector<T>					_pendingElements;

		std::vector<std::pair<T, T> >	_pairs;

        /* Constructors & Destructors */
        MergeVector(void);

        /* Member functions */

    protected:
        /* Attributs */

        /* Constructors & Destructors */

        /* Member functions */

		void	toSortedPairs(void);
		void	separatePairs(void);

		void	mergeSort(size_t begin, size_t end);
		void	merge(size_t begin, size_t middle, size_t end);
		void	generateSortedAndPending(void);

		size_t	lowerboundBinarySearch(const std::vector<T> &arr, const T &target);

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
