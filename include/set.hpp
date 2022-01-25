#pragma once

#include "Includes.hpp"
#include <memory>

namespace ft {
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
		class set {
		public:
			typedef T										key_type;
			typedef T										value_type;
			typedef Compare									key_compare;
			typedef Compare									value_compare;


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
	
			typedef typename tree_type::const_iterator			iterator;
			typedef typename tree_type::const_iterator			const_iterator;
			typedef typename tree_type::const_reverse_iterator	reverse_iterator;
			typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

		private:	
			allocator_type	_alloc;
			key_compare		_comp;
		
		public:

			explicit set(const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()) 
			  	: _tree(comp, alloc), _alloc(alloc), _comp(comp) {}

		template <class InputIterator>
			set(InputIterator first, InputIterator last, 
				const key_compare& comp = key_compare(), 
					const allocator_type& alloc = allocator_type()) 
						: _tree(comp, alloc), _alloc(alloc), _comp(comp) {
				this->insert(first, last);
			}

			set(const set& x) 
				: _tree(x.key_comp(), x.get_allocator()), _alloc(x.get_allocator()), _comp(x.key_comp()) {
				this->insert(x.begin(), x.end());
			}

			set&	operator=(const set& x) {
				
				this->_alloc = x.get_allocator();
				this->_comp = x.key_comp();
				this->clear();
				this->insert(x.begin(), x.end());
				return *this;
			}

			~set() { this->clear(); }

			allocator_type	get_allocator() const {
				return _tree.get_allocator();
			}

			bool empty() const { return _tree.size() == 0; }
			size_type size() const { return _tree.size(); }
			size_type max_size() const { return this->_tree.max_size(); }

			key_compare		key_comp() const {
				return this->_comp;
			}

			value_compare	value_comp() const {
				return _tree.key_comp();
			}

			iterator find(const value_type& val) const {
				return _tree.find(val);
			}

/* 			const_iterator find(const value_type& val) const {
				return _tree.find(val);
			} */

			size_type count(const value_type& val) const {
				return _tree.count(val);
			}

			iterator lower_bound(const value_type& val) const {
				return _tree.lower_bound(val);
			}

			iterator upper_bound(const value_type& val) const {
				return _tree.upper_bound(val);
			}

			pair<iterator,bool> insert(const value_type& val) {
				iterator it = find(val);

				if (it == end())
					return _tree.insert(val);
				return ft::make_pair<iterator, bool>(it, false);
			}

			iterator	insert(iterator position, const value_type& val) {
				iterator it = find(val);

				if (it == end())
					it = _tree.insert(position, val);
				return it;
			}

		template <class InputIterator>
			void 	insert(InputIterator first, InputIterator last) {
				for (; first != last; first++) {
					this->insert(*first);
				}
			}

			void	erase(iterator position) {
				if (this->size() == 0)
					return ;
				this->erase(*position);
			}

			size_type	erase(const value_type& val) {
				if (this->size() == 0)
					return 0;
				iterator __pos = find(val);
				if (__pos != end()) {
					_tree.erase(__pos);
					return 1;
				}
				return 0;
			}

			void erase(iterator first, iterator last) {
				if (this->size() == 0)
					return ;
				while (first != last) {
					this->erase((first++));
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

			ft::pair<iterator,iterator>		equal_range(const value_type& val) const {
				return (ft::pair<iterator, iterator>(lower_bound(val), upper_bound(val)));
			}

			void	swap(set& x) {
				this->_tree.swap(x._tree);
			}

			template<class _K1, class _C1, class _A1>
			friend bool operator==(const set<_K1, _C1, _A1>&, const set<_K1, _C1, _A1>&);

			template<class _K1, class _C1, class _A1>
			friend bool operator<(const set<_K1, _C1, _A1>&, const set<_K1, _C1, _A1>&);
		
		}; //class set end

	template<class Key, class Compare, class Alloc>
	bool operator==(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs){
			return (lhs._tree == rhs._tree); 
	}

	template<class Key, class Compare, class Alloc>
	bool operator!=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs){
			return !(lhs == rhs); 
	}

	template<class Key, class Compare, class Alloc>
	bool operator<(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs){
			return (lhs._tree < rhs._tree);
	}

	template<class Key, class Compare, class Alloc>
	bool operator>(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs){
			return (rhs < lhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator<=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs){
			return !(lhs > rhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator>=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs){
			return !(lhs < rhs);
	}

	template<class Key, class Compare, class Alloc>
	void swap(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs){
		lhs.swap(rhs);
	}

} // namespace ft end
