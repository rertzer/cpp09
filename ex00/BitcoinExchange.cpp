/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 09:52:23 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/28 13:37:28 by rertzer          ###   ########.fr       */
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

void	BitcoinExchange::loadCsv(std::string const & filename)
{
	iterFile(filename, &BitcoinExchange::processCsvEntry);
}

void	BitcoinExchange::iterFile(std::string const & filename, void (BitcoinExchange::*entryfun_ptr)(std::pair<struct tm, float>))
{
	std::fstream fs (filename.c_str(), std::ios::in);
	fs.exceptions(fs.failbit);
	
	std::string	delimiter = "|";
	bool csv = (filename.rfind(".csv") + 4 == filename.length());
	if (csv)
		delimiter = ",";

	try
	{
		std::string	line = "";
		std::getline(fs, line);
		
		fs.exceptions(fs.goodbit | fs.badbit);
		while (std::getline(fs, line))
		{
			try
			{
				std::pair<struct tm, float>	entry = extractPair(line, delimiter);
				(this->*entryfun_ptr)(entry);
			}
			catch (BitcoinExchange::BadInputException & e)
			{
				if (csv)
				{
					fs.close();
					throw;
				}
				else
					std::cout << e.what() << std::endl;
			}
			catch (BitcoinExchange::BadNumberException & e)
			{
				if (csv)
				{
					fs.close();
					throw;
				}
				else
					std::cout << e.what() << std::endl;
			}
			catch (BitcoinExchange::BadDateException & e)
			{
				if (csv)
				{
					fs.close();
					throw;
				}
				else
					std::cout << e.what() << std::endl;
			}
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
		throw (BadInputException());
	tmp = line.substr(0, pos);
	if (badDate(tmp))
		throw (BadDateException());
	strptime(tmp.c_str(), "%Y-%m-%d", &date);
	tmp = line.substr(pos + 1, std::string::npos);
	ss << tmp;
	ss >> value;
	if (ss.fail())
		throw (BadNumberException());
	return std::pair<struct tm, float>(date, value);
}

void	BitcoinExchange::printExchange() const
{
	for (std::map<struct tm, float>::const_iterator it = exchange.begin(); it != exchange.end(); it++)
	{
		
		std::cout << it->first.tm_year << " " << std::fixed << it->second << std::endl;
	}
}

void	BitcoinExchange::loadInput(std::string const & filename)
{
	iterFile(filename, &BitcoinExchange::processInputEntry);	
}

void	BitcoinExchange::processInputEntry(std::pair<struct tm, float> entry)
{
	if (entry.second < 0.0f)
	{
		std::cout << "Error: not a positive number\n";
		return ;
	}
	if (entry.second > 1000.0f)
	{
		std::cout << "Error: too large a number\n";
		return ;
	}
	if (timeCompare(entry.first, (*exchange.begin()).first))
	{
		std::cout << "Error: date to early\n";
		return ;
	}

	char	date[11];
	strftime(date, 11, "%Y-%m-%d", &entry.first);
	std::cout << date << " => " << entry.second << " = " << convert(entry) << std::endl;
}

float	BitcoinExchange::convert(std::pair<struct tm, float> entry) const
{
	std::map<struct tm, float, bool(*)(struct tm const &, struct tm const &)>::const_iterator it;
	it = exchange.upper_bound(entry.first);
	it--;
	return (entry.second * it->second);
}

bool	timeCompare(struct tm const & a, struct tm const & b)
{
	if (a.tm_year == b.tm_year)
	{
		if (a.tm_mon == b.tm_mon)
			return (a.tm_mday < b.tm_mday);
		return (a.tm_mon < b.tm_mon);
	}
	return (a.tm_year < b.tm_year);
}
bool	badDate(std::string tmp)
{
	std::stringstream ss;
	ss << tmp.substr(5, 2);
	unsigned int	month;
	ss >> month;
	ss.clear();
	ss << tmp.substr(8,2);
	unsigned int	day;
	ss >> day;
	if (month < 1 || month > 12 || day < 1 || day > 31)
		return (true);
	return false;
}
