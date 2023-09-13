/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MergeDeque.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:58:08 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 20:35:21 by nicolas          ###   ########.fr       */
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
		std::deque<std::pair<T, T> >	_mainChain;
		std::deque<std::pair<T, T> >	_pendElements;

        /* Constructors & Destructors */
        
		MergeDeque(void);

        /* Member functions */

    protected:
        /* Attributs */

        /* Constructors & Destructors */

        /* Member functions */

		void	toSortedPairs(void);

    public:
        /* Attributs */

        /* Constructors & Destructors */
        MergeDeque(const std::string &values);

        MergeDeque(const MergeDeque &other);
        MergeDeque    &operator=(const MergeDeque &other);

        ~MergeDeque(void);

        /* Member functions */
		void	fordJohnsonSort(void);
};

#include "MergeDeque.tpp"
