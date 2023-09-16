/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 01:34:04 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/16 12:37:29 by nicolas          ###   ########.fr       */
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

template <typename T, template <typename, typename> class Container,
	typename Alloc = std::allocator<T> >
class    PmergeMe
{
	private:
		/* struct */
		struct straggler
		{
			bool	has;
			T		value;
		};

		/* Attributs */
		Container<T, Alloc>					_unsortedData;
		Container<T, Alloc>					_sortedData;

		Container<std::pair<T, T>, Alloc>	_pairedData;
		Container<T, Alloc>					_pendingData;
		Container<size_t, Alloc>			_jacobsthalSequence;

		clock_t								_startTime;
		clock_t								_endTime;
		straggler							_straggler;

		/* Constructors & Destructors */

		/* Member functions */

		void						startTimer(void);
		void						stopTimer(void);

		// Step 1
		void						generatePairs(void);
		void						sortPairs(void);

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
