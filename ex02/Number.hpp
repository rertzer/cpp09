/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Number.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:07:32 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/22 10:18:37 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMBER_HPP
# define NUMBER_HPP

#include <iostream>

class	Number
{
	public:
		Number();
		Number(unsigned int i, unsigned int v);
		Number(Number const & nb);
		~Number();
		Number &	operator=(Number const & rhs);
		bool		operator<(Number const & rhs) const;
		bool		operator==(Number const & rhs) const;

		void			setIndex(unsigned int i);
		void			setValue(unsigned int v);
		unsigned int	getIndex() const;
		unsigned int	getValue() const;

	private:
		unsigned int	index;
		unsigned int	value;
};

std::ostream & operator<<(std::ostream & ost, Number const & rhs);
#endif
