/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:18:35 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/19 16:15:48 by rertzer          ###   ########.fr       */
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

	BitcoinExchange	bce = BitcoinExchange();
	try
	{
		bce.loadCsv(argv[1]);
	}
	catch (BitcoinExchange::CsvParsingException & e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	bce.printExchange();
	return 0;
}
