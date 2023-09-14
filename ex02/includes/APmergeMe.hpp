/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   APmergeMe.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:17:28 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/14 23:05:51 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "debug.hpp"
#include "Colors.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>

template <typename T>
class    APmergeMe
{
	private:
		/* struct */
		struct straggler
		{
			bool	has;
			T		value;
		};

		/* Attributs */
		clock_t		_startTime;
		clock_t		_endTime;

		/* Constructors & Destructors */

		/* Member functions */

	protected:
		/* Attributs */
		straggler	_straggler;

		/* Constructors & Destructors */
		APmergeMe(void);

		APmergeMe(const APmergeMe &other);
		APmergeMe    &operator=(const APmergeMe &other);
		
		/* Member functions */
		void						startTimer(void);
		void						stopTimer(void);
	
		size_t						getJacobsthalValue(size_t n) const;

		virtual void				toSortedPairs(void) = 0;

		virtual void				mergeSort(size_t begin, size_t end) = 0;
		virtual void				merge(size_t begin, size_t middle, size_t end) = 0;
		virtual void				generateSortedAndPending(void) = 0;

		virtual void				insertPendingElements(void) = 0;
		virtual void				generateJacobsthalSequence(void) = 0;

	public:
		/* Attributs */

		/* Constructors & Destructors */

		virtual ~APmergeMe(void);

		/* Member functions */
		
		double						getElapsedTime(void) const;

		virtual void				fordJohnsonSort(void) = 0;
};

#include "APmergeMe.tpp"
