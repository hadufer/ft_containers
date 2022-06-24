#pragma once
#include <iterator>

namespace ft
{
	template< class Iter >
	struct iterator_traits{
		typedef typename	Iter::Category		iterator_category;
		typedef typename	Iter::T				value_type;
		typedef typename	Iter::Distance		difference_type;
		typedef typename	Iter::Pointer		pointer;
		typedef typename	Iter::Reference		Reference;
	};

	template< class T >
	struct iterator_traits<T*>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T*								pointer;
		typedef T&								Reference;
	};

	template< class T >
	struct iterator_traits<const T*>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef const T*						pointer;
		typedef const T&						Reference;
	};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
		public:
			typedef T							value_type;
			typedef Distance					difference_type;
			typedef Pointer						pointer;
			typedef Reference					reference;
			typedef Category					iterator_category;
	};
} // namespace ft
