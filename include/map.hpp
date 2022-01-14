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

		private:
			typedef RBTree<key_type, mapped_type, key_compare>	tree_type;

			tree_type	_tree;

		public:
			typedef Alloc									allocator_type;
			typedef typename Alloc::pointer 				pointer;
			typedef typename Alloc::const_pointer			const_pointer;
			typedef typename Alloc::reference				reference;
			typedef typename Alloc::const_reference			const_reference;
			typedef typename tree_type::size_type			size_type;
			typedef typename tree_type::difference_type		difference_type;

			
		


		}; //class map end





} // namespace ft end
