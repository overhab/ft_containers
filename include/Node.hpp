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

		};

} //namespace ft end
