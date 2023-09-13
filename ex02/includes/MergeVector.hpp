/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MergeVector.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:58:08 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 18:55:34 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "APmergeMe.hpp"

#include <sstream>
#include <vector>

template <typename T>
class    MergeVector: public APmergeMe<T>
{
    private:
        /* Attributs */
		std::vector<T>					_data;
		std::vector<std::pair<T, T> >	_pairs;

        /* Constructors & Destructors */
        MergeVector(void);

        /* Member functions */

    protected:
        /* Attributs */

        /* Constructors & Destructors */

        /* Member functions */

		void	toPairs(void);
		void	sortPairs(void);

    public:
        /* Attributs */

        /* Constructors & Destructors */
		MergeVector(const std::string &values);

        MergeVector(const MergeVector &other);
        MergeVector    &operator=(const MergeVector &other);

        ~MergeVector(void);

        /* Member functions */
};

#include "MergeVector.tpp"
