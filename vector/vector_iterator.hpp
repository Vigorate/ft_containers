/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:43:53 by amine             #+#    #+#             */
/*   Updated: 2022/03/22 17:30:56 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
	class iterator
	{
		public:
			typedef	Category			iterator_category;
			typedef T					value_type;
			typedef Distance			difference_type;
			typedef Pointer				pointer;
			typedef	Reference			reference;

			iterator(void);
			iterator(iterator const & src) { this->_ptr = src._ptr; };
			~iterator(void);

//			pointer			operator[](ptrdiff_t idx) { return _ptr[idx]; };

		private :
			pointer		_ptr;
	};
}