/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:43:53 by amine             #+#    #+#             */
/*   Updated: 2022/03/19 15:57:59 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	template < typename T >
	class vector_iterator
	{
		public:

			iterator(void);
			iterator(iterator const & src) { this->pointer = src.pointer; };
			~iterator(void);

			T		*operator[](ptrdiff_t idx) { return pointer[idx]; };

		private :
			T		*pointer;
	};
}