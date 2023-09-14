/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MergeDeque.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:58:08 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/14 23:34:44 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "APmergeMe.hpp"

#include <sstream>
#include <deque>

template <typename T>
class    MergeDeque: public APmergeMe<T>
{
    private:
		/* Attributs */
		std::deque<T>					_data;
		
		std::deque<std::pair<T, T> >	_pairs;

		std::deque<T>					_sorted;
		std::deque<T>					_pendingElements;

		std::deque<T>					_jacobsthalSequence;

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
		size_t				lowerboundBinarySearch(const std::deque<T> &arr, const T &target);

    protected:
		/* Attributs */

		/* Constructors & Destructors */

		/* Member functions */

    public:
		/* Attributs */

		/* Constructors & Destructors */
		MergeDeque(void);
		MergeDeque(const std::string &values);
		MergeDeque(const size_t &argc, char **argv);

		MergeDeque(const MergeDeque &other);
		MergeDeque    &operator=(const MergeDeque &other);

		~MergeDeque(void);

		/* Member functions */

		// Getter
		const std::deque<T>	&getData(void) const;
		const std::deque<T>	&getSorted(void) const;
		size_t				getDataSize(void) const;

		// Setter
		void				setData(const std::string &values);
		void				setData(const size_t &argc, char **argv);

		// Other
		const std::string	printDeque(const std::deque<T> &deque) const;
		void				fordJohnsonSort(void);
};

#include "MergeDeque.tpp"
