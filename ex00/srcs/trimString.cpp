/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimString.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:55:03 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/06 13:57:04 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "utils.hpp"

void	trimString(std::string &str)
{
	size_t	pos;

	pos = str.find_first_not_of(" \t\n\r");
	if (pos != std::string::npos)
		str.erase(0, pos);
	pos = str.find_last_not_of(" \t\n\r");
	if (pos != std::string::npos)
		str.erase(pos + 1);
}
