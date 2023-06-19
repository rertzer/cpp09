/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 09:52:23 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/19 16:57:56 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	bool(*fn_pt)(struct tm const &, struct tm const &) = &timeCompare;
	exchange = std::map<struct tm, float, bool(*)(struct tm const &, struct tm const &)>(fn_pt);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const & btc)
{
	*this = btc;
}

BitcoinExchange::~BitcoinExchange()
{}

BitcoinExchange &	BitcoinExchange::operator=(BitcoinExchange const & rhs)
{
	if (this != &rhs)
	{
		exchange = rhs.exchange;
	}
	return *this;
}

void	BitcoinExchange::loadCsv(char *const & filename)
{
	iterFile(filename, &BitcoinExchange::processCsvEntry);
}

void	BitcoinExchange::iterFile(char * const & filename, void (BitcoinExchange::*entryfun_ptr)(std::pair<struct tm, float>))
{
	std::fstream fs (filename, std::ios::in);
	fs.exceptions(fs.failbit);

	try
	{
		std::string	line = "";
		std::getline(fs, line);
		
		fs.exceptions(fs.goodbit | fs.badbit);
		while (std::getline(fs, line))
		{
			std::cerr << line << std::endl;
			std::pair<struct tm, float>	entry = extractPair(line, ",");
			(this->*entryfun_ptr)(entry);
		}
	}
	catch (std::ios_base::failure & e)
	{
		fs.close();
		throw;
	}
	fs.close();
}

void	BitcoinExchange::processCsvEntry(std::pair<struct tm, float> entry)
{
	exchange.insert(entry);
}

std::pair<struct tm, float>	BitcoinExchange::extractPair(std::string const & line, std::string const & delimiter) const
{
	size_t				pos = 0;
	std::stringstream	ss;
	std::string			tmp = "";
	struct tm			date = {};
	float				value = 0;;

	pos = line.find(delimiter);
	if (pos == std::string::npos)
		throw (CsvParsingException());
	tmp = line.substr(0, pos);
	strptime(tmp.c_str(), "%Y-%m-%d", &date);
	tmp = line.substr(pos + 1, std::string::npos);
	ss << tmp;
	ss >> value;
	if (ss.fail())
		throw (CsvParsingException());
	return std::pair<struct tm, float>(date, value);
}

void	BitcoinExchange::printExchange() const
{
	for (std::map<struct tm, float>::const_iterator it = exchange.begin(); it != exchange.end(); it++)
	{
		
		std::cout << it->first.tm_year << " " << it->second << std::endl;
	}
}

void	BitcoinExchange::processInput(std::string const & filename)	const
{
	iterFile(filename, &BitcoinExchange::processInputEntry);	
}

void	BitcoinExchange::processInputEntry(std::pair<struct tm, float> entry)
{
	if (!validDate(entry->first))
	{
		std::cout << "Error: invalid date\n";
		return ;
	}
	if (entry->second < 0.0f)
	{
		std::cout << "Error: not a positive number\n";
		return ;
	}
	if (entry->second > 1000.0f)
	{
		std::cout << "Error: too large a number\n";
		return ;
	}
}


bool	timeCompare(struct tm const & a, struct tm const & b)
{
	if (a.tm_year == b.tm_year)
	{
		if (a.tm_mon == b.tm_mon)
			return a.tm_mday < b.tm_mday;
		return a.tm_mon < b.tm_mon;
	}
	return a.tm_year < b.tm_year;
}

