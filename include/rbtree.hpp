#pragma once

#include "Includes.hpp"
#include "tree_iterator.hpp"

namespace ft {

	template<class key_type, class T, class Compare = std::less<key_type>, class A = std::allocator<ft::s_Node<T> > >
		class RBTree {
		public:
			typedef T										value_type;
			typedef ft::s_Node<T>							Node;
			typedef std::allocator<T>						value_alloc;
			typedef Compare									key_compare;
			typedef A										allocator_type;
			typedef typename A::pointer 					pointer;
			typedef typename A::const_pointer				const_pointer;
			typedef typename A::reference					reference;
			typedef typename A::const_reference				const_reference;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef ft::tree_iterator<value_type>			iterator;
			typedef ft::const_tree_iterator<value_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			size_type			__size;
			value_alloc			__val_alloc;
			pointer				root;
			pointer				nil_Node;
			allocator_type		_alloc;
			key_compare			__comp;

			pointer		create_node(const T& val, bool empty) {
				pointer newNode;

				newNode = this->_alloc.allocate(1);
			
				this->__val_alloc.construct(&newNode->value, val);
				newNode->color = false;
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

			void	transplant(pointer x, pointer y) {
				if (x->parent == nil_Node)
					root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->parent = x->parent;
			}

			pointer tree_minimum(pointer __x) const {
				while (__x != NULL && __x->left != nil_Node)
					__x = __x->left;
				return __x;
			}

			pointer tree_maximum(pointer __x) const {
				while (__x != NULL && __x->right != nil_Node)
					__x = __x->right;
				return __x;
			}

			void	deleteFix(pointer x) {
				pointer w;

				while (x != nil_Node && x->color == false) {
					if (x == x->parent->left) {
						w = x->parent->right;
						if (w->color == true) {
							w->color = false;
							x->parent->color = true;
							left_rotation(x->parent);
							w = x->parent->right;
						}
						if (w->left->color == false && w->right->color == false) {
							w->color = true;
							x = x->parent;
						} else {
							if (w->right->color == false) {
								w->left->color = false;
								w->color = true;
								right_rotation(w);
								w = x->parent->right;
							}
							w->color = x->parent->color;
							x->parent->color = false;
							w->right->color = false;
							left_rotation(x->parent);
							x = root;
						}
					} else {
						w = x->parent->left;
						if (w->color == true) {
							w->color = false;
							x->parent->color = true;
							left_rotation(x->parent);
							w = x->parent->left;
						}
						if (w->right->color == false && w->left->color == false) {
							w->color = true;
							x = x->parent;
						} else {
							if (w->left->color == false) {
								w->right->color = false;
								w->color = true;
								right_rotation(w);
								w = x->parent->left;
							}
							w->color = x->parent->color;
							x->parent->color = false;
							w->left->color = false;
							left_rotation(x->parent);
							x = root;
						}
					}
				}
				x->color = false;
			}

		public:
			/**
			 * CONSTRUCTORS
			 */
			RBTree() : __size(0) {
				nil_Node = this->_alloc.allocate(1);
				//this->_alloc.construct(nil_Node, Node());
				root = nil_Node;
				nil_Node->left = root;
				nil_Node->right = root;
				root->left = nil_Node;
				root->right = nil_Node;
			}

			RBTree(const Compare& comp) : __size(0), __comp(comp) {
				nil_Node = this->_alloc.allocate(1);
				//this->_alloc.construct(nil_Node, Node());
				root = nil_Node;
				nil_Node->left = root;
				nil_Node->right = root;
				root->left = nil_Node;
				root->right = nil_Node;
			}

			~RBTree() {
				this->_alloc.deallocate(nil_Node, 1);
			}

			key_compare		key_comp() const { return __comp;}

			bool 	empty() const { return this->size() == 0; }

			size_type	size() const { return this->__size;}
			size_type	max_size() const { 
				return this->_alloc.max_size();
			}

			allocator_type	get_allocator() const {
				return this->_alloc;
			}

			ft::pair<iterator, bool>	insert(const T& val, pointer __pos = NULL) {
				if (__pos == NULL) {
					__pos = root;
				}
				pointer		newNode;
				ft::pair<iterator, bool> ins;

				newNode = create_node(val, empty());

				if (empty()) {
					root = newNode;
					ins = ft::pair<iterator, bool>(iterator(root, nil_Node), true);
				} else {
					pointer y = nil_Node;
					pointer x = __pos;
					while (x != nil_Node) {
						y = x;
						if (val.first == x->value.first) { //compare keys
							this->deleteElement(newNode);
							return ft::pair<iterator, bool>(iterator(x, nil_Node), false);
						}
						else if (__comp(newNode->value, x->value))
							x = x->left;
						else 
							x = x->right;
					}
					newNode->parent = y;
					if (y == nil_Node)
						root = newNode;
					else if (__comp(newNode->value, y->value))
						y->left = newNode;
					else
						y->right = newNode;
					ins = ft::pair<iterator, bool>(iterator(newNode, nil_Node), true);
					insert_fixup(newNode);
				}
				nil_Node->left = root; // for end()
				nil_Node->right = root;
				nil_Node->parent = nil_Node;
				root->parent = nil_Node;
				__size++;
				return ins;

			}

			iterator insert(iterator position, const T& val) {

				(void)position;
				return (this->insert(val)).first;

				/* iterator ret;

				if (position == begin()) {
					if (position != end() && __comp(val, (*position)))
						ret = (this->insert(val, position.base())).first;
					else 
						ret = (this->insert(val)).first;
				} else if (position == end()) {
					if (position != begin() && __comp((*position), val))
						ret = (this->insert(val, (position.base() - 1))).first;
					else 
						ret = (this->insert(val)).first;
				} 
				else 
					ret = (this->insert(val)).first;
				return ret; */
			}

		template <class InputIterator>
  			void	insert(InputIterator first, InputIterator last) {
				for (; first != last; ++first) {
					this->insert(*first);
				}
			}

			iterator lower_bound(const T& k) {
				for (iterator it = this->begin(); it != this->end(); ++it) {
					if (!__comp(*it, k))
						return it;
				}
				return this->end();
			}

			const_iterator lower_bound(const T& k) const {
				for (const_iterator it = this->begin(); it != this->end(); ++it) {
					if (!__comp(*it, k))
						return it;
				}
				return this->end();
			}

			iterator upper_bound(const T& k) {
				for (iterator it = this->begin(); it != this->end(); ++it) {
					if (__comp(k, *it))
						return it;
				}
				return this->end();
			}

			const_iterator upper_bound(const T& k) const {
				for (const_iterator it = this->begin(); it != this->end(); ++it) {
					if (__comp(k, *it))
						return it;
				}
				return this->end();
			}

			size_type	count(const T& k) const {
				pointer tmp = root;

				while (tmp != nil_Node) {
					if (__comp(tmp->value, k))
						tmp = tmp->right;
					else if (__comp(k, tmp->value))
						tmp = tmp->left;
					else
						return 1;
				}
				return 0;
			}

			iterator	find(const T& k) {
				pointer tmp = root;

				while (tmp != nil_Node) {
					if (__comp(tmp->value, k))
						tmp = tmp->right;
					else if (__comp(k, tmp->value))
						tmp = tmp->left;
					else
						return iterator(tmp, nil_Node);
				}
				return this->end();
			}

			const_iterator	find(const T& k) const {
				pointer tmp = root;
				
				while (tmp != nil_Node) {
					if (__comp(tmp->value, k))
						tmp = tmp->right;
					else if (__comp(k, tmp->value))
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

			void erase(iterator position) {
				if (__size == 0)
					return ;
				pointer z = position.base(), x, y, to_delete = z;
				
				y = z;
				bool y_original_color = y->color;
				if (z->left == nil_Node) {
					x = z->right;
					transplant(z, z->right);
				} else if (z->right == nil_Node) {
					x = z->left;
					transplant(z, z->left);
				} else {
					y = tree_minimum(z->right);
					y_original_color = y->color;
					x = y->right;
					if (y->parent == z)
						x->parent = y;
					else {
						transplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					transplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				deleteElement(to_delete);
				if (y_original_color == false)
					deleteFix(x);
				__size--;
				if (__size == 0)
					root = nil_Node;
				nil_Node->parent = nil_Node;
				nil_Node->left = root; // for end()
				nil_Node->right = root;
				root->parent = nil_Node;
			}

			void	swap(RBTree& x) {
				ft::my_swap(this->nil_Node, x.nil_Node);
				ft::my_swap(this->root, x.root);
				ft::my_swap(this->__size, x.__size);
			}
			
			/* void	printTree(pointer node = NULL, bool __isroot = true, bool __isLeft = false) const {
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
			} */

			void	deleteElement(const pointer& node) {
				this->__val_alloc.destroy(&node->value);
				this->_alloc.deallocate(node, 1);
			}

		}; //RBTree class

	
		template<class key_type, class T, class Compare>
		inline bool operator<(const RBTree<key_type, T, Compare>& lhs,  const RBTree<key_type, T, Compare>& rhs){
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
		
		template<class key_type, class T, class Compare>
		inline bool operator>(const RBTree<key_type, T, Compare>& lhs,  const RBTree<key_type, T, Compare>& rhs){
			return (lhs < rhs);
		}
		
		
		template<class key_type, class T, class Compare>
		inline bool operator==(const RBTree<key_type, T, Compare>& lhs, const RBTree<key_type, T, Compare>& rhs){
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}
		
		template<class key_type, class T, class Compare>
		void swap(const  RBTree<key_type, T, Compare>& lhs, const  RBTree<key_type, T, Compare>& rhs){
			lhs.swap(rhs);
		}


} //namespace ft end
