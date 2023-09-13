/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MergeDeque.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:58:08 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 17:08:11 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "APmergeMe.hpp"

#include <sstream>
#include <deque>

class    MergeDeque: public APmergeMe<unsigned long int>
{
    private:
        /* Attributs */
		std::deque<unsigned long int>   _data;
		std::deque<unsigned long int>   _pairs;

        /* Constructors & Destructors */
        
		MergeDeque(void);

        /* Member functions */

    protected:
        /* Attributs */

        /* Constructors & Destructors */

        /* Member functions */

    public:
        /* Attributs */

        /* Constructors & Destructors */
        MergeDeque(const std::string &values);

        MergeDeque(const MergeDeque &other);
        MergeDeque    &operator=(const MergeDeque &other);

        ~MergeDeque(void);

        /* Member functions */
};

