/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:43:21 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/22 16:47:18 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void	fjSort(NbVector & to_sort)
{
	NbVector	halfbig = NbVector();
	NbVector	remain = NbVector();
	NbVector	pairing = NbVector();

	if (to_sort.getLen() == 1)
		return ;

	pairSwap(to_sort);
	splitMe(to_sort, halfbig, remain, pairing);
	fjSort(halfbig);
	reload(to_sort, remain, halfbig, pairing);
	reinsert(to_sort, halfbig, remain, pairing);
}

void	pairSwap(NbVector & to_sort)
{
	for (unsigned int i = 0; i < to_sort.getLen() - 1; i += 2)
	{
		if (to_sort[i] < to_sort[i + 1])
		{
			Number tmp = to_sort[i];
			to_sort[i] = to_sort[i + 1];
			to_sort[i + 1] = tmp;
		}
	}
}

void	splitMe(NbVector & to_sort, NbVector & halfbig, NbVector & remain, NbVector & pairing)
{
	unsigned int i = 0;	
	Number	pr = Number();

	for (; i < to_sort.getLen() - 1; i += 2)
	{
		pr.setValue(to_sort[i + 1].getIndex());
		pr.setIndex(to_sort[i].getIndex());
		pairing.push(pr);
		halfbig.push(to_sort[i]);
		remain.push(to_sort[i + 1]);
	}
	if (to_sort.getLen() % 2)
	{
		pr.setValue(to_sort[i].getIndex());
		pr.setIndex(-1);
		pairing.push(pr);
		remain.push(to_sort[i]);
	}
}

void	reload(NbVector & to_sort, NbVector & remain, NbVector & halfbig, NbVector & pairing)
{
	unsigned int	index;	
	Number			to_insert = Number();

	to_sort.clear();

	index = halfbig.getVector().front().getIndex();
	index = pairing.getByIndex(index).getValue();

	to_insert = remain.getByIndex(index);
	to_sort.push(to_insert);
	for (unsigned int i = 0; i < halfbig.getLen(); i++)
		to_sort.push(halfbig[i]);
}

void	reinsert(NbVector & to_sort, NbVector & halfbig, NbVector & remain, NbVector & pairing)
{
	std::vector<unsigned int> the_order;
	
	getOrder(the_order, remain.getLen()); // size_t vs uint
	
	for (size_t i = 0; i < the_order.size(); i++)
	{
		unsigned int	index;
		if (the_order[i] < halfbig.getLen())
			index = halfbig[the_order[i]].getIndex();
		else
			index = -1;

		index = pairing.getByIndex(index).getValue();
		binaryInsert(to_sort, remain.getByIndex(index));
	}
}

void	getOrder(std::vector<unsigned int> & the_order, unsigned int len)
{
	unsigned int	group = 1;
	unsigned int	current = 2;
	unsigned int	g = 0;

	while (group)
	{
		g = nextGroupSize(g, group);
		unsigned int maxi = std::min(current + g, len + 1);
		if (current + g > len)
			group = -1;
		for (unsigned int i = maxi; i > current; i--)
			the_order.push_back(i - 2);
		current += g;
		group++;
	}
}

unsigned int	nextGroupSize(unsigned int g, unsigned int group)
{
	unsigned int	gs = 1;
	
	for (unsigned int i = 0; i < group; i++)
		gs *= 2;

	return (gs - g); 
}

void	binaryInsert(NbVector & to_sort, Number r)
{
	long int						left = 0;
	long int						right = to_sort.getLen();
	long int						pos;
	std::vector<Number>::iterator		it = to_sort.getVector().begin();
	
	while (1)
	{
		pos = (left + right) / 2;

		if (to_sort[pos] < r)
		{
			if (pos == to_sort.getLen() - 1 || pos == left)
				break ;
			left = pos;
		}
		else if (r < to_sort[pos])
		{
			if (pos == 0)
			{
				pos = -1;
				break;
			}
			if (pos == right)
				break;
			right = pos;
		}
		else
			break ;
	}
	to_sort.getVector().insert(it + pos + 1, r);
	to_sort.increase();
}
