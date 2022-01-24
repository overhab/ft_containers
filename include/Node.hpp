#pragma once

#include "Includes.hpp"

namespace ft {

	template<class T>
		struct s_Node {
			typedef T	value_type;

			value_type	value;
			bool 		color; // true - red, false - black
			s_Node<T>*	left;
			s_Node<T>*	right;
			s_Node<T>*	parent;

			s_Node() {
				color = false;
				right = 0;
				left = 0;
				parent = 0;
			}

			s_Node(const value_type& val) : value(val) {
				color = false;
				right = 0;
				left = 0;
				parent = 0;
			}

		};

} //namespace ft end
