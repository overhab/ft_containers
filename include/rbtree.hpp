#pragma once

#include "Includes.hpp"


namespace ft {

	template<class T>
		struct s_Node {
			typedef T	value_type;
			typedef T*	pointer;
			typedef T&	reference;

			value_type	value;
			bool 		color; // true - red, false - black
			s_Node<T>*	left;
			s_Node<T>*	right;
			s_Node<T>*	parent;

			s_Node() {
				color = false;
				left = 0;
				right = 0;
				parent = 0;
			}

			s_Node(const T& val) : value(val) {
				color = false;
				left = 0;
				right = 0;
				parent = 0;

				//T::printPair(value); //checker
			}

			~s_Node() {}

		};

	template<class key_type, class T, class Compare = std::less<key_type>, class A = std::allocator<ft::s_Node<T> > >
		class RBTree {
		private:
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
						} else if (z == z->parent->right) {
							z = z->parent;
							left_rotation(z);
						}
						z->parent->color = false;
						z->parent->parent->color = true;
						right_rotation(z->parent->parent);
					} else { // same as previous but change 'right' to 'left' and vice versa
						y = z->parent->parent->left;
						if (y->color == true) {
							z->parent->color = false;
							y->color = false;
							z->parent->parent->color = true;
							z = z->parent->parent;
						} else if (z == z->parent->left) {
							z = z->parent;
							right_rotation(z);
						}
						z->parent->color = false;
						z->parent->parent->color = true;
						left_rotation(z->parent->parent);
					}
				}
				root->color = false;
			}

		public:
			/**
			 * CONSTRUCTORS
			 */
			RBTree() {
				nil_Node = this->_alloc.allocate(1);
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

			bool 	empty() { return root == nil_Node; }

			allocator_type	get_allocator() const {
				return this->_alloc;
			}

			// ft::pair<iterator, bool>
			void	insert(const T& val) {
				pointer		newNode;

				newNode = create_node(val, empty());

				if (empty()) {
					root = newNode;
				} else {
					pointer y = nil_Node;
					pointer x = root;
					while (x != nil_Node) {
						y = x;
						if (val.first == x->value.first) { //compare keys
							x->value.second = val.second;

							std::cout << "same key" << std::endl;

							return ; //ft::pair<iterator, false>
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

					newNode->left = nil_Node; // no need, leave for now
					newNode->right = nil_Node;
					newNode->color = true;

					insert_fixup(newNode);
					//deleteElement(newNode); // placeholder
				}

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
					//std::cout << "check" << std::endl;
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


			

		}; //RBTree class







} //namespace ft end
