/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:43:21 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/21 17:22:33 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void	fjSort(NbVector & to_sort)
{
	NbVector	halfBig = NbVector();
	NbVector	remain = NbVector();

	if (to_sort.getLen() == 1)
		return ;

	pairSwap(to_sort);
	splitMe(to_sort, halfbig, remain);
	fjSort(halfbig);
	reload(to_sort, remain, halfbig);
	reinsert(to_sort, remain);
}

void	pairSwap(NbVector & to_sort)
{
	for (size_t i = 0; i < to_sort.getLen() - 1; i += 2)
	{
		if (to_sort[i] < to_sort[i + 1])
		{
			Number tmp = to_sort[i];
			to_sort[i] = to_sort[i + 1];
			to_sort[i + 1] = tmp;
		}
	}

void	splitMe(NbVector & to_sort, NbVector & halfbig, NbVector & remain)
{
	size_t i = 0;
	
	for (; i < to_sort.getLen() - 1; i += 2)
	{
		to_sort[i].setIndex = i;
		to_sort[i + 1].setIndex = i;
		halfbig.push(to_sort[i]);
		remain.push(to_sort[i + 1]);
	}
	if (to_sort.getLen() % 2)
	{
		to_sort[i].setIndex = i;
		remain.push(to_sort[i];
	}

}

void	reload(NbVector & to_sort, NbVector & remain, NbVector & halfbig)
{
	unsigned int	index;	
	Number			to_insert = Number();

	to_sort.getVector().clear();
	index = halfbig.getVector().front().getIndex();
	to_insert = remain.getByIndex(index);
	to_sort.push(to_insert);
	for (size_t i = 0; i < halfbig.len(); i++)
		to_sort.push(halfbig[i]);
}

void	reinsert(NbVector & to_sort, NbVector & remain)
{
	std::vector<unsigned int> the_order;
	getOrder(the_order, remain.len());
	for (size_t i = 0; i < len(the_order); i++)
		binaryInsert(to_sort, remain[the_order[i]]);
}

void	getOrder(std::vector<unsigned int> & the_order, size_t len)
{
	unsigned int	group = 1;
	unsigned int	current = 2;
	while (group)
	{
		unsigned int g = nextGroupSize(group);
		for (unsigned int i = current + g; i > current; i--)
		{
			if (i < len)
				the_order.push_back(i);
			else
				group = -1;
		}
		group++;
	}
}

