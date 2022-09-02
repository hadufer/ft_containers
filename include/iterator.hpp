#pragma once
#include <iterator>
#include <vector>
#include <map>

namespace ft
{
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template< class Iter >
	struct iterator_traits{
		typedef typename	Iter::difference_type		difference_type;
		typedef typename	Iter::value_type			value_type;
		typedef typename	Iter::pointer				pointer;
		typedef typename	Iter::reference				reference;
		typedef typename	Iter::iterator_category		iterator_category;
	};

	template< class T >
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag		iterator_category;
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T*								pointer;
		typedef T&								reference;
	};

	template< class T >
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag		iterator_category;
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
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

	template< class InputIt >
	typename iterator_traits<InputIt>::difference_type
	distance(InputIt first, InputIt last )
	{
		typename iterator_traits<InputIt>::difference_type df_type = 0;
		for(; first != last; first++)
		{
			df_type++;
		}
		return (df_type);
	}

	template <typename T>
	class random_access_iterator : iterator<random_access_iterator_tag, T>
	{
		public:
			typedef typename iterator<random_access_iterator_tag, T>::iterator_category				iterator_category;
			typedef typename iterator<random_access_iterator_tag, T>::value_type					value_type;
			typedef typename iterator<random_access_iterator_tag, T>::difference_type				difference_type;
			typedef T*																				pointer;
			typedef T&																				reference;
		private:
			pointer mOPtr;
		public:
			random_access_iterator() : mOPtr(NULL) {}
			random_access_iterator(pointer ptr) : mOPtr(ptr) {}
			random_access_iterator(const random_access_iterator &it) : mOPtr(it.mOPtr) {}
		
			pointer base() const { return this->mOPtr;}
			random_access_iterator &operator=(const random_access_iterator &it)
			{
				if (this != &it)
					this->mOPtr = it.mOPtr;
				return *this;
			}
			reference operator*() { return *(this->mOPtr); }
			reference operator*() const { return *(this->mOPtr); }
			reference operator[](difference_type n) { return *(this->mOPtr + n);}
			reference operator[](difference_type n) const { return *(this->mOPtr + n);}
			pointer operator->() const { return this->mOPtr ;}
			operator random_access_iterator<const T>() { return random_access_iterator<const T>(this->mOPtr);}
			bool operator==(const random_access_iterator &it) const { return (this->mOPtr == it.mOPtr);}
			bool operator==(random_access_iterator<const T> &it) const { return (this->mOPtr == it.base());}
			bool operator!=(const random_access_iterator &it) const { return (this->mOPtr != it.mOPtr);}
			bool operator!=(random_access_iterator<const T> &it) const { return (this->mOPtr != it.base());}
			bool operator<(const random_access_iterator &it) const { return (this->mOPtr < it.mOPtr);}
			bool operator<(random_access_iterator<const T> &it) const { return (this->mOPtr < it.mOPtr);}
			bool operator>(const random_access_iterator &it) const { return (this->mOPtr > it.mOPtr);}
			bool operator>(random_access_iterator<const T> &it) const {return (this->mOPtr > it.base());}
			bool operator>=(const random_access_iterator &it) const { return (this->mOPtr >= it.mOPtr);}
			bool operator>=(random_access_iterator<const T> &it) const { return (this->mOPtr >= it.mOPtr);}
			bool operator<=(const random_access_iterator &it) const { return (this->mOPtr <= it.mOPtr);}
			bool operator<=(random_access_iterator<const T> &it) const { return (this->mOPtr <= it.mOPtr);}
			random_access_iterator operator+(difference_type n) const { return (this->mOPtr + n);}
			random_access_iterator operator-(difference_type n) const { return (this->mOPtr - n);}
			random_access_iterator& operator++() {this->mOPtr += 1; return *this;}
			random_access_iterator operator++(int) {random_access_iterator ret(*this); this->mOPtr += 1; return ret;}
			random_access_iterator& operator--() {this->mOPtr -= 1; return *this;}
			random_access_iterator operator--(int) {random_access_iterator ret(*this); this->mOPtr -= 1; return ret;}
			random_access_iterator& operator+=(difference_type n) {this->mOPtr += n; return *this;}
			random_access_iterator& operator-=(difference_type n) {this->mOPtr -= n; return *this;}
	};

	template <typename T>
	bool operator==(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename T1, typename T2>
	bool operator==(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename T>
	bool operator!=(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename T1, typename T2>
	bool operator!=(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename T>
	bool operator<(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename T1, typename T2>
	bool operator<(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename T>
	bool operator>(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename T1, typename T2>
	bool operator>(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename T>
	bool operator<=(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename T1, typename T2>
	bool operator<=(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename T>
	bool operator>=(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename T1, typename T2>
	bool operator>=(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename T>
	random_access_iterator<T>
	operator+(typename random_access_iterator<T>::difference_type n, typename ft::random_access_iterator<T>& it)
	{
		return (it.base() + n);
	}

	template <typename T1, typename T2>
	typename random_access_iterator<T1>::difference_type
	operator+(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
	{
		return (lhs.base() + rhs.base());
	}

	template <typename T1, typename T2>
	random_access_iterator<T1>
	operator-(typename random_access_iterator<T1>::difference_type n, typename ft::random_access_iterator<T2>& it)
	{
		return (it.base() - n);
	}

	template <typename T1, typename T2>
	typename random_access_iterator<T1>::difference_type
	operator-(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template <class T>
	class reverse_iterator
	{
		public:
			typedef T												iterator_type;
			typedef typename iterator_traits<T>::iterator_category	iterator_category;
			typedef typename iterator_traits<T>::value_type			value_type;
			typedef typename iterator_traits<T>::difference_type	difference_type;
			typedef typename iterator_traits<T>::pointer			pointer;
			typedef typename iterator_traits<T>::reference			reference;
		private:
			T	mItType;
		public:
			reverse_iterator() : mItType() {}

			explicit reverse_iterator(iterator_type it) : mItType(it) {}

			template <class It>
			reverse_iterator(const reverse_iterator<It> &cpy) : mItType(cpy.base()) {}

			template<class It>
			reverse_iterator &operator=(const reverse_iterator<It> &cpy)
			{
				if (*this != cpy)
					mItType = cpy.base();
				return *this;
			}

			iterator_type base() const	{return mItType; }

			reference operator*() const
			{
				iterator_type tmp(mItType);
				--tmp;
				return *tmp;
			}

			pointer	operator->() const
			{
				iterator_type tmp(mItType);
				tmp--;
				return to_pointer(tmp);
			}

			reverse_iterator operator+(difference_type n) const {return(reverse_iterator(mItType - n)); }
			reverse_iterator operator-(difference_type n) const {return(reverse_iterator(mItType + n)); }
			difference_type operator-(reverse_iterator rhs) {return(-ft::distance(rhs.mItType, mItType)); }
			
			reverse_iterator& operator++()
			{
				mItType--;
				return *this;
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmpIt = *this;
				mItType--;
				return tmpIt;
			}

			reverse_iterator& operator--()
			{
				mItType++;
				return *this;
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmpIt = *this;
				mItType++;
				return tmpIt;
			}

			reverse_iterator& operator+=(difference_type n)
			{
				mItType -= n;
				return *this;
			}

			reverse_iterator& operator-=(difference_type n)
			{
				mItType += n;
				return *this;
			}

			const reference operator[](difference_type n) const
			{
				return *(mItType - n - 1);
			}
			private:
				template<typename T1>
				static T1* to_pointer(T1* p)
				{
					return p;
				}
				template<typename T1>
				static pointer to_pointer(T1 t)
				{
					return t.operator->();
				}
	};

	template <class It>
	bool operator==(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<class T1, class T2>
	bool operator==(const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<class T1, class T2>
	bool operator!=(const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<class T1, class T2>
	bool operator<(const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<class T1, class T2>
	bool operator>(const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<class T1, class T2>
	bool operator<=(const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<class T1, class T2>
	bool operator>=(const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template<class It>
	reverse_iterator<It>
	operator+(typename reverse_iterator<It>::difference_type n, const reverse_iterator<It>& it)
	{
		return (it + n);
	}

	template<class It>
	typename reverse_iterator<It>::difference_type
	operator+(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
	{
		return (lhs.base() + rhs.base());
	}

	template<class It>
	reverse_iterator<It>
	operator-(typename reverse_iterator<It>::difference_type n, const reverse_iterator<It>& it)
	{
		return (it.base() - n);
	}

	template<class It>
	typename reverse_iterator<It>::difference_type
	operator-(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
	{
		return (rhs.base() - lhs.base());
	}

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (comp(*first1, *first2)) return true;
			if (comp(*first2, *first1)) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
}
