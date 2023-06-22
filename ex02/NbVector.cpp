/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NbVector.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:28:27 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/22 15:59:25 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NbVector.hpp"

NbVector::NbVector():len(0)
{}

NbVector::NbVector(std::vector<Number> const & vec):nbs(vec), len(vec.size())
{}

NbVector::NbVector(NbVector const & nbv):nbs(nbv.nbs), len(nbv.len)
{}

NbVector::~NbVector()
{}

NbVector &	NbVector::operator=(NbVector const & rhs)
{
	if (this != &rhs)
	{
		nbs = rhs.nbs;
		len = rhs.len;
	}
	return *this;
}

Number &	NbVector::operator[](unsigned int i)
{
	return nbs[i];
}

void	NbVector::loadData(int argc, char **argv)
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

void	NbVector::clear()
{
	nbs.clear();
	len = 0;
}

void	NbVector::push(Number nb)
{
	nbs.push_back(nb);
	len++;
}

void	NbVector::increase()
{
	len++;
}

unsigned int	NbVector::getLen()
{
	return len;
}

std::vector<Number> &	NbVector::getVector()
{
	return nbs;
}

Number &	NbVector::getByIndex(unsigned int index)
{
	for (unsigned int i = 0; i < len; i++)
	{
		if (nbs[i].getIndex() == index)
			return (nbs[i]);
	}
	throw (OutOfRangeException());
}

std::ostream & operator<<(std::ostream & ost, NbVector & rhs)
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
