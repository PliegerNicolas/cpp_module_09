/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 01:34:04 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/16 02:40:33 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "debug.hpp"
#include "colors.hpp"

#include <iostream>
#include <string>
#include <cstddef>

#include <vector>
#include <deque>
#include <list>

template <typename T, template <typename,
	typename> class Container, typename Alloc = std::allocator<T> >
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
};

#include "PmergeMe.tpp"
