#pragma once

#include "Includes.hpp"

namespace ft {
	template <class T, class Container = ft::vector<T> >
	class stack {

		template<typename _Tp1, typename _Seq1>
			friend bool
			operator==(const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);

		template<typename _Tp1, typename _Seq1>
			friend bool
			operator<(const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);

		protected:
			Container _cont;

		public: 
			typedef Container								container_type;
			typedef typename Container::value_type 			value_type;
			typedef typename Container::size_type			size_type;

			stack() : _cont() {};
			explicit 				stack(const container_type& cont) : _cont(cont) {};
			bool 					empty() {return _cont.empty();};
			size_type				size() const {return _cont.size();};
			value_type&				top() {return _cont.back();};
			const value_type&		top() const {return _cont.back();};
			void					push(const value_type& x) {_cont.push_back(x);};
			void					pop() {_cont.pop_back();};
	};

	/*
	**Operator overloads
	*/
	template <class T, class Container>
	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs._cont == rhs._cont;
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return rhs < lhs;
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs._cont < rhs._cont;
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return !(lhs < rhs);
	}
	
	template <class T, class Container>
	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return !(rhs < lhs);
	}
	
} //ft namespace end
