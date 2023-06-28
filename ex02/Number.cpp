/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Number.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:47:49 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/28 15:16:29 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Number.hpp"

Number::Number():index(0), value(0)
{}

Number::Number(unsigned int i, unsigned int v):index(i), value(v)
{}

Number::Number(Number const  & nb):index(nb.index), value(nb.value)
{}

Number::~Number()
{}

Number &	Number::operator=(Number const & rhs)
{
	index = rhs.index;
	value = rhs.value;
	return *this;
}

bool	Number::operator<(Number const & rhs) const
{
	return (value < rhs.value);
}

bool	Number::operator==(Number const & rhs) const
{
	return (value == rhs.value);
}

void	Number::setIndex(unsigned int i)
{
	index = i;
}

void	Number::setValue(unsigned int v)
{
	value = v;
}

unsigned int	Number::getIndex() const
{
	return index;
}

unsigned int	Number::getValue() const
{
	return value;
}

std::ostream &	operator<<(std::ostream & ost, Number const & rhs)
{
	ost << rhs.getValue();
	return ost;
}
