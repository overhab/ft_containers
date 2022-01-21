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
				
				typedef ft::s_Node<_Iterator>*	node;

			private:
				node		_current;
				node		nil_Node;

			public:

				tree_iterator() : _current(), nil_Node() {}

				tree_iterator(node __node, node __nil_Node) : _current(__node), nil_Node(__nil_Node) {}

				tree_iterator(const tree_iterator& copy) : _current(copy._current), nil_Node(copy.nil_Node) {}

				~tree_iterator() {} 

				tree_iterator& operator=(const tree_iterator& other) {
					this->_current = other._current;
					this->nil_Node = other.nil_Node;
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

				bool
      			operator==(const tree_iterator& __x) const
      			{ return _current == __x._current; }

      			bool
      			operator!=(const tree_iterator& __x) const
      			{ return _current != __x._current; }

		};

		template<class _Iterator>
		class const_tree_iterator {

			public:
				typedef _Iterator													value_type;
				typedef const _Iterator&											reference;
				typedef const _Iterator*											pointer;

				typedef tree_iterator<_Iterator>	iterator;
				
				typedef typename ft::bidirectional_iterator_tag						iterator_category;
				typedef ptrdiff_t													difference_type;
				typedef size_t														size_type;
				
				typedef ft::s_Node<_Iterator>*	node;	

			private:
				node		_current;
				node		nil_Node;

			public:

				const_tree_iterator() : _current(), nil_Node() {}

				const_tree_iterator(node __node, node __nil_Node) : _current(__node), nil_Node(__nil_Node) {}

				const_tree_iterator(const const_tree_iterator& copy) : _current(copy._current), nil_Node(copy.nil_Node) {}

				const_tree_iterator(const iterator& other) : _current(other.base()), nil_Node(other.getNilNode()) {}

				~const_tree_iterator() {} 

				const_tree_iterator& operator=(const const_tree_iterator& other) {
					this->_current = other._current;
					this->nil_Node = other.nil_Node;
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

				const_tree_iterator&	operator++() {
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
						_current = y;
					}
					return *this;
				}

				const_tree_iterator&	operator--() {		
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
						_current = y;
					}
					return *this;
				}

				const_tree_iterator	operator++(int) {
					const_tree_iterator tmp(*this);
					++(*this);
					return tmp;
				}

				const_tree_iterator	operator--(int) {
					const_tree_iterator tmp(*this);
					--(*this);
					return tmp;
				}

				bool
      			operator==(const const_tree_iterator& __x) const
      			{ return _current == __x._current; }

      			bool
      			operator!=(const const_tree_iterator& __x) const
      			{ return _current != __x._current; }

		};

		template<class _Iter1>
		bool operator==(const tree_iterator<_Iter1> &lhs, const const_tree_iterator<_Iter1> &rhs) {
			return lhs.base() == rhs.base();
		}

		template<class _Iter1>
		bool operator!=(const tree_iterator<_Iter1> &lhs, const const_tree_iterator<_Iter1> &rhs) {
			return lhs.base() != rhs.base();
		}

} //namespace ft end
