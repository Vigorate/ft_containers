/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:11:41 by amine             #+#    #+#             */
/*   Updated: 2022/08/09 10:44:37 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "avl_tree.hpp"
#include <memory.h>
#include "map_iterator.hpp"
#include "pair.hpp"

namespace ft
{
	
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< pair<const Key,T> >>
	class map
	{
		public:
			typedef				Key																	key_type;
			typedef				T																	mapped_type;
			typedef				ft::pair<key_type,mapped_type>										value_type;
			typedef				Compare																key_compare;
			typedef				Alloc																allocator_type;
			typedef				Tree< value_type, Compare, Alloc>									tree;
			typedef typename	tree::Node															Node;
			typedef				Tree< const value_type, Compare, Alloc>								const_tree;
			typedef typename	allocator_type::reference											reference;
			typedef typename	tree::value_compare													value_compare;
			typedef				map_iterator<bidirectional_iterator_tag, tree>						iterator;
			typedef				map_iterator<bidirectional_iterator_tag, const_tree, tree>			const_iterator;
			typedef				reverse_map_iterator<bidirectional_iterator_tag, tree>				reverse_iterator;
			typedef				reverse_map_iterator<bidirectional_iterator_tag, const_tree, tree>	const_reverse_iterator;
			typedef				size_t																size_type;

			//				CONSTRUCTOR
			// Default
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _tree(comp, alloc) {}
			// Range
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _tree(comp, alloc)
			{ for (; first != last; ++first) insert(*first); }
			// Copy
			map(const map &x) { *this = x; }

			//				DESTRUCTOR
			~map() {}

			map					&operator=(const map &x)
			{
				clear();
				insert(x.begin(), x.end());
				return *this;
			}

			allocator_type		get_allocator() const { return _tree.get_allocator(); }

			//				CAPACITY
			bool		empty() const { return _tree.size() == 0; }
			size_type	size() const { return _tree.size(); }
			size_type	max_size() const { return _tree.max_size(); }

			//				ITERATOR
			iterator				begin() { return iterator((_tree.size() ? _tree.minimum() : _tree._last()), _tree._last()); }
			iterator				end() { return iterator(_tree._last(), _tree._last()); }
			const_iterator			begin() const { return const_iterator((_tree.size() ? _tree.minimum() : _tree._last()), _tree._last()); }
			const_iterator			end() const { return const_iterator(_tree._last(), _tree._last()); }
			reverse_iterator		rbegin() { return reverse_iterator((_tree.size() ? _tree.maximum() : _tree._last()), _tree._last()); }
			reverse_iterator		rend() { return reverse_iterator(_tree._last(), _tree._last()); }
			const_reverse_iterator	rbegin() const { return const_reverse_iterator((_tree.size() ? _tree.maximum() : _tree._last()), _tree._last()); }
			const_reverse_iterator	rend() const { return const_reverse_iterator(_tree._last(), _tree._last()); }

			//				ELEMENT ACCESS
			mapped_type &operator[](const key_type &k)
			{
				iterator it = find(k);
				if (it != end())
					return (*it).second;
				else
				{
					insert(value_type(k, mapped_type()));
					return (*find(k)).second;
				}
			}

			//				MODIFIER
			void					clear() { _tree.clear(); }

			pair<iterator, bool>	insert(const value_type &val)
			{
				size_type		n = this->size();

				_tree.insert(val); // ICI 2
				pair<iterator, bool> ret;
				ret.second = (n != this->size());
				ret.first = iterator(this->_tree.find(val.first), this->_tree._last());
				return ret;
			}

			template <class InputIterator>
			void 					insert(InputIterator first, InputIterator last)
			{ for (; first != last; ++first) insert(*first); }

			iterator				insert(iterator position, const value_type &val)
			{ 
				iterator	last(position);

				if (value_comp()(*last, val) && value_comp()(val, *++position)) // insert using position as an hint
				{
					this->_tree.insert(val);
					return this->find(val.first);
				}
				return this->insert(val).first;
			}

			void					erase(iterator position) { _tree.erase((*position).first); }

			size_type erase(const key_type &k)
			{
				size_type i = this->size();
				if (!count(k))
					return 0;
				value_type data = *(find(k));
				_tree.erase(data.first);
				return (i != this->size());
			}

			void					erase(iterator first, iterator last)
			{
				iterator tmp;
				while (first != last)
				{
					tmp = first;
					++first;
					erase(tmp);
				}
			}

			void					swap(map &x) { _tree.swap(x._tree); }

			//				LOOKUP
			size_type								count(const key_type &k) const { return _tree.count(k); }

			pair<const_iterator, const_iterator>	equal_range(const key_type &k) const
			{
				for (const_iterator it = this->begin(); it != this->end(); it++)
					if (!this->_tree.key_comp()(k, it->first) && !this->_tree.key_comp()(it->first, k))
						return pair<const_iterator, const_iterator>(it++, it);
				return pair<const_iterator, const_iterator>(this->lower_bound(k), this->lower_bound(k));
			}

			pair<iterator, iterator>				equal_range(const key_type &k)
			{
				for (iterator it = this->begin(); it != this->end(); it++)
					if (!this->_tree.key_comp()(k, it->first) && !this->_tree.key_comp()(it->first, k))
						return pair<iterator, iterator>(it++, it);
				return pair<iterator, iterator>(this->lower_bound(k), this->lower_bound(k));
			}

			iterator								lower_bound(const key_type &k)
			{
				for (iterator it = begin(); it != end(); it++)
					if (!_tree.key_comp()((*it).first, k))
						return it;
				return end();
			}

			const_iterator							lower_bound(const key_type &k) const
			{
				for (const_iterator it = begin(); it != end(); it++)
					if (!_tree.key_comp()((*it).first, k))
						return it;
				return end();
			}

			const_iterator							upper_bound(const key_type &k) const
			{
				for (const_iterator it = begin(); it != end(); it++)
					if (_tree.key_comp()(k, (*it).first))
						return it;
				return end();
			}

			iterator								upper_bound(const key_type &k)
			{
				for (iterator it = begin(); it != end(); it++)
					if (_tree.key_comp()(k, (*it).first))
						return it;
				return end();
			}

			iterator								find(const key_type &k)
			{
				Node *tmp = _tree.find(k);
				if (tmp)
					return iterator(tmp, _tree._last());
				return end();
			}

			//					OBSERVER
			value_compare	value_comp() const { return this->_tree.value_comp(); }
			key_compare		key_comp() const { return _tree.key_comp(); }

		private:
			tree _tree;
	};
}