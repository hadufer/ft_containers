#pragma once
#include <memory>
#include "vector.hpp"
#include "tree.hpp"
#include "iterator.hpp"
#include "stack.hpp"
#include "utils.hpp"
#include "pair.hpp"

namespace ft{
	template<
	class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<ft::pair<const Key, T> >
	> class map
	{
		public:
			typedef Key											key_type;
			typedef	T											mapped_type;
			typedef	ft::pair<key_type, mapped_type>				value_type;
			typedef	Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef	typename allocator_type::reference			reference;
			typedef	typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef	typename allocator_type::const_pointer		const_pointer;
			class value_compare
			{
				protected:
					Compare mCompare;
				public:
					typedef bool								result_type;
					typedef value_type							first_argument_type;
					typedef value_type							second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return mCompare(x.first, y.first);
				}
			};
			typedef	Tree<value_type, value_compare>				tree_type;
			typedef	typename tree_type::iterator				iterator;	
			typedef	typename tree_type::const_iterator			const_iterator;
			typedef	typename tree_type::size_type				size_type;
			typedef map<Key, value_compare>						map_type;
			typedef	typename tree_type::reverse_iterator		reverse_iterator;
			typedef	typename tree_type::const_reverse_iterator	const_reverse_iterator;
		private:
			tree_type											mTree;
			allocator_type										mAllocator;
			key_compare											mkeyCompare;
			value_compare										mValCompare;

		public:
			map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : mAllocator(alloc), mkeyCompare(comp), mValCompare(value_compare()) {}

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : mAllocator(alloc), mkeyCompare(comp), mValCompare(value_compare())
			{
				for (InputIterator begin = first; begin != last; begin++)
				{
					mTree.insert(*begin);
				}
			}

			map(const map &x)
			{
				*this = x;
			}

			map &operator=(const map &x) 
			{
				mTree = x.mTree;
				mTree.clear();
				insert(x.begin(), x.end());
				mAllocator = x.mAllocator;
				mkeyCompare = x.mkeyCompare;
				mValCompare = x.mValCompare;
				return (*this);
			}

			~map() { mTree.clear(); }

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				for (InputIterator begin = first; begin != last; begin++)
				{
					mTree.insert(*begin);
				}
			}

			void erase(iterator position) { mTree.erase(position); }

			size_type erase(const key_type &k)
			{
				ft::pair<key_type, mapped_type> toErase = ft::make_pair(k, mapped_type());
				return mTree.erase(toErase);
			}

			void erase(iterator first, iterator last)
			{
				while (first != last)
					mTree.erase(first++);
			}

			void swap(map &x)
			{
				map tmpMap = map(x);

				mTree.swap(x.mTree);
				x.mAllocator = mAllocator;
				x.mkeyCompare = mkeyCompare;
				x.mValCompare = mValCompare;
				this->mAllocator = tmpMap.mAllocator;
				this->mkeyCompare = tmpMap.mkeyCompare;
				this->mValCompare = tmpMap.mValCompare;
			}

			iterator begin() { return iterator(mTree.begin()); }

			reverse_iterator rbegin() { return reverse_iterator(mTree.rbegin()); }

			const_iterator begin() const { return const_iterator(mTree.begin()); }

			const_reverse_iterator rbegin() const { return const_reverse_iterator(mTree.rbegin()); }

			iterator end() { return iterator(mTree.end()); }

			reverse_iterator rend() { return reverse_iterator(mTree.rend()); }

			const_iterator end() const { return const_iterator(mTree.end()); }

			const_reverse_iterator rend() const { return const_reverse_iterator(mTree.rend()); }

			bool empty() const { return mTree.size() == 0; }

			size_type size(void) const { return mTree.size(); }

			size_type max_size() const { return mTree.max_size();}

			mapped_type &operator[](const key_type &k) { return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second; }

			pair<iterator, bool> insert(const value_type &val) { return mTree.insert(val); }

			iterator insert(iterator position, const value_type &val) { return mTree.insert(position, val); }

			void clear() { mTree.clear(); }

			key_compare key_comp() const { return this->mkeyCompare; }

			value_compare value_comp() const { return this->mValCompare; }

			iterator find(const key_type &k) { return mTree.find(ft::make_pair(k, mapped_type())); }

			const_iterator find(const key_type &k) const { return mTree.find(ft::make_pair(k, mapped_type())); }

			size_type count(const key_type &k) const { return (mTree.find(ft::make_pair(k, mapped_type())) != mTree.end()); }

			allocator_type get_allocator() const { return this->mAllocator; }
			
			iterator lower_bound(const key_type &k)
			{
				iterator	it(mTree.begin());
				iterator	ite(mTree.end());

				for (; it != ite; it++)
				{
					if (it->first >= k)
						break;
				}
				return (it);
			}

			const_iterator lower_bound(const key_type &k) const
			{
				const_iterator	it(mTree.begin());
				const_iterator	ite(mTree.end());

				for (; it != ite; it++)
				{
					if (it->first >= k)
						break;
				}
				return (it);
			}

			iterator upper_bound(const key_type &k)
			{
				iterator	it(mTree.begin());
				iterator	ite(mTree.end());

				for (; it != ite; it++)
				{
					if (it->first > k)
						break;
				}
				return	(it);
			}

			const_iterator upper_bound(const key_type &k) const
			{
				const_iterator	it(mTree.begin());
				const_iterator	ite(mTree.end());

				for (; it != ite; it++)
				{
					if (it->first > k)
						break;
				}
				return	(it);
			}

			ft::pair<iterator, iterator> equal_range(const key_type &k)
			{
				ft::pair<iterator, iterator>	ret;
				iterator up = upper_bound(k);
				iterator low = lower_bound(k);
				ret = ft::make_pair(low, up);
				return (ret);
			}

			ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
			{
				ft::pair<const_iterator, const_iterator>	ret;
				const_iterator up = upper_bound(k);
				const_iterator low = lower_bound(k);
				ret = ft::make_pair(low, up);
				return (ret);
			}

	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		std::map<Key, T, Compare> test;
		std::map<Key, T, Compare> test2;
		for(typename ft::map<Key, T, Compare, Alloc>::const_iterator it = lhs.begin(); it != lhs.end(); it++)
			test.insert(std::make_pair(it->first, it->second));
		for(typename ft::map<Key, T, Compare, Alloc>::const_iterator it = rhs.begin(); it != rhs.end(); it++)
			test2.insert(std::make_pair(it->first, it->second));
		return (test == test2);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		std::map<Key, T, Compare> test;
		std::map<Key, T, Compare> test2;
		for(typename ft::map<Key, T>::const_iterator it = lhs.begin(); it != lhs.end(); it++)
			test.insert(std::make_pair(it->first, it->second));
		for(typename ft::map<Key, T>::const_iterator it = rhs.begin(); it != rhs.end(); it++)
			test2.insert(std::make_pair(it->first, it->second));
		return (test != test2);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		std::map<Key, T, Compare> test;
		std::map<Key, T, Compare> test2;
		for(typename ft::map<Key, T, Compare, Alloc>::const_iterator it = lhs.begin(); it != lhs.end(); it++)
			test.insert(std::make_pair(it->first, it->second));
		for(typename ft::map<Key, T, Compare, Alloc>::const_iterator it = rhs.begin(); it != rhs.end(); it++)
			test2.insert(std::make_pair(it->first, it->second));
		return (test < test2);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		std::map<Key, T, Compare> test;
		std::map<Key, T, Compare> test2;
		for(typename ft::map<Key, T, Compare, Alloc>::const_iterator it = lhs.begin(); it != lhs.end(); it++)
			test.insert(std::make_pair(it->first, it->second));
		for(typename ft::map<Key, T, Compare, Alloc>::const_iterator it = rhs.begin(); it != rhs.end(); it++)
			test2.insert(std::make_pair(it->first, it->second));
		return (test <= test2);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		std::map<Key, T, Compare> test;
		std::map<Key, T, Compare> test2;
		for(typename ft::map<Key, T, Compare, Alloc>::const_iterator it = lhs.begin(); it != lhs.end(); it++)
			test.insert(std::make_pair(it->first, it->second));
		for(typename ft::map<Key, T, Compare, Alloc>::const_iterator it = rhs.begin(); it != rhs.end(); it++)
			test2.insert(std::make_pair(it->first, it->second));
		return (test > test2);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		std::map<Key, T, Compare> test;
		std::map<Key, T, Compare> test2;
		for(typename ft::map<Key, T, Compare, Alloc>::const_iterator it = lhs.begin(); it != lhs.end(); it++)
			test.insert(std::make_pair(it->first, it->second));
		for(typename ft::map<Key, T, Compare, Alloc>::const_iterator it = rhs.begin(); it != rhs.end(); it++)
			test2.insert(std::make_pair(it->first, it->second));
		return (test >= test2);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key, T, Compare, Alloc> &lhs, ft::map<Key, T, Compare, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
}