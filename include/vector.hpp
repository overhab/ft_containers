#pragma once

#include "Includes.hpp"
#include <memory>

namespace ft {

	template <class T, class A = std::allocator<T> >
	class vector {
		public:
			typedef A										allocator_type;
			typedef typename A::pointer 					pointer;
			typedef typename A::const_pointer				const_pointer;
			typedef typename A::reference					reference;
			typedef typename A::const_reference				const_reference;
			typedef typename A::value_type					value_type;
			typedef typename A::size_type					size_type;
			typedef typename A::difference_type				difference_type;

			typedef ft::normal_iterator<pointer>			iterator;
			typedef ft::normal_iterator<const_pointer>		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;


		private:
			pointer			_array;
			size_type		_size;
			size_type		_capacity;
			A				_alloc;

			/* REALLOCATE NEW VECTOR WHEN NEEDED */
			bool		reallocate(size_type newCapacity) {
				/* check if newCapacity != 0 (even tho it's impossible to get here if its 0) */
				if (newCapacity == 0)
					return false;
				pointer tmp = this->_alloc.allocate(newCapacity);
				for (size_type i = 0; i < this->_size; i++) {
					_alloc.construct(&tmp[i], this->_array[i]);
				}
				this->~vector(); //delete previous instance of vector to replace with new
				this->_capacity = newCapacity;
				this->_array = tmp;
				return true;
			};

		public:
			/* CONSTRUCTORS */

			explicit vector(const allocator_type& alloc = allocator_type()) : _array(0), _size(0), _capacity(0), _alloc(alloc) {};

			explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type())
				 	: _size(n), _capacity(n), _alloc(alloc) {
					_array = _alloc.allocate(n);
					for (size_type i = 0; i < n; i++) {
						_alloc.construct(&_array[i], val);
					}
				 };


			//range constructor
			template<class InputIterator>
				vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type())
				: _alloc(alloc), _size(ft::distance(first, last)), _capacity(ft::distance(first, last)) {
					if (first > last)
						throw std::length_error("vector");
					this->_array = this->_alloc.allocate(this->size());
					for (size_type i = 0; first < last; i++, first++) {
						_alloc.construct(this->_array + i, *first);
					}
				}


			/* MEMBER FUNCTIONS*/

			size_type	size(void) { return this->_size;};
			size_type	max_size(void) { return this->_alloc.max_size();} //Documentation: https://www.viva64.com/en/a/0050/
			size_type	capacity(void) { return this->_capacity;};
			bool		empty(void) { return this->size() == 0;};

			void		push_back(const value_type& val) {
				if (this->_size + 1 > this->_capacity)
					this->reallocate((this->_capacity * 2) + 1);
				this->_alloc.construct(&this->_array[_size], val);
				this->_size++;
			};

			void pop_back() {
				this->_alloc.destroy(&this->_array[this->_size - 1]);
				this->_size--;
			};

			void reserve(size_type n) {
				if (n > this->max_size())
					throw std::length_error("vector");
				if (n > this->_capacity)
					this->reallocate(n);
				/* check if the vector[i] (where i is index after new size) is returning 0 */
			};

			void		resize(size_type n, value_type val = value_type()) {
				if (n > this->_capacity) {
					this->reallocate(n);
				}
				while (n > this->_size)
					push_back(val);
				while (n < this->_size)
					pop_back();
			};
			
			void		clear(void) {
				while (this->_size)
					this->pop_back();
			}; // erase(begin(), end());


			reference		operator[](size_type pos) { return this->_array[pos];};

			const_reference	operator[](size_type pos) const { return this->_array[pos];};


			~vector() {
				this->clear();
				this->_alloc.deallocate(this->_array, this->_capacity);
				this->_array = 0;
			};


			//iterators

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
	};




} //ft namespace end
