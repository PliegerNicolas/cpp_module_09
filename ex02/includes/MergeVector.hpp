/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MergeVector.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:58:08 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/15 01:13:44 by nicolas          ###   ########.fr       */
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
		
		std::vector<std::pair<T, T> >	_pairs;

		std::vector<T>					_sorted;
		std::vector<T>					_pendingElements;

		std::vector<T>					_jacobsthalSequence;

		/* Constructors & Destructors */

		/* Member functions */

		// Getter
		
		// Setter

		// Other

		void				toSortedPairs(void);

		void				mergeSort(size_t begin, size_t end);
		void				merge(size_t begin, size_t middle, size_t end);
		void				generateSortedAndPending(void);

		void				insertPendingElements(void);
		void				generateJacobsthalSequence(void);
		size_t				lowerboundBinarySearch(const std::vector<T> &arr, const T &target);

    protected:
		/* Attributs */

		/* Constructors & Destructors */

		/* Member functions */

    public:
		/* Attributs */

		/* Constructors & Destructors */
		MergeVector(void);
		MergeVector(const std::string &values);
		MergeVector(const size_t &argc, char **argv);

		MergeVector(const MergeVector &other);
		MergeVector    &operator=(const MergeVector &other);

		~MergeVector(void);

		/* Member functions */

		// Getter
		const std::vector<T>	&getData(void) const;
		const std::vector<T>	&getSorted(void) const;
		size_t					getDataSize(void) const;

		// Setter
		void					setData(const std::string &values);
		void					setData(const size_t &argc, char **argv);

		// Other
		const std::string		printVector(const std::vector<T> &vector) const;
		void					fordJohnsonSort(void);
};

#include "MergeVector.tpp"
