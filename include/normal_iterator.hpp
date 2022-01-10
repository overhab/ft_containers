#pragma once

#include "Includes.hpp"

namespace ft {

	template<class _Iterator>
		class normal_iterator {
			private:
				typedef ft::iterator<ft::random_access_iterator_tag, _Iterator>	_iterator_traits;
			public:
				typedef _Iterator										iterator_type;
				typedef typename _iterator_traits::iterator_category	iterator_category;
				typedef typename _iterator_traits::value_type 			value_type;
				typedef typename _iterator_traits::difference_type		difference_type;
				typedef _Iterator& 			reference;
				typedef _Iterator* 				pointer;

			private:
				pointer _current;

			public:
			normal_iterator() : _current() {}

			normal_iterator(pointer a) : _current(a) {}

			normal_iterator(const normal_iterator& copy) : _current(copy.base()) {}

			template<class _Iter>
				normal_iterator(const normal_iterator<_Iter> &rhs) : _current(rhs.base()) {}

			normal_iterator & operator=(const  normal_iterator & __value) {
				_current = __value.base();
				return *this;
			}

			pointer base() const {
				return this->_current;
			}

			reference operator*() const {
				return *_current;
			}

			pointer operator->() const {
				return &(this->operator*());
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

			reference operator[](difference_type __dist) const {
				return _current[__dist];
			}

			normal_iterator& operator+=(difference_type __dist) {
				_current += __dist;
				return *this;
			}

			normal_iterator operator+(difference_type __dist) const {
				return normal_iterator(_current + __dist);
			}

			normal_iterator& operator-=(difference_type __dist) {
				_current -= __dist;
				return *this;
			}

			normal_iterator operator-(difference_type __dist) const {
				return normal_iterator(_current - __dist);
			}

			virtual ~normal_iterator() {}
		};

	template<class _Iter1, class _Iter2>
		inline bool operator==(const normal_iterator<_Iter1> &lhs, const normal_iterator<_Iter2> &rhs) {
			return lhs.base() == rhs.base();
		}

	template<class _Iter1, class _Iter2>
		inline bool operator!=(const normal_iterator<_Iter1> &lhs, const normal_iterator<_Iter2> &rhs) {
			return lhs.base() != rhs.base();
		}

	template<class _Iter1, class _Iter2>
		inline bool operator<(const normal_iterator<_Iter1> &lhs, const normal_iterator<_Iter2> &rhs) {
			return lhs.base() < rhs.base();
		}

	template<class _Iter1, class _Iter2>
		inline bool operator>(const normal_iterator<_Iter1> &lhs, const normal_iterator<_Iter2> &rhs) {
			return lhs.base() > rhs.base();
		}

	template<class _Iter1, class _Iter2>
		inline bool operator<=(const normal_iterator<_Iter1> &lhs, const normal_iterator<_Iter2> &rhs) {
			return lhs.base() <= rhs.base();
		}

	template<class _Iter1, class _Iter2>
		inline bool operator>=(const normal_iterator<_Iter1> &lhs, const normal_iterator<_Iter2> &rhs) {
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

	template<class _Iter1>
		inline normal_iterator<_Iter1> operator+(typename normal_iterator<_Iter1>::difference_type _n, const normal_iterator<_Iter1>& rhs) {
			return normal_iterator<_Iter1>(rhs.base() + _n);
		}

	template<class _Iter1>
		inline typename normal_iterator<_Iter1>::difference_type operator-(const normal_iterator<_Iter1>& lhs, const normal_iterator<_Iter1>& rhs) {
			return lhs.base() - rhs.base();
		}

		//normal_iterator end


	template<class _Iterator>
		class reverse_iterator {
			private:
				typedef ft::iterator<ft::random_access_iterator_tag, _Iterator>	_iterator_traits;
			public:
				typedef _Iterator										iterator_type;
				typedef typename _iterator_traits::iterator_category	iterator_category;
				typedef typename _iterator_traits::value_type 			value_type;
				typedef typename _iterator_traits::difference_type		difference_type;
				typedef _Iterator& 			reference;
				typedef _Iterator* 			pointer;

			private:
				iterator_type  _current;

			public:
			reverse_iterator() : _current() {}

			reverse_iterator(const _Iterator &  a) : _current(a) {}

			reverse_iterator(const reverse_iterator& copy) : _current(copy._current) {}

/* 			explicit reverse_iterator(iterator_type it) {
				_current = &it;
			} */

			template<class _Iter>
				reverse_iterator(const reverse_iterator<_Iter> &rhs) : _current(rhs.base()) {}

			reverse_iterator & operator=(const  reverse_iterator & __value) {
				_current = __value.base();
				return *this;
			}

			iterator_type base() const {
				return _current;
			}

			reference operator*() const {
				iterator_type  _tmp = this->_current;
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

			reference operator[](difference_type __dist) const {
				return *(*this + __dist);
			}

			reverse_iterator& operator+=(difference_type __dist) {
				_current -= __dist;
				return *this;
			}

			reverse_iterator operator+(difference_type __dist) const {
				return reverse_iterator(_current - __dist);
			}

			reverse_iterator& operator-=(difference_type __dist) {
				_current += __dist;
				return *this;
			}

			reverse_iterator operator-(difference_type __dist) const {
				return reverse_iterator(_current + __dist);
			}

			virtual ~reverse_iterator() {}
		};

	template<class _Iter1, class _Iter2>
		inline bool operator==(const reverse_iterator<_Iter1> &lhs, const reverse_iterator<_Iter2> &rhs) {
			return lhs.base() == rhs.base();
		}

	template<class _Iter1, class _Iter2>
		inline bool operator!=(const reverse_iterator<_Iter1> &lhs, const reverse_iterator<_Iter2> &rhs) {
			return lhs.base() != rhs.base();
		}

	template<class _Iter1, class _Iter2>
		inline bool operator<(const reverse_iterator<_Iter1> &lhs, const reverse_iterator<_Iter2> &rhs) {
			return lhs.base() < rhs.base();
		}

	template<class _Iter1, class _Iter2>
		inline bool operator>(const reverse_iterator<_Iter1> &lhs, const reverse_iterator<_Iter2> &rhs) {
			return lhs.base() > rhs.base();
		}

	template<class _Iter1, class _Iter2>
		inline bool operator<=(const reverse_iterator<_Iter1> &lhs, const reverse_iterator<_Iter2> &rhs) {
			return lhs.base() <= rhs.base();
		}

	template<class _Iter1, class _Iter2>
		inline bool operator>=(const reverse_iterator<_Iter1> &lhs, const reverse_iterator<_Iter2> &rhs) {
			return lhs.base() >= rhs.base();
		}

	template<class _Iter1>
		inline reverse_iterator<_Iter1> operator+(typename reverse_iterator<_Iter1>::difference_type _n, const reverse_iterator<_Iter1>& rhs) {
			return reverse_iterator<_Iter1>(rhs.base() - _n);
		}

	template<class _Iter1>
		inline typename reverse_iterator<_Iter1>::difference_type operator-(const reverse_iterator<_Iter1>& lhs, const reverse_iterator<_Iter1>& rhs) {
			return rhs.base() - lhs.base();
		}
	//reverse_iterator end

	//distance
	template<class _Iter1, class _Iter2>
		inline typename iterator_traits<_Iter1>::difference_type
		distance(_Iter1 first, _Iter2 last) {
			return last - first;
		}

} //namespace ft end