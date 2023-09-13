/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MergeVector.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:58:08 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 17:06:07 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "APmergeMe.hpp"

#include <sstream>
#include <vector>

class    MergeVector: public APmergeMe<unsigned long int>
{
    private:
        /* Attributs */
		std::vector<unsigned long int>	_data;
		std::vector<unsigned long int>	_pairs;

        /* Constructors & Destructors */
        MergeVector(void);

        /* Member functions */

    protected:
        /* Attributs */

        /* Constructors & Destructors */

        /* Member functions */

    public:
        /* Attributs */

        /* Constructors & Destructors */
		MergeVector(const std::string &values);

        MergeVector(const MergeVector &other);
        MergeVector    &operator=(const MergeVector &other);

        ~MergeVector(void);

        /* Member functions */
};

