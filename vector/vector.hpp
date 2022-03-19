/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:29:31 by amine             #+#    #+#             */
/*   Updated: 2022/03/19 19:37:51 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <memory>
#include "vector_iterator.hpp"

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef	T							value_type;
			typedef	Allocator					allocator_type;
			typedef	allocator_type::reference	reference;
			typedef	allocator_type::pointer		pointer;
			typedef vector_iterator				iterator;
			typedef ptrdiff_t					difference_type;
			typedef	size_t						size_type;


			explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0);
			explicit	vector (size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _size(n), _capacity(n), _alloc(alloc) // Fill constructor
			{
				_array = _alloc.allocate(_size);
				for (int i = 0; i < n; ++i)
					_alloc.construct(&_array[i], val);
			};
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {};

			vector (const vector &x) { *this = x; };
			~vector(void) {};
	
			vector&     operator=(vector const & src);

			size_type			max_size(void) {return _alloc.max_size(); }

		private :
			size_type						_size;
			size_type						_capacity; //Always double capacity on array size max reached and need to realloc
			pointer							_array;
			allocator_type					_alloc;
	};



}