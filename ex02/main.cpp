/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:14:07 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/28 15:36:44 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "PmergeMe.hpp"
#include "PmergeMeL.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Please enter a list of positive numbers as arguments\n";
		return (1);
	}

	struct timeval	begin, end;
	unsigned int	nbelem = 0;

	// Vector version
	gettimeofday(&begin, 0);
	try
	{
		NbVector	to_sort = NbVector();
		to_sort.loadData(argc, argv);
		nbelem = to_sort.getLen();
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
	double	timer = sec * 1e6 + msec;
	std::cout << "time to process a range of : " << nbelem << " with std::vector : " << timer <<  " us" << std::endl;

	//List version
	gettimeofday(&begin, 0);
	try
	{
		NbList	to_sort = NbList();
		to_sort.loadData(argc, argv);
		PmergeMeL	pm	= PmergeMeL(to_sort);
		std::cout << "Before: " << pm.getMergeMeL() << std::endl;
		pm.fjSort();
		std::cout << "After: " << pm.getMergeMeL() << std::endl;
	}
	catch (NbList::ParsingException & e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	catch (NbList::OutOfRangeException & e)
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
	sec = end.tv_sec - begin.tv_sec;
	msec = end.tv_usec - begin.tv_usec;
	timer = sec * 1e6 + msec;
	std::cout << "time to process a range of : " << nbelem << " with std::list : " << timer <<  " us" << std::endl;

	return (0);
}
