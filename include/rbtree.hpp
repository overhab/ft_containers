#pragma once

#include "Includes.hpp"
#include "tree_iterator.hpp"

namespace ft {

	template<class key_type, class T, class Compare = std::less<key_type>, class A = std::allocator<ft::s_Node<T> > >
		class RBTree {
		public:
			typedef T										value_type;
			typedef ft::s_Node<T>							Node;
			typedef Compare									key_compare;
			typedef A										allocator_type;
			typedef typename A::pointer 					pointer;
			typedef typename A::const_pointer				const_pointer;
			typedef typename A::reference					reference;
			typedef typename A::const_reference				const_reference;
			typedef std::size_t								size_type;
			typedef ptrdiff_t								difference_type;
			typedef ft::tree_iterator<value_type>			iterator;
			typedef ft::tree_iterator<const value_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			size_type			__size;

			pointer				root;
			pointer				nil_Node;
			allocator_type		_alloc;
			key_compare			__comp;



			pointer		create_node(const T& val, bool empty) {
				pointer newNode;

				newNode = this->_alloc.allocate(1);
			
				this->_alloc.construct(newNode, Node(val));
				if (empty == false)
					newNode->color = true;
				newNode->parent = nil_Node;
				newNode->left = nil_Node;
				newNode->right = nil_Node;

				return newNode;
			}

			void	left_rotation(pointer x) {
				

				pointer y = x->right;
				x->right = y->left;

				if (y->left != nil_Node)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == nil_Node)
					root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else 
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void	right_rotation(pointer x) {


				pointer y = x->left;
				x->left = y->right;

				if (y->right != nil_Node)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == nil_Node)
					root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else 
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			void	insert_fixup(pointer z) {
				pointer y;
				
				while (z->parent->color == true){
					if (z->parent == z->parent->parent->left) {
						y = z->parent->parent->right;
						if (y->color == true) {
							z->parent->color = false;
							y->color = false;
							z->parent->parent->color = true;
							z = z->parent->parent;
						} else {
							if (z == z->parent->right) {
								z = z->parent;
								left_rotation(z);
							}
							z->parent->color = false;
							z->parent->parent->color = true;
							right_rotation(z->parent->parent);
						}
					} else { // same as previous but change 'right' to 'left' and vice versa
						y = z->parent->parent->left;
						if (y->color == true) {
							z->parent->color = false;
							y->color = false;
							z->parent->parent->color = true;
							z = z->parent->parent;
						} else {
							if (z == z->parent->left) {
								z = z->parent;
								right_rotation(z);
							}
							z->parent->color = false;
							z->parent->parent->color = true;
							left_rotation(z->parent->parent);
						}
					}
				}
				root->color = false;
			}

		public:
			/**
			 * CONSTRUCTORS
			 */
			RBTree() : __size(0) {
				nil_Node = this->_alloc.allocate(1);
				this->_alloc.construct(nil_Node, Node());
				root = nil_Node;
				root->left = nil_Node;
				root->right = nil_Node;
			}

			~RBTree() {
				//add clear_tree();
				this->_alloc.deallocate(nil_Node, 1);
				this->_alloc.destroy(root);
				this->_alloc.deallocate(root, 1);
			}

			key_compare		key_comp() const { return __comp;}

			bool 	empty() const { return this->size() == 0; } // change to this->size() == 0;

			size_type	size() const { return this->__size;}
			size_type	max_size() const { return this->_alloc.max_size();}

			allocator_type	get_allocator() const {
				return this->_alloc;
			}

			ft::pair<iterator, bool>	insert(const T& val) {
				pointer		newNode;
				ft::pair<iterator, bool> ins;

				newNode = create_node(val, empty());

				if (empty()) {
					root = newNode;
					ins = ft::pair<iterator, bool>(iterator(root, nil_Node), true);
				} else {
					pointer y = nil_Node;
					pointer x = root;
					while (x != nil_Node) {
						y = x;
						if (val.first == x->value.first) { //compare keys
							return ft::pair<iterator, bool>(iterator(x, nil_Node), false);
						}
						else if (__comp(newNode->value.first, x->value.first))
							x = x->left;
						else 
							x = x->right;
					}
					newNode->parent = y;
					if (y == nil_Node)
						root = newNode;
					else if (__comp(newNode->value.first, y->value.first))
						y->left = newNode;
					else
						y->right = newNode;
					ins = ft::pair<iterator, bool>(iterator(root, nil_Node), true);
					insert_fixup(newNode);
				}
				nil_Node->left = root; // for end()
				nil_Node->right = root; // for end()
				__size++;
				return ins;

			}

			iterator lower_bound (const key_type& k) {
				for (iterator it = this->begin(); it != this->end(); ++it) {
					if (!__comp(it->first, k))
						return it;
				}
				return this->end();
			}

			const_iterator lower_bound (const key_type& k) const {
				for (const_iterator it = this->begin(); it != this->end(); ++it) {
					if (!__comp(it->first, k))
						return it;
				}
				return this->end();
			}

			iterator upper_bound (const key_type& k) {
				for (iterator it = this->begin(); it != this->end(); ++it) {
					if (__comp(k, it->first))
						return it;
				}
				return this->end();
			}

			const_iterator upper_bound (const key_type& k) const {
				for (const_iterator it = this->begin(); it != this->end(); ++it) {
					if (__comp(k, it->first))
						return it;
				}
				return this->end();
			}

			size_type	count(const key_type& k) const {
				pointer tmp = root;

				while (tmp != nil_Node) {
					if (__comp(tmp->value.first, k))
						tmp = tmp->right;
					else if (__comp(k, tmp->value.first))
						tmp = tmp->left;
					else
						return 1;
				}
				return 0;
			}

			iterator	find(const key_type& k) {
				pointer tmp = root;

				while (tmp != nil_Node) {
					if (__comp(tmp->value.first, k))
						tmp = tmp->right;
					else if (__comp(k, tmp->value.first))
						tmp = tmp->left;
					else
						return iterator(tmp, nil_Node);
				}
				return this->end();
			}

			const_iterator	find(const key_type& k) const {
				pointer tmp = root;
				
				while (tmp != nil_Node) {
					if (__comp(tmp->value.first, k))
						tmp = tmp->right;
					else if (__comp(k, tmp->value.first))
						tmp = tmp->left;
					else
						return const_iterator(tmp, nil_Node);
				}
				return this->end();
			}

			iterator begin() {
				pointer tmp = root;
				while (tmp->left != nil_Node)
					tmp = tmp->left;
				return iterator(tmp, nil_Node);
			}

			iterator end() {
				return iterator(nil_Node, nil_Node);
			}

			const_iterator begin() const {
				pointer tmp = root;
				while (tmp->left != nil_Node)
					tmp = tmp->left;
				return const_iterator(tmp, nil_Node);
			}

			const_iterator end() const {
				return const_iterator(nil_Node, nil_Node);
			}

			reverse_iterator rbegin() {
				return reverse_iterator(end());
			}

			reverse_iterator rend() {
				return reverse_iterator(begin());
			}

			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(end());
			}

			const_reverse_iterator rend() const {
				return const_reverse_iterator(begin());
			}
			
			void	printTree(pointer node = NULL, bool __isroot = true, bool __isLeft = false) {
				if (__isroot)
					node = root;
				if (node == nil_Node) {
					std::cout << "nil node " << node->color << std::endl;
					return ;
				}
				if (__isroot) {
					std::cout << "root: color = " << node->color << "\n";
					T::printPair(node->value);
					printTree(node->left, false, true);
					printTree(node->right, false, false);
				} else if (__isLeft) {
					std::cout << "left: color = " << node->color << "\n";
					T::printPair(node->value);
					printTree(node->left, false, true);
					printTree(node->right, false, false);
				} else {
					std::cout << "right: color = " << node->color << "\n";
					T::printPair(node->value);
					printTree(node->left, false, true);
					printTree(node->right, false, false);
				}
			}

/* 			void insert_into_tree(pointer z) {

			} */

			void	deleteElement(const pointer& node) {
				this->_alloc.destroy(node);
				this->_alloc.deallocate(node, 1);
			}

			void		iterator_test() const {
				iterator it(root, nil_Node);
				
				value_type::printPair(*it);
				it->second = 100100;
				std::cout << it->second << std::endl;

			}

		}; //RBTree class







} //namespace ft end
