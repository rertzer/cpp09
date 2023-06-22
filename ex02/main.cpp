/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:14:07 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/22 12:45:45 by rertzer          ###   ########.fr       */
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

	try
	{
		NbVector	to_sort = NbVector();
		to_sort.loadData(argc, argv);
		std::cout << "Before: " << to_sort << std::endl;
		fjSort(to_sort);
		std::cout << "After: " << to_sort << std::endl;
	}
	catch (NbVector::ParsingException & e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	catch (NbVector::OutOfRangeException & e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}

	return (0);
}
