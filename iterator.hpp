#pragma once
#include <iterator>

namespace ft
{
	template< class Iter >
	struct iterator_traits{
		typedef iterator_category	Iter::Category;
		typedef value_type			Iter::T;
		typedef difference_type		Iter::Distance;
		typedef pointer				Iter::Pointer;
		typedef Reference			Iter::Reference;
	};
} // namespace ft
