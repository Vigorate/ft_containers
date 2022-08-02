/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:45:00 by amine             #+#    #+#             */
/*   Updated: 2022/08/02 18:14:51 by amine            ###   ########.fr       */
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

	template <class Category, class T, class Distance = ptrdiff_t, class Reference = T &, class Pointer = T *>
	class reverse_vector_iterator
	{
		public:
			typedef	T			value_type;
			typedef	Distance	difference_type;
			typedef	Pointer		pointer;
			typedef	Reference	reference;
			typedef	Category	iterator_category;

			reverse_vector_iterator(T *ptr)
			{
				_pointer = ptr;
			}
			reverse_vector_iterator(const reverse_vector_iterator &other)
			{
				_pointer = other._pointer;
			}
			virtual ~reverse_vector_iterator(){};
			reverse_vector_iterator &operator=(const reverse_vector_iterator &other)
			{
				_pointer = other._pointer;
				return *this;
			}
			reverse_vector_iterator &operator++()
			{
				_pointer++;
				return *this;
			}
			reverse_vector_iterator &operator--()
			{
				_pointer--;
				return *this;
			}
			reverse_vector_iterator operator++(int)
			{
				reverse_vector_iterator tmp(*this);
				_pointer--;
				return tmp;
			}
			reverse_vector_iterator operator--(int)
			{
				reverse_vector_iterator tmp(*this);
				_pointer++;
				return tmp;
			}
			reverse_vector_iterator &operator+(int i)
			{
				_pointer += i;
				return *this;
			}
			reverse_vector_iterator &operator-(int i)
			{
				_pointer -= i;
				return *this;
			}

			bool	operator==(const reverse_vector_iterator &other) const { return _pointer == other._pointer; }
			bool	operator!=(const reverse_vector_iterator &other) const { return _pointer != other._pointer; }
			bool	operator>(const reverse_vector_iterator &other) const { return _pointer > other._pointer; }
			bool	operator<(const reverse_vector_iterator &other) const { return _pointer < other._pointer; }
			bool	operator>=(const reverse_vector_iterator &other) const { return _pointer >= other._pointer; }
			bool	operator<=(const reverse_vector_iterator &other) const { return _pointer <= other._pointer; }


			friend reverse_vector_iterator operator-(difference_type n, const reverse_vector_iterator &it)
			{
				return reverse_vector_iterator(it._pointer - n);
			}
			friend difference_type operator-(const reverse_vector_iterator &a, const reverse_vector_iterator &b)
			{
				return (a._pointer - b._pointer);
			}
			// friend bool 	operator> (const reverse_vector_iterator& lhs, const reverse_vector_iterator& rhs) { return lhs._pointer > rhs._pointer; }
			T &operator*()
			{
				return *_pointer;
			}
			T *operator->()
			{
				return &(operator*)();
			}

		private:
			T	*_pointer;

	};
}
