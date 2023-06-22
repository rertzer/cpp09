/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:14:07 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/21 15:01:28 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Please enter a list of positive numbers as arguments\n";
		return (1);
	}
	NbVector	to_sort = NbVector();
	try
	{
		to_sort.loadData(argc, argv);
	}
	catch (NbVector::ParsingException & e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	std::cout << "Before: " << to_sort << std::endl;
	fjSort(to_sort);


	return (0);
}
