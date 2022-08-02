/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:36:09 by amine             #+#    #+#             */
/*   Updated: 2022/08/02 18:18:38 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include "pair.hpp"

namespace ft
{
	template <class T, class Compare = std::less<typename T::first_type>, class Alloc = std::allocator<T> >
	class Tree
	{
		typedef	Alloc						allocator_type;
		typedef T							value_type;
		typedef typename T::first_type		key_type;
		typedef typename T::second_type		mapped_type;
		typedef Compare						key_compare;
		typedef ptrdiff_t					difference_type;
		typedef size_t						size_type;
		typedef T							&reference;
		typedef T							*pointer;

	public:

		struct Node
		{
			value_type	pair;
			Node		*parent;
			Node		*left;
			Node		*right;
			int			height;

			Node *max()
			{
				Node	*node = this;
				while (node->right != NULL)
					node = node->right;
				return (node);
			}
			Node *min()
			{
				Node	*node = this;
				while (node->left != NULL)
					node = node->left;
				return (node);
			}
		};
		//					CONSTRUCTOR
		// Default
		Tree(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _allocValue(alloc), _comp(comp)
		{
			_size = 0;
			_base = NULL;
			_end = _allocNode.allocate(1);
			set_end_node();
		}
		//	Copy
		Tree(const Tree &x)
			: _allocValue(x._allocValue), _allocNode(x._allocNode), _comp(x._comp)
		{
			_size = 0;
			_base = NULL;
			_end = _allocNode.allocate(1);
			set_end_node();
			*this = x;
		}
		//				DESTRUCTOR
		~Tree()
		{
			clear();
			_allocNode.deallocate(_end, 1);
		}

		//				ITERATOR
		Node *_last(void) const
		{
			set_end_node();
			return _end;
		}

		Node *root(void) const { return _base; }

		//				CAPACITY
		size_type size(void) const { return _size; }
		size_type max_size() const { return _allocNode.max_size(); }
		template <class U>
		const U &max(const U &i, const U &j) { return (i < j) ? j : i; }

		//				MODIFIER
		void insert(value_type type) { _base = insert(_base, type); }
		void erase(key_type key) { _base = erase(_base, key); }

		void clear()
		{
			while (_base)
				_base = erase(_base, _base->pair.first);
			set_end_node();
		}

		void swap(Tree &other)
		{
			Node *tmp = this->_base;
			this->_base = other._base;
			other._base = tmp;
		}

		size_type count(const key_type &key) const
		{
			Node *cur = _base;
			while (cur != nullptr)
			{
				if (_comp(key, cur->pair.first))
					cur = cur->left;
				else if (_comp(cur->pair.first, key))
					cur = cur->right;
				else
					return 1;
			}
			return 0;
		}

		//				ELEMENT ACCES
		key_compare		key_comp() const { return _comp; }
		allocator_type	get_allocator() const { return _allocValue; }
		Node			*find(key_type type) const { return searching(type); }
		Node *minimum(void) const { return (_size ? minValueNode(_base) : NULL); }

		Node *maximum(void) const { return (_size ? maxValueNode(_base) : NULL); }
		Node *maximum(Node *node1, Node *node2) const
		{ return (_size ? maxValueNode(node1, node2) : NULL); }

		//				ALLOCATION
		Node *maxValueNode(Node *node1, Node *node2) const
		{
			if (node1 == nullptr)
				return (node2);
			if (node2 == nullptr)
				return (node1);
			if (_comp(node1->pair.first, node2->pair.first))
				return (node2);
			return (node1);
		}

	private:
		int height(Node *node) const
		{
			if (!node)
				return (0);
			return (node->height);
		}

		Node *newNode(value_type pair, Node *parent) // allocate the new node containing ethe key & value
		{
			Node *node = _allocNode.allocate(1);
			_allocValue.construct(&node->pair, pair);
			node->left = NULL;
			node->right = NULL;
			node->height = 1;
			node->parent = parent;
			return (node);
		}

		Node *rightRotate(Node *old_p)
		{
			Node *new_p = old_p->left; // Left child is gonna be the new parrent
			Node *t_child = new_p->right; // new_p right is going to be transfered to old_p left

			new_p->parent = old_p->parent; // connects the subtree to the rest
			old_p->parent = new_p; // relinks the old_p with new_p
			if (t_child) // if new_p child exists
				t_child->parent = old_p; // reconnects it to his new parents
			new_p->right = old_p; // connects the new_p with his new right which is the old_parent
			old_p->left = t_child; // finishin transfer of right new parent with left old parrent
			// Calculate the new height
			old_p->height = height(old_p->left) < height(old_p->right) ? height(old_p->right) + 1 : height(old_p->left) + 1;
			new_p->height = height(new_p->left) < height(new_p->right) ? height(new_p->right) + 1 : height(new_p->left) + 1;
			return (new_p); // Return new_base
		}

		Node *leftRotate(Node *old_p)
		{
			Node *new_p = old_p->right;
			Node *t_child = new_p->left;

			new_p->parent = old_p->parent;
			old_p->parent = new_p;
			if (t_child != NULL)
				t_child->parent = old_p;
			new_p->left = old_p;
			old_p->right = t_child;
			old_p->height = height(old_p->left) < height(old_p->right) ? height(old_p->right) + 1 : height(old_p->left) + 1;
			new_p->height = height(new_p->left) < height(new_p->right) ? height(new_p->right) + 1 : height(new_p->left) + 1;
			return (new_p);
		}

		int getBalance(Node *node) const
		{
			if (!node)
				return (0);
			return (height(node->left) - height(node->right));
		}

		Node *searching(key_type key) const
		{
			Node *node = _base;
			while (node)
			{
				if (_comp(key, node->pair.first))
					node = node->left;
				else if (_comp(node->pair.first, key))
					node = node->right;
				else
					return (node);
			}
			return (NULL);
		}

		Node *insert(Node *node, value_type key, Node *parent = NULL)
		{
			int balance;

			if (!node) // node is base, creates and return new base
			{
				_size++;
				return (newNode(key, parent));
			}
			if (_comp(key.first, node->pair.first)) // reccursively travels to the correct end to insert
				node->left = insert(node->left, key, node);
			else if (_comp(node->pair.first, key.first))
				node->right = insert(node->right, key, node);
			else
				return (node);
			// Sets height of the new inserted node
			node->height = height(node->left) > height(node->right) ? height(node->left) : height(node->right);
			node->height++;
			balance = getBalance(node);
			// Check if the tree has become inbalance and correctly identifies which in balance and corrects it accordingly
			if (balance > 1 && _comp(key.first, node->left->pair.first)) // Left Left Case
				return rightRotate(node);
			if (balance < -1 && _comp(node->right->pair.first, key.first)) // Right Right Case
				return leftRotate(node);
			if (balance > 1 && _comp(node->left->pair.first, key.first)) // Left Right Case
			{
				node->left = leftRotate(node->left);
				return rightRotate(node);
			}
			if (balance < -1 && _comp(key.first, node->right->pair.first)) // Right Left Case
			{
				node->right = rightRotate(node->right);
				return leftRotate(node);
			}
			set_end_node();
			return (node);
		}

		Node *minValueNode(Node *node) const
		{
			Node	*parse = node;

			if (!node)
				return node;
			while (parse->left != NULL)
				parse = parse->left;
			return (parse);
		}

		Node *maxValueNode(Node *node) const
		{
			Node	*parse = node;

			if (!node)
				return NULL;
			while (parse->right != NULL)
				parse = parse->right;
			return (parse);
		}

		Node *erase(Node *node, key_type key)
		{
			int balance;
			Node *tmp;

			if (!node) // if tree is empty
				return node;
			if (_comp(key, node->pair.first)) // reccursively travels to the correct node
				node->left = erase(node->left, key);
			else if (_comp(node->pair.first, key))
				node->right = erase(node->right, key);
			else // Found the correct node
			{
				if ((node->left == NULL) || (node->right == NULL))
				{ // No and one child case
					tmp = node->right ? node->right : node->left;
					if (tmp == NULL)
					{ // No child
						tmp = node;
						node = NULL;
					}
					else // one child
						*node = *tmp;
					if (node)
						node->parent = tmp->parent;
					_allocValue.destroy(&tmp->pair);
					_allocNode.deallocate(tmp, 1);
					_size--;
				}
				else
				{ // Two child case
					tmp = minValueNode(node->right); // find the biggest from smaller side
					if (tmp != node->right)
					{ // relinks his right child to the new parrent
						tmp->right = node->right;
						node->right->parent = tmp;
					}
					if (tmp != node->left)
					{ // relinks his left child to the new parrent
						tmp->left = node->left;
						node->left->parent = tmp;
					}
					tmp->parent->left = 0;
					tmp->parent = node->parent;
					this->_allocValue.destroy(&node->pair);
					this->_allocNode.deallocate(node, 1);
					_size--;
					node = tmp;
				}
			}
			if (node == NULL) // if one node
				return node;

			node->height = 1 + _comp(height(node->left), height(node->right));
			balance = getBalance(node);
			// Check if the tree has become inbalance and correctly identifies which in balance and corrects it accordingly			
			if (balance > 1 && getBalance(node->left) >= 0) // Left Left Case
				return rightRotate(node);
			if (balance > 1 && getBalance(node->left) < 0) // Left Right Case
			{
				node->left = leftRotate(node->left);
				return rightRotate(node);
			}
			if (balance < -1 && getBalance(node->right) <= 0) // Right Right Case
				return leftRotate(node);
			if (balance < -1 && getBalance(node->right) > 0) // Right Left Case
			{
				node->right = rightRotate(node->right);
				return leftRotate(node);
			}
			return node;
		}

		void set_end_node(void) const
		{
			if (_size)
				_end->parent = maxValueNode(_base);
			else
				_end->parent = nullptr;
			_end->left = _end->right = nullptr;
		}

		class value_compare
		{
			friend class Tree;

			typedef bool			result_type;
			typedef value_type		first_type;
			typedef value_type		second_type;

			protected:
				Compare		comp;
				value_compare(key_compare c) : comp(c) {}

			public:
				bool operator()(const value_type &x, const value_type &y) const
				{ return comp(x.first, y.first); }
		};

		value_compare value_comp() const { return value_compare(this->_comp); }

	private:
		allocator_type			_allocValue;
		std::allocator<Node>	_allocNode;
		key_compare				_comp;
		size_type				_size;
		Node					*_base;
		Node					*_end;
	};
}
