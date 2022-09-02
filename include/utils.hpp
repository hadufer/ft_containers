#pragma once
#include <iterator>
#include <vector>
#include <map>
#include <iostream>

namespace ft {

	template<bool B, class T = void>
	struct enable_if {};
 
	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template <typename T>	struct is_integral								{ static const bool value = false;};
	template <>				struct is_integral<bool>						{ static const bool value = true;};
	template <>				struct is_integral<char>						{ static const bool value = true;};
	template <>				struct is_integral<wchar_t>						{ static const bool value = true;};
	template <>				struct is_integral<signed char>					{ static const bool value = true;};
	template <>				struct is_integral<short>						{ static const bool value = true;};
	template <>				struct is_integral<int>							{ static const bool value = true;};
	template <>				struct is_integral<long>						{ static const bool value = true;};
	template <>				struct is_integral<long long>					{ static const bool value = true;};
	template <>				struct is_integral<unsigned char>				{ static const bool value = true;};
	template <>				struct is_integral<unsigned short>				{ static const bool value = true;};
	template <>				struct is_integral<unsigned int>				{ static const bool value = true;};
	template <>				struct is_integral<unsigned long>				{ static const bool value = true;};
	template <>				struct is_integral<unsigned long long>			{ static const bool value = true;};
	template <>				struct is_integral<const bool>					{ static const bool value = true;};
	template <>				struct is_integral<const char>					{ static const bool value = true;};
	template <>				struct is_integral<const wchar_t>				{ static const bool value = true;};
	template <>				struct is_integral<const signed char>			{ static const bool value = true;};
	template <>				struct is_integral<const short>					{ static const bool value = true;};
	template <>				struct is_integral<const int>					{ static const bool value = true;};
	template <>				struct is_integral<const long>					{ static const bool value = true;};
	template <>				struct is_integral<const long long>				{ static const bool value = true;};
	template <>				struct is_integral<const unsigned char>			{ static const bool value = true;};
	template <>				struct is_integral<const unsigned short>		{ static const bool value = true;};
	template <>				struct is_integral<const unsigned>				{ static const bool value = true;};
	template <>				struct is_integral<const unsigned long>			{ static const bool value = true;};
	template <>				struct is_integral<const unsigned long long>	{ static const bool value = true;};

	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, 
			InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2) {
			if (!(*first1 == *first2)) {
				return false;
			}
		}
		return true;
	}
}









#include <map>