/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:37:15 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/20 16:45:36 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main (int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Please enter an inverted Polish expression\n";
		return 1;
	}
	try
	{
		hsilop(argv[1]);
	}
	catch (RPNException & e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
