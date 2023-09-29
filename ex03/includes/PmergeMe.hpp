/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 01:34:04 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/18 03:45:36 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "debug.hpp"
#include "colors.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

#include <vector>
#include <deque>
#include <list>

template <typename T, template <typename, typename> class Container>
class	PmergeMe
{
	private:

		typedef std::allocator<T>					Alloc;
		typedef std::allocator<std::pair<T, T> >	PairAlloc;

		typedef struct straggler
		{
			Container<std::pair<T, T>, PairAlloc>	pairs;
			bool									hasStraggler;
			T										stragglerValue;
		} t_pairedData;

		typedef typename Container<T, Alloc>::iterator							Iterator;
		typedef typename Container<T, Alloc>::const_iterator					ConstIterator;
		typedef typename Container<std::pair<T, T>, PairAlloc>::iterator		PairsIterator;
		typedef typename Container<std::pair<T, T>, PairAlloc>::const_iterator	ConstPairsIterator;

		/* Attributs */
		Container<T, Alloc>		_unsortedData;
		Container<T, Alloc>		_sortedData;

		clock_t					_startTime;
		clock_t					_endTime;

		/* Constructors & Destructors */

		/* Member functions */

		void		startTimer(void);
		void		stopTimer(void);

		// Ford-Johnson algorythm

		void				recursivePairsTraversal(Container<T, Alloc> &container);

		t_pairedData		createPairedData(Container<T, Alloc> &container);
		Container<T, Alloc>	createPendingData(t_pairedData &pairedData);

		Iterator			higherboundBinarySearch(Container<T, Alloc> &container, const T &target);


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
