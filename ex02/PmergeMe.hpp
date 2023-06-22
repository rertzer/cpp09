/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:09:30 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/22 15:36:06 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include "NbVector.hpp"

void	fjSort(NbVector & to_sort);
void	pairSwap(NbVector & to_sort);
void	splitMe(NbVector & to_sort, NbVector & halfbig, NbVector & remain, NbVector & pairing);
void	reload(NbVector & to_sort, NbVector & remain, NbVector & halfbig, NbVector & pairing);
void	reinsert(NbVector & to_sort, NbVector & halfbig, NbVector & remain, NbVector & pairing);
void	getOrder(std::vector<unsigned int> & the_ordrer, unsigned int len);
unsigned int	nextGroupSize(unsigned int g, unsigned int group);
void	binaryInsert(NbVector & to_sort, Number r);

#endif
