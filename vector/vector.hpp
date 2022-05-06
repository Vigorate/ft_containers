/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:29:31 by amine             #+#    #+#             */
/*   Updated: 2022/05/06 16:48:35 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <memory>
#include <exception>
#include <stdexcept>
#include "vector_iterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef				T												value_type;
			typedef				Alloc											allocator_type;
			typedef	typename	allocator_type::reference						reference;
			typedef	typename	allocator_type::const_reference					const_reference;
			typedef	typename	allocator_type::pointer							pointer;
			typedef	typename	allocator_type::const_pointer					const_pointer;
			typedef				vector_iterator<random_access_iterator_tag, T>	iterator;
			typedef				ptrdiff_t										difference_type;
			typedef				size_t											size_type;

			//				CONSTRUCTOR
			// Default
			explicit	vector (const allocator_type &alloc = allocator_type()) : _size(0), _capacity(0), _array(NULL), _alloc(alloc) {};
			// Fill
			explicit	vector (size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _size(n), _capacity(n), _alloc(alloc)
			{
				_array = _alloc.allocate(n);
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(&_array[i], val);
			};
			// Range
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				for (; first != last; ++first)
					push_back(first);
			};
			// Copy
			vector (const vector &x) : _size(x._size), _capacity(x._size), _array(NULL), _alloc(x._alloc)
			{
				_array = _alloc.allocate(x._capacity);
				for (size_type i = 0; i < _size; ++i)
					_alloc.construct(&_array[i], x._array[i]);
			};


			//				DESTRUCTOR
			~vector(void)
			{
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(&_array[i]);
				_alloc.deallocate(_array, _capacity);
			};


			//				OPERATOR OVERLOAD
			vector		&operator=(vector const & src)
			{
				reserve(src._size);
				for (size_type i = 0; i < src._size; ++i)
					_alloc.construct(&_array[i], src._array[i]);
				_size = src._size;
				return *this;
			};


			//				CAPACITY
			size_type			size(void) const		{ return _size; };
			
			size_type			max_size(void) const	{ return _alloc.max_size(); };
			
			void				resize (size_type n, value_type val = value_type())
			{
				while (_size > n)
					pop_back();
				if (n > _capacity * 2)
					reserve(n);
				while (_size < n)
					push_back(val);

				
				// pointer			n_arr;
				// if (n < _size)
				// {
				// 	n_arr = _alloc.allocate(_capacity);
				// 	for (size_type i = 0; i < n; ++i)
				// 		_alloc.construct(&n_arr[i], _array[i]);
				// 	for (int i = n; i < _size; ++ i)
				// 		_alloc.destroy(&_array[i]);
				// 	_alloc.deallocate(_array, _capacity);
				// 	_size = n;
				// 	_array = n_arr;
				// }
				// if (n > _size)
				// {
				// 	if (_capacity >= n)
				// 	{
				// 		for (size_type i = _size; i < n; ++i)
				// 			n_arr[i], val;
				// 		_size = n;
				// 	}
				// 	else
				// 	{
				// 		n_arr = _alloc.allocate(_capacity * 2);
				// 		for (size_type i = 0; i < _size; ++i)
				// 			_alloc.construct(&n_arr[i], _array[i]);
				// 		for (size_type i = _size; i < n; ++i)
				// 			n_arr[i] = val;
				// 		_size = n;
				// 		_capacity = _capacity * 2 > n ? _capacity * 2 : n;
				// 		_array = n_arr;
				// 	}
				// }
			};

			size_type			capacity(void) const	{ return _capacity; };

			bool				empty(void) const		{ return !_size ? true : false; };

			void				reserve(size_type n)
			{
				if (n > _alloc.max_size())
					throw	std::length_error("Lenght Error.");
				pointer		n_arr;
				if (n > _capacity)
				{
					n_arr = _alloc.allocate(n);
					for (size_type i = 0; i < _size; ++i)
					{
						_alloc.construct(&n_arr[i], _array[i]);
						_alloc.destroy(&_array[i]);
					}
					_alloc.deallocate(_array, _capacity);
					_array = n_arr;
					_capacity = n;
				}
			};


			//				ELEMENT ACCES
			reference			operator[] (size_type n)		{ return _array[n]; };
			const_reference		operator[] (size_type n) const	{ return _array[n]; };
			
			reference			at (size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("Out of Range");
				return _array[n];
			};
			const_reference		at (size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("Out of Range.");
				return _array[n];
			};
			
			reference			front(void)			{ return _array[0]; };
			const_reference		front(void) const	{ return _array[0]; };

			reference			back(void)			{ return _array[_size - 1]; };
			const_reference		back(void) const	{ return _array[_size - 1]; };


			//				MODIFIER
			//	range
			template <class InputIterator>
			void	assign (InputIterator first, InputIterator last);
			//	fill
			void	assign (size_type n, const value_type& val)
			{
				for (int i = 0; i < _size; ++i)
					_alloc.destroy(_array[i]);
				if (n > _capacity)
				{
					pointer		n_arr;
					n_arr = _alloc.allocate(n);
					_capacity = n;
				}
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(&_array[i], val);
				_alloc.deallocate(_array, n);
				_size = n;
			};

			void	push_back (const value_type& val)
			{
				pointer		n_arr;
				if (_capacity && _capacity < _size + 1)
				{
					n_arr = _alloc.allocate(_capacity * 2);
					for (size_type i = 0; i < _size; ++i)
					{
						_alloc.construct(&n_arr[i], _array[i]);
						_alloc.destroy(&_array[i]);
					}
					_alloc.deallocate(_array, _capacity);
					_array = n_arr;
					_capacity = _capacity * 2;
				}
				if (_capacity == 0)
				{
					_capacity = 1;
					n_arr = _alloc.allocate(1);
					_array = n_arr;
				}
				_size += 1;
				_alloc.construct(&_array[_size - 1], val);
			};

			void	pop_back (void)
			{
				_size -= 1;
				_alloc.destroy(&_array[_size - 1]);
			}

			void	clear (void)
			{
				for (int i = 0; i < _size; ++i)
					_alloc.destroy(&_array[i]);
				_size = 0;
			};


			//	OPERATOR4
			

		private :
			size_type						_size;
			size_type						_capacity; //Always double capacity on array size max reached and need to realloc
			pointer							_array;
			allocator_type					_alloc;
	};

			template <class T, class Alloc>
			bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
			{
				if (lhs._size != rhs._size)
					return false;
				for (size_t i = 0; i < lhs.size(); ++i)
					if (lhs[i] != rhs[i])
						return false;
				return true;
			}
			template <class T, class Alloc>
			bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { !(lhs == rhs); };


}