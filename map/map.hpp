/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:11:41 by amine             #+#    #+#             */
/*   Updated: 2022/07/04 09:19:21 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "bst.hpp"

namespace ft
{
	
	template < class Key, class T, class Comapre = less<Key>, class Alloc = allocator< pair<const Key,T> >>
	class map
	{
		public:
			typedef				Key									key_type;
			typedef				T									mapped_type;
			typedef				pair<const Key, T>					value_type;
			typedef				Compare								value_compare;
			typedef				Alloc								allocator_type;
			typedef	typename	allocator_type::reference			reference;
			typedef	typename	allocator_type::const_reference		const_reference;
			typedef	typename	allocator_type::pointer				pointer;
			typedef	typename	allocator_type::const_pointer		const_pointer;
			typedef				map_iterator						iterator;
			typedef				map_iterator						const_iterator;
			typedef				ptrdiff_t							difference_type;
			typedef				size_t								size_type;

			//				CONSTRUCTOR
			explicit	map (const allocator_type &alloc = allocator_type())

			private:
				
	};
}