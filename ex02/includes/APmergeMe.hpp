/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   APmergeMe.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:17:28 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/14 13:35:37 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "Colors.hpp"

#include <iostream>
#include <string>
#include <ctime>

template <typename T>
class    APmergeMe
{
    private:
        /* Attributs */

        /* Constructors & Destructors */

        /* Member functions */

    protected:
		struct straggler
		{
			bool	has;
			T		value;
		};

        /* Attributs */
		clock_t		_startTime;
		clock_t		_endTime;
		
		straggler	_straggler;

        /* Constructors & Destructors */
		APmergeMe(void);

		APmergeMe(const APmergeMe &other);
		APmergeMe    &operator=(const APmergeMe &other);
		
        /* Member functions */
		void						startTimer(void);
		void						stopTimer(void);
		double						getElapsedTime(void) const;
	
		virtual void				toSortedPairs(void) = 0;

		unsigned long int			jacobsthal(unsigned long int n) const;

    public:
        /* Attributs */

        /* Constructors & Destructors */

		virtual ~APmergeMe(void);

        /* Member functions */
		
		virtual void				fordJohnsonSort(void) = 0;
};

#include "APmergeMe.tpp"
