#pragma once

#include "Includes.hpp"

namespace ft { 

	template<class _Iterator>
		class tree_iterator {

			public:
				typedef _Iterator													value_type;
				typedef _Iterator&													reference;
				typedef _Iterator*													pointer;
				
				typedef typename ft::bidirectional_iterator_tag						iterator_category;
				typedef ptrdiff_t													difference_type;
				typedef size_t														size_type;
				
				typedef ft::s_Node<typename ft::remove_const<_Iterator>::type >*	node;		

			private:
				node		_current;
				node		nil_Node;

			public:

				tree_iterator() : _current(), nil_Node() {}

				tree_iterator(node __node, node __nil_Node) : _current(__node), nil_Node(__nil_Node) {}

				tree_iterator(const tree_iterator& copy) : _current(copy.base()), nil_Node(copy.getNilNode()) {}

				template<class T>
					tree_iterator(const tree_iterator<T>& other) : _current(other.base()), nil_Node(other.getNilNode()) {}

				virtual ~tree_iterator() {} 

				tree_iterator& operator=(const tree_iterator& other) {
					this->_current = other.base();
					this->nil_Node = other.getNilNode();
					return *this;
				}

				node		base() const {
					return this->_current;
				}

				node		getNilNode() const {
					return this->nil_Node;
				}

				reference	operator*() const {
					return (this->_current->value);
				}

				pointer		operator->() const {
					return &(this->_current->value);
				}

				tree_iterator&	operator++() {
					if (_current->right != nil_Node) {
						_current = _current->right;
						while (_current->left != nil_Node)
							_current = _current->left;
					} else {
						node y = _current->parent;
						while (y != nil_Node && _current == y->right) {
							_current = y;
							y = y->parent;
						}
						if (_current->right != y)
							_current = y;
					}
					return *this;
				}

				tree_iterator&	operator--() {
					if (_current->left != nil_Node) {
						_current = _current->left;
						while (_current->right != nil_Node)
							_current = _current->right;
					} else {
						node y = _current->parent;
						while (y != nil_Node && _current == y->left) {
							_current = y;
							y = y->parent;
						}
						if (_current->left != y)
							_current = y;
					}
					return *this;
				}

				tree_iterator	operator++(int) {
					tree_iterator tmp(*this);
					++(*this);
					return tmp;
				}

				tree_iterator	operator--(int) {
					tree_iterator tmp(*this);
					--(*this);
					return tmp;
				}

		};

		template<class _Iter1, class _Iter2>
		inline bool operator==(const tree_iterator<_Iter1> &lhs, const tree_iterator<_Iter2> &rhs) {
			return lhs.base() == rhs.base();
		}

		template<class _Iter1, class _Iter2>
		inline bool operator!=(const tree_iterator<_Iter1> &lhs, const tree_iterator<_Iter2> &rhs) {
			return lhs.base() != rhs.base();
		}

} //namespace ft end