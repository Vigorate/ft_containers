/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:16:31 by ambelkac          #+#    #+#             */
/*   Updated: 2022/03/22 15:15:02 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <iostream>

void		display_vector(std::vector<int> v)
{
	std::vector<int>::iterator		begin = v.begin();
	std::vector<int>::iterator		end = v.end();

	while (begin != end)
	{
		std::cout << *begin;
		if (begin + 1 != end)
			std::cout << " ";
		++begin;
	}
	std::cout << std::endl;
}

int			main(void)
{
	// Constructor test
	{
	std::vector<int>		def;
	std::vector<int>		fill(5, 10);

	def.assign(6, 11);
	std::vector<int>::iterator		begin;
	std::vector<int>::iterator		end;

	begin = def.begin() + 1;
	end = def.end() - 1;

	std::vector<int>		rang(begin, end);

	std::cout << "default vector :" << std::endl;
	display_vector(def);
	std::cout << "fill vector :" << std::endl;
	display_vector(fill);
	std::cout << "range vector :" << std::endl;
	display_vector(rang);
	}

}