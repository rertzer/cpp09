/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NbVector.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:28:27 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/21 16:44:17 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NbVector.hpp"

NbVector::NbVector():len(0)
{}

NbVector::NbVector(std::vector<Number> const & vec):nbs(vec), len(len(vec))
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

Number &	NbVector::operator[](size_t i)
{
	return nbs[i];
}

void	NbVector::loadData(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		std::stringstream	ss;
		Number			nb = Number();

		ss.exceptions(ss.failbit | ss.badbit);
		if (!std::isdigit(argv[i][0]))
			throw (ParsingException());
		ss << argv[i];
		unsigned int tmp;
		ss >> tmp;
		nb.setValue(tmp);
		nb.setIndex(i);
		nbs.push_back(nb);
		len++;
	}
}


void	NbVector::push(Number nb)
{
	nbs.push_back(nb);
	len++;
}

size_t	NbVector::getLen()
{
	return len;
}

std::vector<Number> &	NbVector::getVector()
{
	return nbs;
}

Number &	NbVector::getByIndex(unsigned int index)
{
	for (size_t i = 0; i < len; i++)
	{
		if (nbs[i].getIndex() == index)
			return (nbs[i]);
	}
	throw (OutOfRangeException());
}

std::ostream & operator<<(std::ostream & ost, NbVector & rhs)
{
	for (std::vector<Number>::iterator it = rhs.getVector().begin(); it != rhs.getVector().end(); it++)
	{
		ost << *it;
		if (it->getIndex() != rhs.getVector().back().getIndex())
			ost << " ";
		else
			ost << std::endl;
	}
	return ost;
}
