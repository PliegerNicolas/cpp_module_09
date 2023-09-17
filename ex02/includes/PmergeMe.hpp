/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 01:34:04 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/17 20:56:35 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "debug.hpp"
#include "colors.hpp"

#include <iostream>
#include <string>
#include <cstddef>
#include <sstream>
#include <ctime>

#include <vector>
#include <deque>
#include <list>

template <typename T, template <typename, typename> class Container>
class    PmergeMe
{
	private:
		/* struct */
		struct straggler
		{
			bool	has;
			T		value;
		};

		typedef std::allocator<T>												Alloc;
		typedef std::allocator<std::pair<T, T> >								PairAlloc;

		typedef typename Container<T, Alloc>::iterator							Iterator;
		typedef typename Container<T, Alloc>::const_iterator					ConstIterator;
		typedef typename Container<std::pair<T, T>, PairAlloc>::iterator		PairIterator;
		typedef typename Container<std::pair<T, T>, PairAlloc>::const_iterator	ConstPairIterator;

		/* Attributs */
		Container<T, Alloc>						_unsortedData;
		Container<T, Alloc>						_sortedData;

		Container<std::pair<T, T>, PairAlloc>	_pairedData;
		Container<T, Alloc>						_pendingData;

		clock_t									_startTime;
		clock_t									_endTime;
		straggler								_straggler;

		/* Constructors & Destructors */

		/* Member functions */

		void		startTimer(void);
		void		stopTimer(void);

		// Ford-Johnson algorythm
		// Step 1
		void		generatePairs(void);
		// Step 2
		void		sortPairs(void);
		// Step 3
		void		mergeSort(PairIterator begin, PairIterator end);
		void		merge(PairIterator begin, PairIterator middle, PairIterator end);
		// Step 4
		void		splitPairs(void);
		// Step 5
		void		insertPendingData(void);
		Iterator	higherboundBinarySearch(Container<T, Alloc> &container, const T &target);

	protected:
		/* Attributs */

		/* Constructors & Destructors */

		/* Member functions */

	public:
		/* Attributs */

		/* Constructors & Destructors */
		PmergeMe(void);

		PmergeMe(const PmergeMe &other);
		PmergeMe    &operator=(const PmergeMe &other);

		~PmergeMe(void);

		/* Member functions */

		// ::Getters
		const Container<T, Alloc>	&getUnsortedData(void) const;
		const Container<T, Alloc>	&getSortedData(void) const;
		double						getElapsedTime(void) const;

		// ::Setters
		void						setUnsortedData(const std::string &str);
		void						setUnsortedData(const int &argc, char **argv);

		// :Other

		const std::string			printUnsortedData(void) const;
		const std::string			printSortedData(void) const;
		void						fordJohnsonSort(void);
};

#include "PmergeMe.tpp"
