#pragma once

#include "Includes.hpp"

namespace ft{ 

	template<class T>
		std::string my_to_string(T arg) {
			std::stringstream ss;

			ss << arg;
			return ss.str();
		}



} //namespace ft end