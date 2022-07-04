/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:33:43 by amine             #+#    #+#             */
/*   Updated: 2022/07/04 23:30:36 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>

namespace ft
{
	template < class T, class Compare = std::less<typename T::first_type>, class Alloc = std::allocator<T> >
	class	Bst
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

		class	Node
		{
			public:
				Node	*min() {}
				Node	*max() {}
				value		_pair;
				Node		*_up;
				Node		*_left
				Node		*_right;
				int			height;
				int			balance;
		};

		Bst(const value_compare &_compare = value_compare(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _compare(compare)
		{
			
		}

		private:
			Node					*_start;
			Node					*_end;
			size_type				_size;
			allocator_type			_alloc;
			std::allocator<Node>	_allocNode;
			key_compare				_compare;
	};
}