#pragma once

#include "Includes.hpp"

namespace ft {

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
		struct iterator {
	    	typedef T         value_type;
	    	typedef Distance  difference_type;
	    	typedef Pointer   pointer;
	    	typedef Reference reference;
	    	typedef Category  iterator_category;
	  };

	struct output_iterator_tag {};

	struct input_iterator_tag {};

	struct forward_iterator_tag : public input_iterator_tag {};

	struct bidirectional_iterator_tag : public forward_iterator_tag {};

	struct random_access_iterator_tag : public bidirectional_iterator_tag {};


	template <class It>
		struct iterator_traits {
			typedef typename It::iterator_category	iterator_category;
			typedef typename It::value_type 		value_type;
			typedef typename It::difference_type		difference_type;
			typedef typename It::reference 			reference;
			typedef typename It::pointer 			pointer;
		};
	
	template <class T>
		struct iterator_traits<T *> {
			typedef ft::random_access_iterator_tag 	iterator_category;
			typedef T 								value_type;
			typedef std::ptrdiff_t 					difference_type;
			typedef T 								*pointer;
			typedef T& 								reference;
		};

	template <class T>
		struct iterator_traits<const T *> {
			typedef ft::random_access_iterator_tag 	iterator_category;
			typedef T 								value_type;
			typedef std::ptrdiff_t 					difference_type;
			typedef T 								*pointer;
			typedef T& 								reference;
		};

} //namespace ft end