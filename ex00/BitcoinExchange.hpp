/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:36:14 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/20 12:10:10 by rertzer          ###   ########.fr       */
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

		void	loadCsv(std::string const &filename);
		void	loadInput(std::string const & filename);
		void	printExchange() const;
		//float	getValueByDate(struct tm date) const;

		class	CsvParsingException: public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return ("BitcoinExchange::exception: file parsing error");
				}
		};

		class	BadInputException: public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return ("Error: bad input");
				}
		};

		class	BadNumberException: public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return ("Error: bad number");
				}
		};

		class	BadDateException: public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return ("Error: bad date");
				}
		};
;



	private:
		void	iterFile(std::string const &filename, void (BitcoinExchange::*entryfun_ptr)(std::pair<struct tm, float>)); 
		void	processCsvEntry(std::pair<struct tm, float>);
		void	processInputEntry(std::pair<struct tm, float>);
		std::pair<struct tm, float>	extractPair(std::string const & line, std::string const & delimiter) const;
		float	convert(std::pair<struct tm, float>) const;

		std::map<struct tm, float, bool(*)(struct tm const & , struct tm const &)>	exchange;
};

bool	badDate(std::string tmp);
bool	timeCompare(struct tm const & a, struct tm const & b);	
#endif
