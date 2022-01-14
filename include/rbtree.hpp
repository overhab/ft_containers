#pragma once

#include "Includes.hpp"

namespace ft {

	template<class T>
		struct s_Node {
			typedef T	value_type;
			typedef T*	pointer;
			typedef T&	reference;

			value_type	value;
			int 		color; // 1 - red, 0 - black
			s_Node<T>*	left;
			s_Node<T>*	right;
			s_Node<T>*	parent;

			s_Node() {
				color = 0;
				left = 0;
				right = 0;
				parent = 0;
			}

			s_Node(const T& val) : value(val) {
				color = 0;
				left = 0;
				right = 0;
				parent = 0;

				T::printPair(value); //checker
			}

			~s_Node() {}

		};


	//class Node = ft::s_Node<T>, 
	template<class key_type, class T, class Compare = std::less<key_type>, class A = std::allocator<ft::s_Node<T>> >
		class RBTree {
		private:
			typedef T										value_type;
			typedef ft::s_Node<T>							Node;
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


			pointer		create_node(const T& val) {
				pointer newNode;

				newNode = this->_alloc.allocate(1);

				this->_alloc.construct(newNode, Node(val));

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
					x->parent.right = y;
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
					x->parent.left = y;
				y->right = x;
				x->parent = y;
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

			void	insert(const T& val) {
				pointer		newNode;
				//pointer		prevNode;

				newNode = create_node(val);

				if (empty()) {
					root = newNode;
				} else {
					
					deleteElement(newNode); // placeholder
					




				}

			}

			void	deleteElement(const pointer& node) {
				this->_alloc.destroy(node);
				this->_alloc.deallocate(node, 1);
			}


			

		}; //RBTree class







} //namespace ft end
