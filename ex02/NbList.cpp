/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NbList.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:28:27 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/26 13:12:08 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NbList.hpp"

NbList::NbList():len(0)
{}

NbList::NbList(std::list<Number> const & lst):nbs(lst), len(lst.size())
{}

NbList::NbList(NbList const & nbl):nbs(nbl.nbs), len(nbl.len)
{}

NbList::~NbList()
{}

NbList &	NbList::operator=(NbList const & rhs)
{
	if (this != &rhs)
	{
		nbs = rhs.nbs;
		len = rhs.len;
	}
	return *this;
}

Number &	NbList::operator[](unsigned int i)
{
	std::list<Number>::iterator it = nbs.begin();
	for (unsigned int j = 0; j < i; j++)
	{
		it++;
		if (it == nbs.end())
			throw (OutOfRangeException());
	}
	return *it;
}

void	NbList::loadData(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		std::stringstream	ss;
		Number				nb = Number();

		ss.exceptions(ss.failbit | ss.badbit);
		if (!std::isdigit(argv[i][0]))
			throw (ParsingException());
		ss << argv[i];
		unsigned int tmp;
		ss >> tmp;
		nb.setValue(tmp);;
		nb.setIndex((i - 1));
		nbs.push_back(nb);
		len++;
	}
}

void	NbList::clear()
{
	nbs.clear();
	len = 0;
}

void	NbList::push(Number nb)
{
	nbs.push_back(nb);
	len++;
}

void	NbList::increase()
{
	len++;
}

unsigned int	NbList::getLen()
{
	return len;
}

std::list<Number> &	NbList::getList()
{
	return nbs;
}

unsigned int	NbList::getBigPosByIndex(unsigned int index)
{
	unsigned int	i = 0;
	for (std::list<Number>::iterator it = nbs.begin(); it != nbs.end(); it++)
	{
		if (it->getIndex() == index)
			return (i);
		i++;
	}
	throw (OutOfRangeException());
}

Number &	NbList::getByIndex(unsigned int index)
{
	for (std::list<Number>::iterator it = nbs.begin(); it != nbs.end(); it++)
	{
		if (it->getIndex() == index)
			return (*it);
	}
	throw (OutOfRangeException());
}

std::ostream & operator<<(std::ostream & ost, NbList & rhs)
{
	for (unsigned int i = 0; i < rhs.getLen(); i++)
	{
		ost << rhs[i];
		if (i != rhs.getLen() - 1)
			ost << " ";
		else
			ost << std::endl;
	}
	return ost;
}
