/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   APmergeMe.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:17:28 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 16:55:22 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "Colors.hpp"

#include <iostream>
#include <string>
#include <ctime>

template <typename Container>
class    APmergeMe
{
    private:
        /* Attributs */
		clock_t		_startTime;
		clock_t		_elapsedTime;

        /* Constructors & Destructors */

        /* Member functions */

    protected:
        /* Attributs */

        /* Constructors & Destructors */
		APmergeMe(void);

		APmergeMe(const APmergeMe &other);
		APmergeMe    &operator=(const APmergeMe &other);
		
        /* Member functions */
		void		startTimer(void);
		void		stopTimer(void);
		double		getElapsedTime(void) const;

    public:
        /* Attributs */

        /* Constructors & Destructors */

		virtual ~APmergeMe(void);

        /* Member functions */
};

#include "APmergeMe.tpp"
