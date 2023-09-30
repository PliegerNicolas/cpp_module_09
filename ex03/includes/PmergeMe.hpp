/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 01:34:04 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/30 18:19:38 by nicolas          ###   ########.fr       */
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
#include <algorithm>

#include <vector>
#include <deque>
#include <list>

template <typename T, template <typename, typename> class C>
class	PmergeMe
{
	private:
		/* Typdefs */
		typedef std::allocator<T>								Alloc;
		typedef std::allocator<std::pair<T, T> >				PairAlloc;
		typedef std::allocator<size_t>							JacobsthalAlloc;
		typedef std::allocator<C<T, Alloc> >					GroupAlloc;

		typedef C<T, Alloc>										Container;
		typedef C<std::pair<T, T>, PairAlloc>					PairContainer;
		typedef C<size_t, JacobsthalAlloc>						JacobsthalContainer;
		typedef C<C<T, Alloc>, GroupAlloc >						GroupContainer;

		typedef typename Container::iterator					Iterator;
		typedef typename Container::const_iterator				ConstIterator;
		typedef typename PairContainer::iterator				PairIterator;
		typedef typename PairContainer::const_iterator			ConstPairIterator;
		typedef typename JacobsthalContainer::iterator			JacobIterator;
		typedef typename JacobsthalContainer::const_iterator	ConstJacobIterator;
		typedef typename GroupContainer::iterator				GroupIterator;
		typedef typename GroupContainer::const_iterator			ConstGroupIterator;


		typedef struct pairedData
		{
			PairContainer	pairs;
			bool			hasStraggler;
			T				straggler;
		}	t_pairedData;

		/* Attributs */
		Container	_unsortedData;
		Container	_sortedData;

		clock_t		_startTime;
		clock_t		_endTime;

		/* Constructors & Destructors */

		/* Member functions */

		void				startTimer(void);
		void				stopTimer(void);

		// Ford-Johnson algorythm
		t_pairedData		generateOrderedPairs(const Container &container);

		Container			recursivePairSort(t_pairedData &pairedData);
		void				mergeSort(PairIterator begin, PairIterator end);
		void				merge(PairIterator begin, PairIterator middle, PairIterator end);

		void				insertPendingElements(Container &pendingElements);
		GroupContainer		generateInsertionGroups(const Container &pendingElements);
		JacobsthalContainer	generateJacobsthalSequence(const size_t size);

	protected:
		/* Attributs */

		/* Constructors & Destructors */

		/* Member functions */

	public:
		/* Attributs */

		/* Constructors & Destructors */
		PmergeMe(void);
		PmergeMe(const std::string &str);
		PmergeMe(const int &argc, char **argv);

		PmergeMe(const PmergeMe &other);
		PmergeMe	&operator=(const PmergeMe &other);

		~PmergeMe(void);

		/* Member functions */

		// ::Getters
		const Container		&getUnsortedData(void) const;
		const Container		&getSortedData(void) const;
		double				getElapsedTime(void) const;

		// ::Setters
		void				setUnsortedData(const std::string &str);
		void				setUnsortedData(const int &argc, char **argv);

		// :Other

		const std::string	printUnsortedData(void) const;
		const std::string	printSortedData(void) const;
		void				fordJohnsonSort(void);
};

#include "PmergeMe.tpp"
