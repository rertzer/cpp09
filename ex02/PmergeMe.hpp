/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:09:30 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/24 11:10:47 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include "NbVector.hpp"

class	PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(NbVector const  & mm);
		PmergeMe(PmergeMe const & rhs);
		~PmergeMe();

		PmergeMe &	operator=(PmergeMe const & rhs);

		void				fjSort();
		NbVector &	getMergeMe();

	private:
		void			pairSwap();
		void			splitMe();
		void			reload();
		void			reinsert();
		void			getOrder();
		unsigned int	nextGroupSize(unsigned int g, unsigned int group);
		void			binaryInsert(Number r, long int right);

		NbVector					merge_me;
		NbVector					halfbig;
		NbVector					remain;
		NbVector					pairing;
		std::vector<unsigned int>	the_order;
};
#endif
