#pragma once
#include "vector.hpp"
#include "iterator.hpp"

namespace ft {
	template<
	class T,
	class Container = ft::vector<T>
	> class stack
	{
		public:
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;
		protected:
			Container mContainer;
		public:
			explicit stack(const container_type& cont = Container())
				: mContainer(cont)
			{}

			stack& operator=( const stack& other )
			{
				mContainer = other.mContainer;
				return (*this);
			}

			reference top() { return (mContainer.back());}

			const_reference top() const { return (mContainer.back());};

			bool empty() const { return mContainer.empty();}

			size_type size() const { return mContainer.size();}

			void push(const value_type& value) { mContainer.push_back(value);}

			void pop() { mContainer.pop_back();};

			template<class Type, class CContainer>
			friend bool operator==(const ft::stack<Type, CContainer>& lhs, const ft::stack<Type, CContainer>& rhs);

			template<class Type, class CContainer>
			friend bool operator!=(const ft::stack<Type, CContainer>& lhs, const ft::stack<Type, CContainer>& rhs);

			template<class Type, class CContainer>
			friend bool operator<(const ft::stack<Type, CContainer>& lhs, const ft::stack<Type, CContainer>& rhs);

			template<class Type, class CContainer>
			friend bool operator>(const ft::stack<Type, CContainer>& lhs, const ft::stack<Type, CContainer>& rhs);

			template<class Type, class CContainer>
			friend bool operator<=(const ft::stack<Type, CContainer>& lhs, const ft::stack<Type, CContainer>& rhs);

			template<class Type, class CContainer>
			friend bool operator>=(const ft::stack<Type, CContainer>& lhs, const ft::stack<Type, CContainer>& rhs);
	};

	template<class T, class Container>
	bool operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return (lhs.mContainer == rhs.mContainer);
	}

	template<class T, class Container>
	bool operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return (lhs.mContainer != rhs.mContainer);
	}

	template<class T, class Container>
	bool operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return (lhs.mContainer < rhs.mContainer);
	}

	template<class T, class Container>
	bool operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return (lhs.mContainer > rhs.mContainer);
	}

	template<class T, class Container>
	bool operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return (lhs.mContainer <= rhs.mContainer);
	}

	template<class T, class Container>
	bool operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return (lhs.mContainer >= rhs.mContainer);
	}
}