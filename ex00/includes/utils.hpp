/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:27:18 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/06 13:57:12 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include <iostream>
#include <string>
#include <sstream>

void	isValidDate(const std::string &date, const char separator);
void	isValidDouble(const std::string &str);
void	trimString(std::string &str);
