#pragma once

#include "Includes.hpp"

namespace ft {

	/*
	**	INTEGRAL_CONSTANT, IS_INTEGRAL
	*/
	template<class T, T v>
		struct integral_constant {
			static const T value = v;
		};
	
	struct true_type : public integral_constant<bool, true> {};
	struct false_type : public integral_constant<bool, false> {};

	template<class T>
		struct is_integral : public false_type {};
	template<class T>
		struct is_integral<const T> : public is_integral<T> {};
	template<>
		struct is_integral<bool> : public true_type {};
	template<>
		struct is_integral<unsigned char> : public true_type {};
	template<>
		struct is_integral<unsigned short> : public true_type {};
	template<>
		struct is_integral<unsigned int> : public true_type {};
	template<>
		struct is_integral<unsigned long> : public true_type {};
	template<>
		struct is_integral<signed char> : public true_type {};
	template<>
		struct is_integral<char> : public true_type {};
	template<>
		struct is_integral<short> : public true_type {};
	template<>
		struct is_integral<int> : public true_type {};
	template<>
		struct is_integral<long> : public true_type {};

	/*
	** ENABLE_IF
	*/
	template<bool B, class T = void>
		struct enable_if {};
	
	template<class T>
		struct enable_if<true, T> {
			typedef T type; 
		};
		
} //namespace ft end