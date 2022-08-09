/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:45:00 by amine             #+#    #+#             */
/*   Updated: 2022/08/09 10:28:13 by ambelkac         ###   ########.fr       */
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
			
			vector_iterator(T *pointer) { _ptr = pointer; }

			vector_iterator(const vector_iterator &src) { _ptr = src._ptr; }

			virtual	~vector_iterator() {};

			vector_iterator		&operator=(const vector_iterator &other)
			{
				_ptr = other._ptr;
				return *this;
			}

			vector_iterator		&operator++()
			{
				_ptr++;
				return *this;
			}
			
			vector_iterator		&operator--()
			{
				_ptr--;
				return *this;
			}

			vector_iterator		operator++(int)
			{
				vector_iterator	tmp = *this;
				_ptr++;
				return tmp;
			}

			vector_iterator		operator--(int)
			{
				vector_iterator	tmp = *this;
				_ptr--;
				return tmp;
			}

			vector_iterator		operator+(int i)
			{
				_ptr += i;
				return *this;
			}

			vector_iterator		operator-(int i)
			{
				_ptr -= i;
				return *this;
			}

			bool	operator==(const vector_iterator &other) const { return _ptr == other._ptr; }
			bool	operator!=(const vector_iterator &other) const { return _ptr != other._ptr; }
			bool	operator>(const vector_iterator &other) const { return _ptr > other._ptr; }
			bool	operator<(const vector_iterator &other) const { return _ptr < other._ptr; }
			bool	operator>=(const vector_iterator &other) const { return _ptr >= other._ptr; }
			bool	operator<=(const vector_iterator &other) const { return _ptr <= other._ptr; }
			
			T	&operator*() { return *_ptr; };
			T	*operator->() { return &(operator*)(); };

		private:
			T	*_ptr;
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

			reverse_vector_iterator(T *pointer) { _ptr = pointer; }

			reverse_vector_iterator(const reverse_vector_iterator &other) { _ptr = other._ptr; }

			virtual ~reverse_vector_iterator(){};

			reverse_vector_iterator &operator=(const reverse_vector_iterator &other)
			{
				_ptr = other._ptr;
				return *this;
			}

			reverse_vector_iterator &operator++()
			{
				_ptr++;
				return *this;
			}

			reverse_vector_iterator &operator--()
			{
				_ptr--;
				return *this;
			}

			reverse_vector_iterator operator++(int)
			{
				reverse_vector_iterator	tmp = *this;
				_ptr--;
				return tmp;
			}

			reverse_vector_iterator operator--(int)
			{
				reverse_vector_iterator	tmp = *this;
				_ptr++;
				return tmp;
			}

			reverse_vector_iterator &operator+(int i)
			{
				_ptr += i;
				return *this;
			}

			reverse_vector_iterator &operator-(int i)
			{
				_ptr -= i;
				return *this;
			}

			bool	operator==(const reverse_vector_iterator &other) const { return _ptr == other._ptr; }
			bool	operator!=(const reverse_vector_iterator &other) const { return _ptr != other._ptr; }
			bool	operator>(const reverse_vector_iterator &other) const { return _ptr > other._ptr; }
			bool	operator<(const reverse_vector_iterator &other) const { return _ptr < other._ptr; }
			bool	operator>=(const reverse_vector_iterator &other) const { return _ptr >= other._ptr; }
			bool	operator<=(const reverse_vector_iterator &other) const { return _ptr <= other._ptr; }

			friend reverse_vector_iterator operator-(difference_type n, const reverse_vector_iterator &it)
			{
				return reverse_vector_iterator(it._ptr - n);
			}
			friend difference_type operator-(const reverse_vector_iterator &a, const reverse_vector_iterator &b)
			{
				return (a._ptr - b._ptr);
			}

			T &operator*() { return *_ptr; }
			T *operator->() { return &(operator*)(); }

		private:
			T	*_ptr;

	};
}
