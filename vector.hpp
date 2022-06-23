#pragma once
#include "iterator.hpp"
#include <memory>

namespace ft{
template<
    class T,
    class Allocator = std::allocator<T>
> class vector{
	private:
		size_t	size;
	public:
		typedef value_type				T;
		typedef allocator_type			Allocator;
		typedef pointer					typename Allocator::pointer;
		typedef const_pointer			typename Allocator::const_pointer;
		typedef reference				value_type&;
		typedef const_reference			const value_type&;
		typedef size_type				size() const;
		typedef difference_type			std::ptrdiff_t;
		typedef iterator				= /* implementation-defined */;
		typedef const_iterator			= /* implementation-defined */;
		typedef reverse_iterator		= std::reverse_iterator<iterator>; // TMP need to reimplement
		typedef const_reverse_iterator	= std::reverse_iterator<const_iterator>; // TMP need to reimplement

	size_t size() {return this->size;};
};
}
