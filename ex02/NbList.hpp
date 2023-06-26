/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NbList.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:20:31 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/26 12:00:30 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NBLIST_HPP
# define NBLIST_HPP

# include <iostream>
# include <sstream>
# include <list>
# include <exception>
# include "Number.hpp"

class	NbList
{
	public:
		NbList();
		NbList(std::list<Number> const & vec);
		NbList(NbList const & nbv);
		~NbList();
		
		NbList &	operator=(NbList const & rhs);
		Number &	operator[](unsigned int i);
		
		std::list<Number>  &	getList();
		unsigned int			getLen();
		unsigned int			getBigPosByIndex(unsigned int index);
		Number &				getByIndex(unsigned int index);
		void					loadData(int argc, char **argv);
		void					clear();
		void					push(Number nb);
		void					increase();
		
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
		std::list<Number> 	nbs;
		unsigned int		len;
};

std::ostream & operator<<(std::ostream & ost, NbList & rhs);
#endif
