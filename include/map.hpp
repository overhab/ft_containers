#pragma once

#include "Includes.hpp"
#include <memory>

namespace ft {
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
		class map {
		public:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const key_type, mapped_type>	value_type;
			typedef Compare									key_compare;

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
			protected:
				key_compare comp;
			public:
				value_compare(key_compare pred) : comp(pred) {}
				bool operator()(const value_type& left, const value_type& right) const {
					return comp(left.first, right.first);
				}
			};

		private:							  
			typedef RBTree<key_type, value_type, value_compare>	tree_type;
			tree_type	_tree;

		public:
			typedef Alloc										allocator_type;
			typedef typename Alloc::pointer 					pointer;
			typedef typename Alloc::const_pointer				const_pointer;
			typedef typename Alloc::reference					reference;
			typedef typename Alloc::const_reference				const_reference;
			typedef typename tree_type::size_type				size_type;
			typedef typename tree_type::difference_type			difference_type;
	
			typedef typename tree_type::iterator				iterator;
			typedef typename tree_type::const_iterator			const_iterator;
			typedef typename tree_type::reverse_iterator		reverse_iterator;
			typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

			map() : _tree(value_compare(Compare())) {}

			allocator_type	get_allocator() const {
				return _tree.get_allocator();
			}

			bool empty() const { return _tree.size() == 0; }
			size_type size() const { return _tree.size(); }
			size_type max_size() const { return _tree.max_size(); }

			key_compare		key_comp() const {
				return this->comp;
			}

			value_compare	value_comp() const {
				return value_compare(_tree.key_comp());
			}

			iterator find(const key_type& k) {
				return _tree.find(value_type(k, T()));
			}

			const_iterator find(const key_type& k) const {
				return _tree.find(value_type(k, T()));
			}

			size_type count(const key_type& k) const {
				return _tree.count(value_type(k, T()));
			}

			iterator lower_bound(const key_type& k) {
				return _tree.lower_bound(value_type(k, T()));
			}

			const_iterator lower_bound(const key_type& k) const {
				return _tree.lower_bound(value_type(k, T()));
			}

			iterator upper_bound(const key_type& k) {
				return _tree.upper_bound(value_type(k, T()));
			}

			const_iterator upper_bound(const key_type& k) const {
				return _tree.upper_bound(value_type(k, T()));
			}

			pair<iterator,bool> insert(const value_type& val) {
				return _tree.insert(val);
			}

			iterator	insert(iterator position, const value_type& val) {
				return _tree.insert(position, val);
			}

		template <class InputIterator>
			void 	insert(InputIterator first, InputIterator last) {
				_tree.insert(first, last);
			}

			void	erase(iterator position) {
				_tree.erase(position);
			}

			size_type	erase(const key_type& k) {
				iterator __pos = find(k);
				if (__pos != end()) {
					erase(__pos);
					return 1;
				}
				return 0;
			}

			void erase (iterator first, iterator last) {
				for (; first != last; ++first)
					erase(*first);
			}

			iterator begin() {
				return _tree.begin();
			}

			iterator end() {
				return _tree.end();
			}

			const_iterator begin() const {
				return _tree.begin();
			}

			const_iterator end() const {
				return _tree.end();
			}

			reverse_iterator rbegin() {
				return _tree.rbegin();
			}

			reverse_iterator rend() {
				return _tree.rend();
			}

			const_reverse_iterator rbegin() const {
				return _tree.rbegin();
			}

			const_reverse_iterator rend() const {
				return _tree.rend();
			}




			void		printTree() const {
				_tree.printTree();
			}

		}; //class map end





} // namespace ft end
