#include "iterator.hpp"
#include "vector.hpp"
#include <iterator>
#include <vector>
#include <iostream>
#include <list>

int main ()
{
	ft::vector<int> a;
	a.push_back(0);
	a.push_back(1);
	a.push_back(2);
	a.erase(a.begin(), a.begin() + 1);
	std::list<int> b;
	b.insert(b.begin(),0);
	b.insert(b.begin(),1);
	b.insert(b.begin(),2);
	a.insert(a.begin(), b.begin(), b.end());
	for (size_t i = 0; i < a.size(); i++)
	{
		std::cout << a[i] << std::endl;
	}

}
