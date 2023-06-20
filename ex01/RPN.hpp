/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:30:00 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/20 16:45:24 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <sstream>
#include <deque>
#include <exception>

typedef	int	(*opfun)(int, int);

void	hsilop(std::string exp);
opfun	getop(char c);
int		add(int lhs, int rhs);
int		subs(int lhs, int rhs);
int		multi(int lhs, int rhs);
int		div(int lhs, int rhs);


class	RPNException: public std::exception
{
	public:
		virtual const char * what() const throw ()
		{
			return  "Error";
		}
};

#endif
