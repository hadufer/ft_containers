#include <map>
#include "map.hpp"
#include <iostream>

int main()
{
	ft::map<int, int> a;
	a.insert(ft::pair<int, int>(2, 3));
	a.insert(ft::pair<int, int>(4, 2));
	a.insert(ft::pair<int, int>(6, 1));
	for (auto itr = a.begin(); itr != a.end(); ++itr) {
        std::cout << '\t' << itr->first << '\t' << itr->second
             << '\n';
    }
}