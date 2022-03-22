/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:29:31 by amine             #+#    #+#             */
/*   Updated: 2022/03/22 18:03:21 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <memory>
#include <exception>
#include <stdexcept>
//#include "vector_iterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef				T									value_type;
			typedef				Alloc								allocator_type;
			typedef	typename	allocator_type::reference			reference;
			typedef	typename	allocator_type::const_reference		const_reference;
			typedef	typename	allocator_type::pointer				pointer;
			typedef	typename	allocator_type::const_pointer		const_pointer;
//			typedef				vector_iterator						iterator;
			typedef				ptrdiff_t							difference_type;
			typedef				size_t								size_type;

			//				CONSTRUCTOR
			// Default
			explicit	vector (const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0), _array(NULL) {};
			// Fill
			explicit	vector (size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _size(n), _capacity(n), _alloc(alloc)
			{
				_array = _alloc.allocate(_size);
				for (int i = 0; i < n; ++i)
					_alloc.construct(&_array[i], val);
			};
			// Range
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _alloc(alloc) {}; // Range
			// Copy
			vector (const vector &x) { *this = x; };

			//				DESTRUCTOR
			~vector(void)
			{
				for (int i = 0; i < _size; ++i)
					_alloc.destroy(_array[i]);
				_alloc.deallocate(_array, _capacity);
			};
	

			//				OPERATOR OVERLOAD
			vector		&operator=(vector const & src)
			{
				_size = src._size;
				_capacity = src._capacity;
				_array = src._array;
				_alloc = src._alloc;
				return *this;
			};


			//				CAPACITY
			size_type			size(void) const		{ return _size; };
			
			size_type			max_size(void) const	{ return _alloc.max_size(); };
			
			void				resize (size_type n, value_type val = value_type())
			{
				pointer			n_arr;
				if (n < _size)
				{
					_alloc.allocate(n_arr, n);
					for (int i = 0; i < n; ++i)
						n_arr[i] = _array[i];
					for (int i = n; i < _size; ++ i)
						_alloc.destroy(_array[i]);
					_alloc.deallocate(_array, _capacity);
					_capacity = n;
					_size = n;
					_array = n_arr;
				}
				if (n > _size)
				{
					_alloc.allocate(n_arr, n);
					for (int i = 0; i < _size; ++i)
						n_arr[i] = _array[i];
					for (int i = size; i < n; ++i)
						n_arr[i] = val;
					_capacity = n;
					_size = n;
					_array = n_arr;
				}
			};

			size_type			capacity(void) const	{ return _capacity; };

			bool				empty(void) const		{ return !_size ? true : false; }

			void				reserve(size_type n)
			{
				pointer		n_arr;
				if (n > _capacity)
				{
					n_arr = _alloc.allocate(n);
					for (int i = 0; _array[i]; ++i)
						n_arr[i] = _array[i];
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
					throw std::out_of_range();
				return _array[n];
			};
			const_reference		at (size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range();
				return _array[n];
			};
			
			reference			front(void)			{ return _array[0]; };
			const_reference		front(void) const	{ return _array[0]; };

			reference			back(void)			{ return _array[_size - 1]; };
			const_reference		back(void) const	{ return _array[_size - 1]; };

		private :
			size_type						_size;
			size_type						_capacity; //Always double capacity on array size max reached and need to realloc
			pointer							_array;
			allocator_type					_alloc;
	};



}