#pragma once
#include "iterator.hpp"
#include "utils.hpp"
#include <memory>
#include <cstring>
#include <iostream>

namespace ft{
template<
	class T,
	class Allocator = std::allocator<T>
> class vector{
	public:
		typedef T												value_type;
		typedef Allocator										allocator_type;
		typedef typename Allocator::pointer						pointer;
		typedef typename Allocator::const_pointer				const_pointer;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef typename Allocator::size_type					size_type;
		typedef typename Allocator::difference_type				difference_type;
		typedef ft::random_access_iterator<value_type>			iterator;
		typedef ft::random_access_iterator<const value_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	protected:
		pointer				mBeginIt;
		allocator_type		mAlloc;
		size_type			mSize;
		size_type			mCapacity;

		void handleRealloc(size_type count = 0)
		{
			size_type	tmpMCapacity;
			if (count)
				tmpMCapacity = count;
			else
				tmpMCapacity = mCapacity * 2;

			if (!tmpMCapacity)
				tmpMCapacity = 1;
			if (tmpMCapacity > mAlloc.max_size())
				throw std::exception();
			pointer tmpIt = mAlloc.allocate(tmpMCapacity);
			for (size_type i = 0; i < mSize; i++)
			{
				mAlloc.construct(tmpIt + i, *(mBeginIt + i));
				mAlloc.destroy(mBeginIt + i);
			}
			mAlloc.deallocate(mBeginIt, mCapacity);
			mBeginIt = tmpIt;
			mCapacity = tmpMCapacity;
		}
	public:
		explicit vector(const allocator_type& alloc = allocator_type())
				: mBeginIt(0), mAlloc(alloc), mSize(0), mCapacity(0)
		{}

		explicit vector(size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
				: mBeginIt(0), mAlloc(alloc), mSize(0), mCapacity(0)
		{
			for (size_t i = 0; i < count; i++)
			{
				push_back(value);
			}
		}

		template<class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			: mBeginIt(0), mAlloc(alloc), mSize(0), mCapacity(0)
		{
			assign(first, last);
		}

		vector(const vector &cpy)
			: mBeginIt(NULL), mAlloc(cpy.mAlloc), mSize(0), mCapacity(0)
		{
			assign(cpy.begin(), cpy.end());
		}

		~vector()
		{
			clear();
			mAlloc.deallocate(mBeginIt, mCapacity);
		}

		void assign(size_type count, const T& value)
		{
			clear();
			if (count >= mCapacity)
				handleRealloc(count);
			for (size_type i = 0; i < count; i++)
				mAlloc.construct(mBeginIt + i, value);
			mSize = count;
		}

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
		typename ft::enable_if<!(ft::is_integral<InputIterator>::value)>::type* = NULL)
		{
			clear();
			size_type firstToLast = 0;
			for (InputIterator tmpIt = first; tmpIt != last; tmpIt++)
				firstToLast++;
			if (firstToLast >= mCapacity)
				handleRealloc(firstToLast);
			for (size_type i = 0; first != last; first++, i++)
				mAlloc.construct(mBeginIt + i, *first);
			mSize = firstToLast;
		}

		iterator insert(iterator position, const T& value)
		{
			size_type beginToPos = 0;
			for (iterator tmpIt = mBeginIt; tmpIt != position; tmpIt++)
				beginToPos++;
			if (mCapacity - mSize < 0)
				handleRealloc(mCapacity + (-1 * (mCapacity - mSize)) + 1);
			vector lastItemVec(iterator(mBeginIt + beginToPos), iterator(mBeginIt + mSize));
			for (iterator tmpIt = lastItemVec.mBeginIt; tmpIt != (lastItemVec.mBeginIt + lastItemVec.mSize); tmpIt++)
				pop_back();
			push_back(value);
			for (iterator tmpIt = lastItemVec.mBeginIt; tmpIt != (lastItemVec.mBeginIt + lastItemVec.mSize); tmpIt++)
				push_back(*tmpIt);
			return (iterator(mBeginIt + beginToPos));
		}

		void insert(const_iterator position, size_type count, const T& value)
		{
			while (mCapacity - mSize - count < 0)
				handleRealloc(mCapacity + (-1 * (mCapacity - mSize - count)) + 1);
			vector lastItemVec(iterator(mBeginIt + (position - iterator(mBeginIt))), iterator(mBeginIt + mSize));
			for (iterator tmpIt = lastItemVec.mBeginIt; tmpIt != (lastItemVec.mBeginIt + lastItemVec.mSize); tmpIt++)
				pop_back();
			for (size_type i = 0; i < count; i++)
				push_back(value);
			for (iterator tmpIt = lastItemVec.mBeginIt; tmpIt != (lastItemVec.mBeginIt + lastItemVec.mSize); tmpIt++)
				push_back(*tmpIt);
		}

		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		{
			size_type firstToLast = 0;
			for (InputIterator tmpIt = first; tmpIt != last; tmpIt++)
				firstToLast++;
			while (mCapacity - mSize - firstToLast < 0)
				handleRealloc(mCapacity + (-1 * (mCapacity - mSize - firstToLast)) + 1);
			vector lastItemVec(iterator(mBeginIt + (position - iterator(mBeginIt))), iterator(mBeginIt + mSize));
			for (iterator tmpIt = lastItemVec.mBeginIt; tmpIt != (lastItemVec.mBeginIt + lastItemVec.mSize); tmpIt++)
				pop_back();
			for (; first != last; first++)
				push_back(*first);
			for (iterator tmpIt = lastItemVec.mBeginIt; tmpIt != (lastItemVec.mBeginIt + lastItemVec.mSize); tmpIt++)
				push_back(*tmpIt);
		}

		iterator erase(const_iterator position)
		{
			size_type beginToPos = 0;
			for (iterator tmpIt = mBeginIt; tmpIt != position; tmpIt++)
				beginToPos++;
			vector lastItemVec(iterator(mBeginIt + beginToPos), iterator(mBeginIt + mSize));
			for (iterator tmpIt = lastItemVec.mBeginIt; tmpIt != (lastItemVec.mBeginIt + lastItemVec.mSize); tmpIt++)
				pop_back();
			for (iterator tmpIt = lastItemVec.mBeginIt + 1; tmpIt != (lastItemVec.mBeginIt + lastItemVec.mSize); tmpIt++)
				push_back(*tmpIt);
			return (iterator(mBeginIt + beginToPos));
		}

		iterator erase(iterator first, iterator last)
		{
			size_type beginToPos = 0;
			size_type firstToLast = 0;
			for (iterator tmpIt = mBeginIt; tmpIt != first; tmpIt++)
				beginToPos++;
			for (iterator tmpIt = first; tmpIt != last; tmpIt++)
				firstToLast++;
			vector lastItemVec(iterator(mBeginIt + beginToPos), iterator(mBeginIt + mSize));
			for (iterator tmpIt = lastItemVec.mBeginIt; tmpIt != (lastItemVec.mBeginIt + lastItemVec.mSize); tmpIt++)
				pop_back();
			for (iterator tmpIt = lastItemVec.mBeginIt + firstToLast; tmpIt != (lastItemVec.mBeginIt + lastItemVec.mSize); tmpIt++)
				push_back(*tmpIt);
			return (iterator(mBeginIt + beginToPos));
		}

		void push_back(const T& value)
		{
			if (mSize >= mCapacity)
				handleRealloc(0);
			mAlloc.construct(mBeginIt + mSize, value);
			mSize++;
		}

		void pop_back()
		{
			mSize--;
			mAlloc.destroy(mBeginIt + mSize);
		}

		void swap(vector& right)
		{
			if (right == *this)
				return ;
			pointer tmpBeginIt = 		mBeginIt;
			allocator_type	tmpAlloc =	mAlloc;
			size_type	tmpMSize =		mSize;
			size_type	tmpMCapacity =	mCapacity;

			mBeginIt = right.mBeginIt;
			mAlloc = right.mAlloc;
			mSize = right.mSize;
			mCapacity = right.mCapacity;

			right.mBeginIt = tmpBeginIt;
			right.mAlloc = tmpAlloc;
			right.mSize = tmpMSize;
			right.mCapacity = tmpMCapacity;
		}

		value_type	*data()
		{
			return mBeginIt;
		}

		reference operator[](size_type position)
		{
			return *(mBeginIt + position);
		}

		const_reference operator[](size_type position) const
		{
			return *(mBeginIt + position);
		}

		const_iterator begin() const
		{
			return (mBeginIt);
		}

		iterator begin()
		{
			return (mBeginIt);
		}

		const_reverse_iterator rbegin() const
		{
			return (reverse_iterator(end()));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(end()));
		}

		const_iterator end() const
		{
			if (empty())
				return (mBeginIt);
			return (mBeginIt + mSize);
		}

		iterator end()
		{
			if (empty())
				return (mBeginIt);
			return (mBeginIt + mSize);
		}

		const_reverse_iterator rend() const
		{
			return (reverse_iterator(begin()));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}

		bool empty() const { return (mSize == 0);}

		void clear()
		{
			for (size_type i = 0; i < mSize; i++)
			{
				mAlloc.destroy(mBeginIt + i);
			}
			mSize = 0;
		}

		void	resize(size_type n, value_type value = value_type())
		{
			if (n > max_size())
				throw std::exception();
			while (mSize < n)
				push_back(value);
			while (mSize > n)
			{
				mAlloc.destroy(mBeginIt + mSize);
				mSize--;
			}
		}

		void reserve(size_type new_cap)
		{
			if ((new_cap <= mCapacity) || (new_cap <= mAlloc.max_size()))
				return ;
			handleRealloc(new_cap);
		}

		vector &operator=(const vector& cpy)
		{
			if (cpy == *this)
				return (*this);
			clear();
			assign(cpy.begin(), cpy.end());
			return (*this);
		}

		reference at(size_type pos)
		{
			if (!(pos < size()))
				throw std::out_of_range("out_of_range");
			return *(mBeginIt + pos);
		}

		const_reference at(size_type pos) const
		{
			if (!(pos < size()))
				throw std::out_of_range("out_of_range");
			return *(mBeginIt + pos);
		}

		reference	front() { return *mBeginIt;}
		const_reference front() const{ return *mBeginIt;}
		reference	back() { return *(mBeginIt + mSize - 1);}
		const_reference back() const{ return *(mBeginIt + mSize - 1);}
		size_type	size() const { return mSize;}
		size_type	max_size() const { return mAlloc.max_size();}
		size_type	capacity() const { return mCapacity;}
	};

	template<class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (lhs.size() != rhs.size() || !equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

}
