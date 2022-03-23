/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:43:53 by amine             #+#    #+#             */
/*   Updated: 2022/03/23 15:00:37 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iterator>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag				: public input_iterator_tag{};
	struct bidirectional_iterator_tag		: public bidirectional_iterator_tag{};
	struct random_access_iterator_tag		: public bidirectional_iterator_tag{};
	
	template <class Iterator>
	class iterator_traits
	{
		typedef	typename	Iterator::difference_type		difference_type;
		typedef	typename	Iterator::value_type			value_type;
		typedef	typename	Iterator::pointer				pointer;
		typedef	typename	Iterator::reference				reference;
		typedef	typename	Iterator::iterator_category		iterator_category;
	};
	
	template <class T>
	class iterator_traits<T*>
	{
		typedef				ptrdiff_t						difference_type;
		typedef				T								value_type;
		typedef				T*								pointer;
		typedef				T&								reference;
		typedef				random_access_iterator_tag		iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
		typedef				ptrdiff_t						difference_type;
		typedef				T								value_type;
		typedef				const T*						pointer;
		typedef				const T&						reference;
		typedef				random_access_iterator_tag		iterator_category;
	};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
	class iterator
	{
			typedef	Category			iterator_category;
			typedef T					value_type;
			typedef Distance			difference_type;
			typedef Pointer				pointer;
			typedef	Reference			reference;
	};
	
	template <class Ite>
	class random_access_iterator : public iterator<random_access_iterator_tag, Ite>
	{
		
	};
	
}