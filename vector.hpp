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
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef std::size_t								size_type;
		typedef std::ptrdiff_t							difference_type;
		typedef ft::iterator_traits<value_type>			iterator;
		typedef ft::iterator_traits<const value_type>	const_iterator;
		typedef std::reverse_iterator<iterator>			reverse_iterator; // TMP need to reimplement
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator; // TMP need to reimplement
	};
}
