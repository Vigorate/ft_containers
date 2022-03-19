/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:29:31 by amine             #+#    #+#             */
/*   Updated: 2022/03/19 16:15:35 by amine            ###   ########.fr       */
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


			explicit	vector(void) : value_type(0), allocator_type(0), difference_type(0), size_type(0), pointer(NULL) {};
			explicit	vector (size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) {};
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {};

			vector(vector const & src);
			~vector(void);
	
			vector&     operator=(vector const & src);

		private :
			
	};



}