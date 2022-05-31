/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:45:00 by amine             #+#    #+#             */
/*   Updated: 2022/05/31 18:16:16 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../utils/iterator_traits.hpp"
#include "../utils/enable_if.hpp"

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t, class Reference = T&, class Pointer = T*>
	class vector_iterator
	{
		public:
			typedef	T			value_type;
			typedef	Distance	difference_type;
			typedef	Pointer		pointer;
			typedef	Reference	reference;
			typedef	Category	iterator_category;
			
			vector_iterator(T *pointer) { _pointer = pointer; }

			vector_iterator(const vector_iterator &src) { _pointer = src._pointer; }

			virtual	~vector_iterator() {};

			vector_iterator		&operator=(const vector_iterator &other)
			{
				_pointer = other._pointer;
				return *this;
			}

			vector_iterator		&operator++()
			{
				_pointer++;
				return *this;
			}
			
			vector_iterator		&operator--()
			{
				_pointer--;
				return *this;
			}

			vector_iterator		operator++(int)
			{
				vector_iterator	tmp = *this;
				_pointer++;
				return tmp;
			}

			vector_iterator		operator--(int)
			{
				vector_iterator	tmp = *this;
				_pointer--;
				return tmp;
			}

			bool	operator==(const vector_iterator &other) const { return _pointer == other._pointer; }
			bool	operator!=(const vector_iterator &other) const { return _pointer != other._pointer; }
			bool	operator>(const vector_iterator &other) const { return _pointer > other._pointer; }
			bool	operator<(const vector_iterator &other) const { return _pointer < other._pointer; }
			bool	operator>=(const vector_iterator &other) const { return _pointer >= other._pointer; }
			bool	operator<=(const vector_iterator &other) const { return _pointer <= other._pointer; }
			
			T	&operator*() { return *_pointer; };
			T	*operator->() { return &(operator*)(); };

			vector_iterator		operator+(int i)
			{
				_pointer += i;
				return *this;
			}

			vector_iterator		operator-(int i)
			{
				_pointer -= i;
				return *this;
			}

		private:
			T	*_pointer;
	};
}