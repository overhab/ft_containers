#pragma once

#include "Includes.hpp"

namespace ft {

	template<class _Iterator>
		class normal_iterator {
			protected:
				_Iterator								_current;
				typedef ft::iterator_traits<_Iterator>	_iterator_traits;
			public:
				typedef _Iterator										iterator_type;
				typedef typename _iterator_traits::iterator_category	iterator_category;
				typedef typename _iterator_traits::value_type 			value_type;
				typedef typename _iterator_traits::difference_type		difference_type;
				typedef typename _iterator_traits::reference 			reference;
				typedef typename _iterator_traits::pointer 				pointer;

			normal_iterator() : _current() {}

			normal_iterator(pointer a) : _current(a) {}

			normal_iterator(const normal_iterator& copy) : _current(copy.base()) {}

			template<class _Iter>
				normal_iterator(const normal_iterator<_Iter> &rhs) : _current(rhs.base()) {}

			normal_iterator & operator=(const  normal_iterator & __value) {
				_current = __value.base();
				return *this;
			}

			const _Iterator& base() const {
				return _current;
			}

			reference operator*() const {
				return *_current;
			}

			pointer operator->() const {
				return _current;
			}

			normal_iterator& operator++() {
				++_current;
				return *this;
			}

			normal_iterator& operator--() {
				--_current;
				return *this;
			}

			normal_iterator operator++(int) {
				return normal_iterator(_current++);
			}

			normal_iterator operator--(int) {
				return normal_iterator(_current--);
			}

			reference operator[](difference_type __dist) {
				return _current[__dist];
			}

			normal_iterator& operator+=(difference_type __dist) {
				_current += __dist;
				return *this;
			}

			normal_iterator operator+(difference_type __dist) {
				return normal_iterator(_current + __dist);
			}

			normal_iterator& operator-=(difference_type __dist) {
				_current -= __dist;
				return *this;
			}

			normal_iterator operator-(difference_type __dist) {
				return normal_iterator(_current - __dist);
			}

			virtual ~normal_iterator() {}
		};

	template<class _Iter1>
		inline bool operator==(const normal_iterator<_Iter1> &lhs, const normal_iterator<_Iter1> &rhs) {
			return lhs.base() == rhs.base();
		}

	template<class _Iter1>
		inline bool operator!=(const normal_iterator<_Iter1> &lhs, const normal_iterator<_Iter1> &rhs) {
			return lhs.base() != rhs.base();
		}

	template<class _Iter1>
		inline bool operator<(const normal_iterator<_Iter1> &lhs, const normal_iterator<_Iter1> &rhs) {
			return lhs.base() < rhs.base();
		}

	template<class _Iter1>
		inline bool operator>(const normal_iterator<_Iter1> &lhs, const normal_iterator<_Iter1> &rhs) {
			return lhs.base() > rhs.base();
		}

	template<class _Iter1>
		inline bool operator<=(const normal_iterator<_Iter1> &lhs, const normal_iterator<_Iter1> &rhs) {
			return lhs.base() <= rhs.base();
		}

	template<class _Iter1>
		inline bool operator>=(const normal_iterator<_Iter1> &lhs, const normal_iterator<_Iter1> &rhs) {
			return lhs.base() >= rhs.base();
		}

	template<class _Iter1, class _Iter2>
		inline typename normal_iterator<_Iter1>::difference_type
			operator-(const normal_iterator<_Iter1> &lhs, const normal_iterator<_Iter2> &rhs) {
			return lhs.base() - rhs.base();
		}

	template<class _Iter1>
		inline typename normal_iterator<_Iter1>::difference_type
			operator+(const normal_iterator<_Iter1> &lhs, const normal_iterator<_Iter1> &rhs) {
			return lhs.base() + rhs.base();
		}

		//normal_iterator end


	template<class _Iterator>
		class reverse_iterator {
			protected:
				_Iterator								_current;
				typedef ft::iterator_traits<_Iterator>	_iterator_traits;
			public:
				typedef _Iterator										iterator_type;
				typedef typename _iterator_traits::iterator_category	iterator_category;
				typedef typename _iterator_traits::value_type 			value_type;
				typedef typename _iterator_traits::difference_type		difference_type;
				typedef typename _iterator_traits::reference 			reference;
				typedef typename _iterator_traits::pointer 				pointer;

			reverse_iterator() : _current() {}

			reverse_iterator(iterator_type a) : _current(a) {}

			reverse_iterator(const reverse_iterator& copy) : _current(copy._current) {}

			template<class _Iter>
				reverse_iterator(const reverse_iterator<_Iter> &rhs) : _current(rhs.base()) {}

			reverse_iterator & operator=(const  reverse_iterator & __value) {
				_current = __value.base();
				return *this;
			}

			const _Iterator& base() const {
				return _current;
			}

			reference operator*() const {
				_Iterator _tmp = _current;
				return *--_tmp;
			}

			pointer operator->() const {
				return &(operator*());
			}

			reverse_iterator& operator++() {
				--_current;
				return *this;
			}

			reverse_iterator& operator--() {
				++_current;
				return *this;
			}

			reverse_iterator operator++(int) {
				reverse_iterator _tmp = *this;
				--_current;
				return _tmp;
			}

			reverse_iterator operator--(int) {
				reverse_iterator _tmp = *this;
				++_current;
				return _tmp;
			}

			reference operator[](difference_type __dist) {
				return *(*this + __dist);
			}

			reverse_iterator& operator+=(difference_type __dist) {
				_current -= __dist;
				return *this;
			}

			reverse_iterator operator+(difference_type __dist) {
				return reverse_iterator(_current - __dist);
			}

			reverse_iterator& operator-=(difference_type __dist) {
				_current += __dist;
				return *this;
			}

			reverse_iterator operator-(difference_type __dist) {
				return reverse_iterator(_current + __dist);
			}

			virtual ~reverse_iterator() {}
		};

	template<class _Iter1>
		inline bool operator==(const reverse_iterator<_Iter1> &lhs, const reverse_iterator<_Iter1> &rhs) {
			return lhs.base() == rhs.base();
		}

	template<class _Iter1>
		inline bool operator!=(const reverse_iterator<_Iter1> &lhs, const reverse_iterator<_Iter1> &rhs) {
			return lhs.base() != rhs.base();
		}

	template<class _Iter1>
		inline bool operator<(const reverse_iterator<_Iter1> &lhs, const reverse_iterator<_Iter1> &rhs) {
			return lhs.base() < rhs.base();
		}

	template<class _Iter1>
		inline bool operator>(const reverse_iterator<_Iter1> &lhs, const reverse_iterator<_Iter1> &rhs) {
			return lhs.base() > rhs.base();
		}

	template<class _Iter1>
		inline bool operator<=(const reverse_iterator<_Iter1> &lhs, const reverse_iterator<_Iter1> &rhs) {
			return lhs.base() <= rhs.base();
		}

	template<class _Iter1>
		inline bool operator>=(const reverse_iterator<_Iter1> &lhs, const reverse_iterator<_Iter1> &rhs) {
			return lhs.base() >= rhs.base();
		}

	//reverse_iterator end

	//distance
	template<class _Iter1, class _Iter2>
		inline typename iterator_traits<_Iter1>::difference_type
		distance(_Iter1 first, _Iter2 last) {
			return last - first;
		}

} //namespace ft end