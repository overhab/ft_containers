#pragma once 

#include "Includes.hpp"

namespace ft {

	template <class T1, class T2>
		struct pair {
			typedef T1 first_type;
			typedef T2 second_type;

			first_type	first;
			second_type	second;

			pair() : first(), second() {}

			template<class U, class V> 
				pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

			pair (const first_type& a, const second_type& b) : first(a), second(b) {}

			pair& operator=(const pair& pr) {
				if ((*this) == pr)
					return *this;
				this->first = pr.first;
				this->second = pr.second;
				return *this; 
			}

			virtual ~pair() {}


			/**
			 * DELETE AT THE END
			 */
			template<class F, class S>
				static void printPair(const pair<F, S>& pr) { std::cout << pr.first << " " << pr.second
					<< std::endl; }
			/** 
			 * DELETE AT THE END
			 */

		};
	
		template <class T1, class T2>
			bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
				return ((lhs.first == rhs.first) && (lhs.second == rhs.second));
			}

		template <class T1, class T2>
			bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
				return !(lhs == rhs);
			}

		template <class T1, class T2>
			bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
				return (lhs.first < rhs.first || (!(rhs.first < lhs.first) 
					&& lhs.second < rhs.second));
			}

		template <class T1, class T2>
			bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
				return !(rhs < lhs);
			}

		template <class T1, class T2>
			bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
				return rhs < lhs;
			}

		template <class T1, class T2>
			bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
				return !(lhs < rhs);
			}

		template <class T1, class T2>
			pair<T1,T2> make_pair (T1 x, T2 y) {
				return (pair<T1, T2>(x, y));
			}

} //namespace ft end
