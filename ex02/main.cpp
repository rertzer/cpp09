/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:14:07 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/24 10:44:48 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Please enter a list of positive numbers as arguments\n";
		return (1);
	}

	struct timeval	begin, end;
	gettimeofday(&begin, 0);
	try
	{
		NbVector	to_sort = NbVector();
		to_sort.loadData(argc, argv);
		PmergeMe	pm	= PmergeMe(to_sort);
		std::cout << "Before: " << pm.getMergeMe() << std::endl;
		pm.fjSort();
		std::cout << "After: " << pm.getMergeMe() << std::endl;
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
	gettimeofday(&end, 0);
	long	sec = end.tv_sec - begin.tv_sec;
	long	msec = end.tv_usec - begin.tv_usec;
	double	timer = sec * 1e3 + sec * 1e-3;
	std::cout << "time to process : " << timer <<  " " << msec << std::endl;

	return (0);
}
