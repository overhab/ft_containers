#pragma once

#include "Includes.hpp"
#include <memory>

namespace ft {
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
		class map {
		public:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const key_type, mapped_type>	value_type;
			typedef Compare									key_compare;

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
			protected:
				key_compare comp;
			public:
				value_compare(key_compare pred) : comp(pred) {}
				bool operator()(const value_type& left, const value_type& right) const {
					return comp(left.first, right.first);
				}
			};

		private:							  
			typedef RBTree<key_type, value_type, value_compare>	tree_type;
			tree_type	_tree;

		public:
			typedef Alloc										allocator_type;
			typedef typename Alloc::pointer 					pointer;
			typedef typename Alloc::const_pointer				const_pointer;
			typedef typename Alloc::reference					reference;
			typedef typename Alloc::const_reference				const_reference;
			typedef typename tree_type::size_type				size_type;
			typedef typename tree_type::difference_type			difference_type;
	
			typedef typename tree_type::iterator				iterator;
			typedef typename tree_type::const_iterator			const_iterator;
			typedef typename tree_type::reverse_iterator		reverse_iterator;
			typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

		private:	
			allocator_type	_alloc;
			key_compare		_comp;
		
		public:

			explicit map(const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()) 
			  	: _tree(value_compare(comp)), _alloc(alloc), _comp(comp) {}

		template <class InputIterator>
			map(InputIterator first, InputIterator last, 
				const key_compare& comp = key_compare(), 
					const allocator_type& alloc = allocator_type()) 
						: _tree(value_compare(comp)), _alloc(alloc), _comp(comp) {
				this->insert(first, last);
			}

			map(const map& x) 
				: _tree(value_compare(x.key_comp())), _alloc(x.get_allocator()), _comp(x.key_comp()) {
				this->insert(x.begin(), x.end());
			}

			map&	operator=(const map& x) {
				
				this->_alloc = x.get_allocator();
				this->_comp = x.key_comp();
				this->clear();
				this->insert(x.begin(), x.end());
				return *this;
			}

			~map() { this->clear(); }

			allocator_type	get_allocator() const {
				return _tree.get_allocator();
			}

			bool empty() const { return _tree.size() == 0; }
			size_type size() const { return _tree.size(); }
			size_type max_size() const { return _tree.max_size(); }

			key_compare		key_comp() const {
				return this->_comp;
			}

			mapped_type& operator[](const key_type& k) {
				iterator	it = this->find(k);

				if (it != this->end())
					return (it->second);
				return (this->insert(value_type(k, mapped_type())).first->second);
			}

			value_compare	value_comp() const {
				return value_compare(_tree.key_comp());
			}

			iterator find(const key_type& k) {
				return _tree.find(value_type(k, T()));
			}

			const_iterator find(const key_type& k) const {
				return _tree.find(value_type(k, T()));
			}

			size_type count(const key_type& k) const {
				return _tree.count(value_type(k, T()));
			}

			iterator lower_bound(const key_type& k) {
				return _tree.lower_bound(value_type(k, T()));
			}

			const_iterator lower_bound(const key_type& k) const {
				return _tree.lower_bound(value_type(k, T()));
			}

			iterator upper_bound(const key_type& k) {
				return _tree.upper_bound(value_type(k, T()));
			}

			const_iterator upper_bound(const key_type& k) const {
				return _tree.upper_bound(value_type(k, T()));
			}

			pair<iterator,bool> insert(const value_type& val) {
				iterator it = find(val.first);

				if (it == end())
					return _tree.insert(val);
				return ft::make_pair<iterator, bool>(it, false);
			}

			iterator	insert(iterator position, const value_type& val) {
				iterator it = find(val.first);

				if (it == end())
					it = _tree.insert(position, val);
				return it;
			}

		template <class InputIterator>
			void 	insert(InputIterator first, InputIterator last) {
				for (; first != last; ++first) {
					this->insert(*first);
				}
			}

			void	erase(iterator position) {
				if (this->size() == 0)
					return ;
				if (position == find(position->first))
					_tree.erase(position);
			}

			size_type	erase(const key_type& k) {
				if (this->size() == 0)
					return ;
				iterator __pos = find(k);
				if (__pos != end()) {
					erase(__pos);
					return 1;
				}
				return 0;
			}

			void erase(iterator first, iterator last) {
				if (this->size() == 0)
					return ;
				while (first != last) {
					this->erase(first++);
					if (this->size() == 0)
						break ;
				}
			}

			iterator begin() {
				return _tree.begin();
			}

			iterator end() {
				return _tree.end();
			}

			const_iterator begin() const {
				return _tree.begin();
			}

			const_iterator end() const {
				return _tree.end();
			}

			reverse_iterator rbegin() {
				return _tree.rbegin();
			}

			reverse_iterator rend() {
				return _tree.rend();
			}

			const_reverse_iterator rbegin() const {
				return _tree.rbegin();
			}

			const_reverse_iterator rend() const {
				return _tree.rend();
			}

			void	clear() {
				this->erase(this->begin(), this->end());
			}

			ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const {
				return (ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
			}

			ft::pair<iterator,iterator>             equal_range(const key_type& k) {
				return (ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
			}

			void	swap(map& x) {
				this->_tree.swap(x._tree);
			}

			/* void		printTree() const {
				_tree.printTree();
			} */

			template<class _K1, class _T1, class _C1, class _A1>
			friend bool operator==(const map<_K1, _T1, _C1, _A1>&, const map<_K1, _T1, _C1, _A1>&);

			template<class _K1, class _T1, class _C1, class _A1>
			friend bool operator<(const map<_K1, _T1, _C1, _A1>&, const map<_K1, _T1, _C1, _A1>&);
		
		}; //class map end

	template<class Key, class T, class Compare, class Alloc>
	inline bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs){
			return (lhs._tree == rhs._tree); 
	}

	template<class Key, class T, class Compare, class Alloc>
	inline bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs){
			return !(lhs == rhs); 
	}

	template<class Key, class T, class Compare, class Alloc>
	inline bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs){
			return (lhs._tree < rhs._tree);
	}

	template<class Key, class T, class Compare, class Alloc>
	inline bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs){
			return (rhs < lhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	inline bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs){
			return !(lhs > rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	inline bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs){
			return !(lhs < rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	void swap(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs){
		lhs.swap(rhs);
	}

} // namespace ft end
