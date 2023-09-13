/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   APmergeMe.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:17:28 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 10:55:51 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "Colors.hpp"

#include <iostream>

template <typename Container>
class    APmergeMe
{
    private:
        /* Attributs */

        /* Constructors & Destructors */

        /* Member functions */

    protected:
        /* Attributs */

        /* Constructors & Destructors */

        /* Member functions */

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
