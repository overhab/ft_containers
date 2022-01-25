#pragma once

#include "Includes.hpp"


namespace ft {

	enum tree_color { _BLACK = false, _RED = true };

	template<class T>
		struct s_Node {
			typedef T				value_type;
			typedef value_type*		pointer;
			typedef value_type&		reference;
			typedef s_Node*			ptr;

			value_type	value;
			tree_color 	color;
			ptr			left;
			ptr			right;
			ptr			parent;

		};

} //namespace ft end
