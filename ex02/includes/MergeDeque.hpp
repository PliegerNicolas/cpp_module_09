/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MergeDeque.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:58:08 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 18:55:29 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "APmergeMe.hpp"

#include <sstream>
#include <deque>

template <typename T>
class    MergeDeque: public APmergeMe<T>
{
    private:
        /* Attributs */
		std::deque<T>					_data;
		std::deque<std::pair<T, T> >	_pairs;

        /* Constructors & Destructors */
        
		MergeDeque(void);

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
        MergeDeque(const std::string &values);

        MergeDeque(const MergeDeque &other);
        MergeDeque    &operator=(const MergeDeque &other);

        ~MergeDeque(void);

        /* Member functions */
};

#include "MergeDeque.tpp"
