#pragma once

#include "Includes.hpp"
#include <memory>

namespace ft {

	template <class T, class A = std::allocator<T> >
	class vector {
		public:
			typedef T										value_type;
			typedef A										allocator_type;
			typedef typename A::pointer 					pointer;
			typedef typename A::const_pointer				const_pointer;
			typedef typename A::reference					reference;
			typedef typename A::const_reference				const_reference;
			typedef typename A::size_type					size_type;
			typedef typename A::difference_type				difference_type;

			typedef ft::normal_iterator<value_type>			iterator;
			typedef ft::normal_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;


		private:
			A				_alloc;
			pointer			_array;
			size_type		_size;
			size_type		_capacity;

			bool		reallocate(size_type newCapacity) {
				size_type oldSize = this->size();

				if (newCapacity == 0)
					return false;
				pointer tmp = this->_alloc.allocate(newCapacity);
				try {
					for (size_type i = 0; i < this->_size; ++i) {
						_alloc.construct(&tmp[i], this->_array[i]);
					}
				} catch (std::exception &e) {
					this->_alloc.deallocate(tmp, newCapacity);
					throw;
				}
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_array + i);
				if (this->capacity() != 0) {
					_alloc.deallocate(_array, _capacity);
				}
				this->_capacity = newCapacity;
				this->_size = oldSize;
				this->_array = tmp;
				return true;
			};

		public:
			/* CONSTRUCTORS */

			explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _array(0), _size(0), _capacity(0)  {};

			explicit vector(size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type())
				 	: _alloc(alloc), _size(n), _capacity(n) {
					_array = _alloc.allocate(n);
					for (size_type i = 0; i < n; i++) {
						_alloc.construct(&_array[i], val);
					}
				 };

			vector (const vector& x)
				: _alloc(x._alloc), _size(x.size()), _capacity(x.capacity()) {
				this->_array = this->_alloc.allocate(this->capacity());
				this->assign(x.begin(), x.end());
			}

			vector& operator=(const vector& x) {
				if (*this == x)
					return (*this);
				this->clear();
				if (x.size() > this->capacity())
					this->reserve(x.size());
				this->assign(x.begin(), x.end());
				return (*this);
			}
			/*
			** range constructor
			*/
			template<class InputIterator>
				vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
					typename ft::enable_if<!is_integral<InputIterator>::value>::type* = 0)
						: _alloc(alloc), _size(0), _capacity(0) {
					for (; first != last; ++first)
						push_back(*first);
				}

			/* 
			** MEMBER FUNCTIONS
			*/
			allocator_type get_allocator() const {
				return this->_alloc;
			}

			size_type	size(void) const { return this->_size;};
			size_type	max_size(void) const { return this->_alloc.max_size();}
			size_type	capacity(void) const { return this->_capacity;};
			bool		empty(void) const { return this->size() == 0;};

			void	push_back(const value_type& val) {
				if (this->_size + 1 > this->_capacity) {
					size_type newCapacity = this->_capacity * 2;
					if (newCapacity == 0) newCapacity = 1;
					this->reallocate(newCapacity);
				}
				this->_alloc.construct(&this->_array[_size], val);
				this->_size++;
			};

			void	pop_back() {
				this->_alloc.destroy(&this->_array[this->_size - 1]);
				this->_size--;
			};

			void	reserve(size_type n) {
				if (n > this->max_size())
					throw std::length_error("vector::reserve");
				if (n > this->_capacity)
					this->reallocate(n);
			};

			void	resize(size_type n, value_type val = value_type()) {
				if (n > this->_capacity) {
					this->reallocate(n);
				}
				while (n > this->_size)
					push_back(val);
				while (n < this->_size)
					pop_back();
			};

			void assign(size_type n, const value_type& val) {
				this->clear();
				if (n > this->_capacity) {
					this->reserve(n);
				}
				for (size_type i = 0; i < n; i++) {
					_alloc.construct(&_array[i], val);
				}
				this->_size = n;
			}

			template<class InputIterator>
				void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!is_integral<InputIterator>::value>::type* = 0) {
					this->clear();
					for (; first != last; ++first)
						push_back(*first);
				}

			iterator erase(iterator position) {
				if (this->empty())
					return this->end();

				pointer __pos = &(*position);
				iterator __last = this->end();

				for (; position != this->end(); position++) {
					this->_alloc.destroy(&(*position));
					if (position + 1 != end()) {
						this->_alloc.construct(&(*position), *(position + 1));
					}
				}
				this->_size -= 1;
				return iterator(__pos);
			}

			iterator erase(iterator first, iterator last) {
				pointer __first = &(*first);
				size_type size_diff = static_cast<size_type>(last - first);

				if (last < this->end()) {
					for (; first != this->end(); first++, last++) {
						this->_alloc.destroy(&(*first));
						if (last < this->end()) {
							this->_alloc.construct(&(*first), *last);
						}
					}
				} else {
					for (; first < last; first++) {
						this->_alloc.destroy(&(*first));
					}
				}
				if (this->_size != 0)
					this->_size -= size_diff;
				return iterator(__first);
			}
			
			void		clear(void) {
				if (this->size() != 0)
					this->erase(begin(), end());
			};

			iterator insert(iterator position, const value_type& val) {
				difference_type index = ft::distance(this->begin(), position);

				this->insert(position, 1, val);
				return iterator(&this->_array[index]);
			}

			void insert(iterator position, size_type n, const value_type& val) {
				difference_type index = ft::distance(this->begin(), position);

				if (this->size() + n > this->capacity())
					this->reserve(this->capacity() + n);
				iterator newPos(&_array[index]);
				if (newPos != this->end()) {
					for (iterator __last = this->end() - 1; __last + 1 != newPos; __last--) {
						this->_alloc.construct(&(*(__last + n)), *__last);
						this->_alloc.destroy(&(*__last));
					}
				}
				for (size_type i = 0; i < n; i++) {
					this->_alloc.construct(&(*(newPos + i)), val);
				}
				this->_size += n;
			}

			template<class InputIterator>
				void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!is_integral<InputIterator>::value>::type* = 0) {
					for (; first != last; ++first) {
						position = insert(position, *first);
						++position;
					}
				}

			reference at(size_type __size) {
				if (__size >= this->size())
					throw std::out_of_range("vector::range_check: __size (which is " + ft::my_to_string(__size) + ") >= this->size() (which is " + ft::my_to_string(this->size()) + ")");
				return (this->_array[__size]);
			};

			const_reference at(size_type __size) const {
				if (__size >= this->size())
					throw std::out_of_range("vector::range_check: __size (which is " + ft::my_to_string(__size) + ") >= this->size() (which is " + ft::my_to_string(this->size()) + ")");
				return (this->_array[__size]);
			};

			void swap(vector& x) {
				ft::my_swap(this->_alloc, x._alloc);
				ft::my_swap(this->_array, x._array);
				ft::my_swap(this->_size, x._size);
				ft::my_swap(this->_capacity, x._capacity);
			}

			reference front() {
				return *begin();
			}

			const_reference front() const {
				return *begin();
			}

			reference back() {
				return *(end() - 1);
			}

			const_reference back() const {
				return *(end() - 1);
			}

			reference		operator[](size_type pos) { return this->_array[pos];};

			const_reference	operator[](size_type pos) const { return this->_array[pos];};

			~vector() {
				this->clear();
				this->_alloc.deallocate(this->_array, this->_capacity);
			};

			/**
			 * iterators
			 */
			iterator begin() {
				return iterator(_array);
			}

			iterator end() {
				return iterator(_array + _size);
			}

			reverse_iterator rbegin() {
				return reverse_iterator(end());
			}

			reverse_iterator rend() {
				return reverse_iterator(begin());
			}

			const_iterator begin() const {
				return const_iterator(_array);
			}

			const_iterator end() const {
				return const_iterator(_array + _size);
			}

			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(end());
			}

			const_reverse_iterator rend() const {
				return const_reverse_iterator(begin());
			}
	}; // class vector

	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
			x.swap(y);
		}

	/*
	** relational operators
	*/
	template <class T, class Alloc>
		bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (lhs.size() == rhs.size()
				&& ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
  		}	

	template <class T, class Alloc>
		bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(lhs == rhs);
  		}

	template <class T, class Alloc>
		bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(),
				rhs.begin(), rhs.end());
  		}

	template <class T, class Alloc>
		bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(rhs < lhs);
  		}

	template <class T, class Alloc>
		bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return rhs < lhs;
  		}

	template <class T, class Alloc>
		bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(lhs < rhs);
		}

} //ft namespace end
