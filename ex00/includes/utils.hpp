/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 08:51:53 by nplieger          #+#    #+#             */
/*   Updated: 2023/09/05 13:42:15 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

# include <iostream>
# include <string>
# include <sstream>
# include <cstdlib>

std::string						&trim(std::string &str);
std::pair<std::string, double>	splitLine(const std::string &line);
