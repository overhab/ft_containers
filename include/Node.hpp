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
			bool		nil;
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



} //namespace ft end