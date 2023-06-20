/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:18:35 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/20 12:10:27 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Enter one file name as argument\n";
		return 1;
	}
	std::string	input(argv[1]);

	BitcoinExchange	bce = BitcoinExchange();
	try
	{
		bce.loadCsv("data.csv");
		bce.loadInput(input);
	}
	catch (BitcoinExchange::CsvParsingException & e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	//bce.printExchange();
	return 0;
}
