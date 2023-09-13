/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MergeVector.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:58:08 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 10:59:38 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "APmergeMe.hpp"
#include <vector>

class    MergeVector: public APmergeMe<unsigned long int>
{
    private:
        /* Attributs */
		std::vector<unsigned long int>	_data;

        /* Constructors & Destructors */

        /* Member functions */

    protected:
        /* Attributs */

        /* Constructors & Destructors */

        /* Member functions */

    public:
        /* Attributs */

        /* Constructors & Destructors */
        MergeVector(void);

        MergeVector(const MergeVector &other);
        MergeVector    &operator=(const MergeVector &other);

        ~MergeVector(void);

        /* Member functions */
};

