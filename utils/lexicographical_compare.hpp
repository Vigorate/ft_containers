/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:34:44 by amine             #+#    #+#             */
/*   Updated: 2022/05/06 16:38:50 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector_iterator.hpp"
#include "vector.hpp"

template <class InputIterator1, class InputIterator2>
bool	lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2);
{
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1)
			return false;
		else if (*first1 < *first2)
			return true;
		++first1; 
		++first2;
	}
	return first2 != last2;
}