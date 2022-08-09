/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:46:37 by amine             #+#    #+#             */
/*   Updated: 2022/08/09 11:53:51 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
//#include "../utils/iterator_traits.hpp"

namespace ft
{
	template <class Category, class T, class notconst_T = T>
	class map_iterator
	{
		public:
			typedef typename T::value_type		value_type;
			typedef typename notconst_T::Node	Node;
			typedef typename T::key_type		key_type;
			typedef typename T::mapped_type		mapped_type;
			typedef typename T::key_compare		key_compare;
			typedef typename T::pointer			pointer;
			typedef typename T::reference		reference;
			typedef ptrdiff_t					difference_type;
			typedef Category					iterator_category;

			map_iterator() {}
			map_iterator(const map_iterator<Category, notconst_T> &toCopy) : _begin(toCopy.base()), _end(toCopy.end()) {}
			map_iterator(Node *node, Node *end) : _begin(node), _end(end) {}

			virtual ~map_iterator() {}

			Node *base() const { return _begin; }
			Node *end() const { return _end; }

			bool operator!=(const map_iterator<Category, T, notconst_T> &rhs) const
			{ return this->_begin != rhs._begin; }

			bool operator==(const map_iterator<Category, T, notconst_T> &rhs) const
			{ return this->_begin == rhs._begin; }

			reference operator*() const { return this->_begin->pair; }

			pointer operator->() const
			{
				if (this->_begin == nullptr)
					return nullptr;
				return &(operator*)();
			}

			map_iterator &operator++()
			{
				key_type		key;
				Node			*tmp;

				if (this->_begin->right)
				{
					this->_begin = this->_begin->right->min();
					return *this;
				}
				else if (this->_begin->parent)
				{
					key = this->_begin->pair.first;
					tmp = this->_begin->parent;
					while (tmp && this->_comp(tmp->pair.first, key))
						tmp = tmp->parent;
					if (tmp)
					{
						this->_begin = tmp;
						return *this;
					}
				}
				this->_begin = this->_end;
				return *this;
			}

			map_iterator &operator--()
			{
				key_type		key;
				Node			*tmp;

				if (this->_begin->left)
				{
					this->_begin = this->_begin->left->max();
					return *this;
				}
				else if (this->_begin->parent)
				{
					key = this->_begin->pair.first;
					tmp = this->_begin->parent;
					while (tmp && this->_comp(key, tmp->pair.first))
						tmp = tmp->parent;
					if (tmp)
					{
						this->_begin = tmp;
						return *this;
					}
				}
				this->_begin = this->_end;
				return *this;
			}

			map_iterator operator++(int)
			{
				map_iterator	tmp = *this;
				++*this;
				return tmp;
			}

			map_iterator operator--(int)
			{
				map_iterator	tmp = *this;
				--*this;
				return tmp;
			}

		private:
			Node			*_begin;
			Node			*_end;
			key_compare		_comp;
	};

	template <class Category, class T, class notconst_T = T>
	class reverse_map_iterator
	{
		public:
			typedef typename T::value_type		value_type;
			typedef typename notconst_T::Node	Node;
			typedef typename T::key_type		key_type;
			typedef typename T::mapped_type		mapped_type;
			typedef typename T::key_compare		key_compare;
			typedef typename T::pointer			pointer;
			typedef typename T::reference		reference;
			typedef ptrdiff_t					difference_type;
			typedef Category					iterator_category;

			reverse_map_iterator() {}
			reverse_map_iterator(const reverse_map_iterator<Category, notconst_T> &toCopy) : _begin(toCopy.base()), _end(toCopy.end()) {}
			reverse_map_iterator(Node *node, Node *end)
			{
				this->_begin = node;
				this->_end = end;
			}

			Node *base() const { return this->_begin; }
			Node *end() const { return this->_end; }

			virtual ~reverse_map_iterator() {}

			reference operator*() const { return this->_begin->pair; }

			bool operator!=(const reverse_map_iterator<Category, T, notconst_T> &other) const
			{
				return this->_begin != other._begin;
			}

			bool operator==(const reverse_map_iterator<Category, T, notconst_T> &other) const
			{
				return this->_begin == other._begin;
			}

			pointer operator->() const
			{
				if (this->_begin == nullptr)
					return nullptr;
				return &(operator*)();
			}

			map_iterator &operator++()
			{
				key_type		key;
				Node			*tmp;

				if (this->_begin->right)
				{
					this->_begin = this->_begin->right->min();
					return *this;
				}
				else if (this->_begin->parent)
				{
					key = this->_begin->pair.first;
					tmp = this->_begin->parent;
					while (tmp && this->_comp(tmp->pair.first, key))
						tmp = tmp->parent;
					if (tmp)
					{
						this->_begin = tmp;
						return *this;
					}
				}
				this->_begin = this->_end;
				return *this;
			}

			map_iterator &operator--()
			{
				key_type		key;
				Node			*tmp;

				if (this->_begin->left)
				{
					this->_begin = this->_begin->left->max();
					return *this;
				}
				else if (this->_begin->parent)
				{
					key = this->_begin->pair.first;
					tmp = this->_begin->parent;
					while (tmp && this->_comp(key, tmp->pair.first))
						tmp = tmp->parent;
					if (tmp)
					{
						this->_begin = tmp;
						return *this;
					}
				}
				this->_begin = this->_end;
				return *this;
			}

			reverse_map_iterator operator++(int)
			{
				reverse_map_iterator tmp = *this;
				++*this;
				return tmp;
			}
			reverse_map_iterator operator--(int)
			{
				reverse_map_iterator tmp = *this;
				--*this;
				return tmp;
			}

		private:
			Node			*_begin;
			Node			*_end;
			key_compare		_comp;
	};
}