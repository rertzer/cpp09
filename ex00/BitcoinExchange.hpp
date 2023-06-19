/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:36:14 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/19 16:46:14 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <map>


class	BitcoinExchange
{
	public:

		//typedef	void (BitcoinExchange::*ef_ptr)(std::pair<struct tm, float>);
		
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const & btc);
		~BitcoinExchange();

		BitcoinExchange &	operator=(BitcoinExchange const & rhs);

		void	iterFile(char * const &filename, void (BitcoinExchange::*entryfun_ptr)(std::pair<struct tm, float>)); 
		void	loadCsv(char * const &filename);
		void	processCsvEntry(std::pair<struct tm, float>);
		void	processInput(std::string const & filename) const;
		void	processInputEntry(std::pair<struct tm, float>);
		void	printExchange() const;
		//float	getValueByDate(struct tm date) const;
		//float	convert(struct tm date, float amount) const;

		class	CsvParsingException: public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return ("BitcoinExchange::exception: CSV parsing error");
				}
		};

	private:
		std::pair<struct tm, float>	extractPair(std::string const & line, std::string const & delimiter) const;

		std::map<struct tm, float, bool(*)(struct tm const & , struct tm const &)>	exchange;
};

bool	timeCompare(struct tm const & a, struct tm const & b);	
#endif
