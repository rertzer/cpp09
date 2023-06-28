/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeL.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:43:21 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/28 15:15:58 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMeL.hpp"

// public

PmergeMeL::PmergeMeL()
{}

PmergeMeL::PmergeMeL(NbList const & mm):merge_me(mm)
{}

PmergeMeL::PmergeMeL(PmergeMeL const & rhs)
{
	*this = rhs;
}

PmergeMeL::~PmergeMeL()
{}

PmergeMeL &	PmergeMeL::operator=(PmergeMeL const & rhs)
{
	if (this != &rhs)
	{
		merge_me = rhs.merge_me;
		halfbig = rhs.halfbig;
		remain = rhs.remain;
		pairing = rhs.pairing;
	}
	return *this;
}

void	PmergeMeL::fjSort()
{
	if (merge_me.getLen() == 1)
		return ;

	pairSwap();
	splitMe();

	PmergeMeL big_sorting = PmergeMeL(halfbig);
	big_sorting.fjSort();
	halfbig = big_sorting.getMergeMeL();

	reload();
	reinsert();
}

NbList & PmergeMeL::getMergeMeL()
{
	return merge_me;
}

// private
void	PmergeMeL::pairSwap()
{
	for (unsigned int i = 0; i < merge_me.getLen() - 1; i += 2)
	{
		if (merge_me[i] < merge_me[i + 1])
		{
			Number tmp = merge_me[i];
			merge_me[i] = merge_me[i + 1];
			merge_me[i + 1] = tmp;
		}
	}
}

void	PmergeMeL::splitMe()
{
	unsigned int i = 0;	
	Number	pr = Number();

	for (; i < merge_me.getLen() - 1; i += 2)
	{
		pr.setValue(merge_me[i + 1].getIndex());
		pr.setIndex(merge_me[i].getIndex());
		pairing.push(pr);
		halfbig.push(merge_me[i]);
		remain.push(merge_me[i + 1]);
	}
	if (merge_me.getLen() % 2)
	{
		pr.setValue(merge_me[i].getIndex());
		pr.setIndex(-1);
		pairing.push(pr);
		remain.push(merge_me[i]);
	}
}

void	PmergeMeL::reload()
{
	unsigned int	index;	
	Number			to_insert = Number();

	merge_me.clear();

	index = halfbig.getList().front().getIndex();
	index = pairing.getByIndex(index).getValue();

	to_insert = remain.getByIndex(index);
	merge_me.push(to_insert);
	for (unsigned int i = 0; i < halfbig.getLen(); i++)
		merge_me.push(halfbig[i]);
}

void	PmergeMeL::reinsert()
{
	getOrder();
	
	for (std::list<unsigned int>::iterator it = the_order.begin(); it != the_order.end(); it++)
	{
		unsigned int	index;
		unsigned int	end;

		if (*it < halfbig.getLen())
		{
			index = halfbig[*it].getIndex();
			end = merge_me.getBigPosByIndex(index);
		}
		else
		{
			index = -1;
			end = merge_me.getLen() - 1;
		}
		index = pairing.getByIndex(index).getValue();
		binaryInsert(remain.getByIndex(index), end);
	}
}

void	PmergeMeL::getOrder()
{
	unsigned int	group = 1;
	unsigned int	current = 2;
	unsigned int	g = 0;

	while (group)
	{
		g = nextGroupSize(g, group);
		unsigned int maxi = std::min(current + g, remain.getLen() + 1);
		if (current + g > remain.getLen())
			group = -1;
		for (unsigned int i = maxi; i > current; i--)
			the_order.push_back(i - 2);
		current += g;
		group++;
	}
}

unsigned int	PmergeMeL::nextGroupSize(unsigned int g, unsigned int group)
{
	unsigned int	gs = 1;
	
	for (unsigned int i = 0; i < group; i++)
		gs *= 2;

	return (gs - g); 
}

void	PmergeMeL::binaryInsert(Number r, long int right)
{
	long int							left = 0;
	long int							pos;
	std::list<Number>::iterator		it = merge_me.getList().begin();
	
	while (1)
	{
		if (right - left == 1)
		{
			if (r < merge_me[left])
				pos = left - 1;
			else if (merge_me[right] < r)
				pos = right;
			else
				pos = left;
			break ;
		}

		pos = (left + right) / 2;

		if (merge_me[pos] < r)
		{
			if (pos == merge_me.getLen() - 1 || pos == left)
				break ;
			left = pos;
		}
		else if (r < merge_me[pos])
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
	for (long int i = 0; i < pos + 1; i++)
		it++;

	merge_me.getList().insert(it, r);
	merge_me.increase();
}
