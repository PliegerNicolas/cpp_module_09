/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   APmergeMe.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:17:28 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 11:35:46 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "Colors.hpp"

#include <iostream>
#include <ctime>

template <typename Container>
class    APmergeMe
{
    private:
        /* Attributs */
		clock_t	_startTime;

        /* Constructors & Destructors */

        /* Member functions */

    protected:
        /* Attributs */

		clock_t	_elapsedTime;

        /* Constructors & Destructors */
		void	setStartTime(void);
		clock_t	getStartTime(void) const;

        /* Member functions */
		void	startTimer(void);
		clock_t	getElapsedTime(void) const;

    public:
        /* Attributs */

        /* Constructors & Destructors */


		APmergeMe(void);

		APmergeMe(const APmergeMe &other);
		APmergeMe    &operator=(const APmergeMe &other);

		virtual ~APmergeMe(void);

        /* Member functions */
};

#include "APmergeMe.tpp"
