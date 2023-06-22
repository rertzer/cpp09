/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NbVector.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:20:31 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/21 16:46:51 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NBVECTOR_HPP
# define NBVECTOR_HPP

# include <iostream>
# include <sstream>
# include <vector>
# include <exception>
# include "Number.hpp"

class	NbVector
{
	public:
		NbVector();
		NbVector(std::vector<Number> const & vec);
		NbVector(NbVector const & nbv);
		~NbVector();
		
		NbVector &	operator=(NbVector const & rhs);
		Number &	operator[](size_t i);
		
		std::vector<Number>  &	getVector();
		size_t					getLen();
		Number &				getByIndex(unsigned int index);
		void					loadData(int argc, char **argv);
		void					push(Number nb);
		
		class	ParsingException: public std::exception
		{
			public:
				virtual const char * what() const throw()
				{
					return ("Error: Bad entry");
				}
		};

		class	OutOfRangeException: public std::exception
		{
			public:
				virtual const char * what() const throw()
				{
					return ("Error: Out of range index");
				}
		};


	private:
		std::vector<Number> 	nbs;
		size_t					len;
};

std::ostream & operator<<(std::ostream & ost, NbVector & rhs);
#endif
