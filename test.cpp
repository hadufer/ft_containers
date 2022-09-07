
#include "iostream"
#include <string>

#include <stack>
#include <vector>
#include <map>

#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"


void    print_map(NAMESPACE::map<std::string, int>& c)
{
    NAMESPACE::map<std::string, int>::iterator it = c.begin();
    NAMESPACE::map<std::string, int>::iterator ite = c.end();

    std::cout << std::endl << "SIZE CONTAINER : " << c.size() << std::endl;
    for (; it != ite; it++)
        std::cout << (*it).first << "/" << (*it).second << std::endl;
    std::cout << std::endl;
}

void    print_stack(NAMESPACE::stack<std::string> s)
{
    std::cout << std::endl << "SIZE CONTAINER : " << s.size() << std::endl;
    while (!s.empty())
    {
        std::cout << s.top() << std::endl;
        s.pop();
    }
}

template <class T> 
void    print_container(T& c)
{
    typename T::iterator it = c.begin();
    typename T::iterator ite = c.end();

    std::cout << std::endl << "SIZE CONTAINER : " << c.size() << std::endl;
    for (; it != ite; it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;
}




int main()
{
    //VECTOR
    NAMESPACE::vector<std::string>  v;
    NAMESPACE::vector<std::string>  v2;
    for (int i = 0; i < 10; i++)
        v.insert(v.begin(), std::to_string(i));
    print_container(v);
    v.assign(2, "TEST");
    print_container(v);
    try
    {
        v.at(150);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "BACK :" << v.back() << std::endl;
    std::cout << "FRONT :" << v.front() << std::endl;
    std::cout << "EMPTY :" << v2.empty() << std::endl;
    v2 = v;
    std::cout << "EMPTY :" << v2.empty() << std::endl;
    print_container(v);
    v2.erase(v2.begin(), v2.end() - 2);
    print_container(v2);
    v2.push_back("42");
    print_container(v2);
    v2.pop_back();
    v2.pop_back();
    v2.push_back("42");
    print_container(v2);
    v.swap(v2);
    print_container(v); print_container(v2);
    v.clear();
    v2.clear();
    print_container(v); print_container(v2);
    //MAP
    std::cout << "----------------------------------" << std::endl << "MAP : " << std::endl << std::endl;
    NAMESPACE::map<std::string, int>   m;   
    NAMESPACE::map<std::string, int>   m2;
    for (int i = 0; i < 10; i++)
        m.insert(m.begin(), NAMESPACE::make_pair(std::to_string(i), i));
    print_map(m);
    std::cout << "m[1] = " << m["1"] << std::endl;
    std::cout << "ERASE 1 : " << std::endl;
    m.erase("1");
    print_map(m);
    std::cout << "FIND m[2] = " << m.find("2")->second << std::endl;
    std::cout << "LOWER BOUNDS : " << m.lower_bound("9")->second << std::endl;
    std::cout << "UPPER BOUNDS : " << m.upper_bound("8")->second << std::endl;
    m.swap(m2);
    print_map(m2);
    m2.swap(m);
    std::cout << "EMPTY : " << m.empty() << std::endl;
    m.clear();
    print_map(m);
    std::cout << "EMPTY : "<< m.empty() << std::endl;
    //STACK
    std::cout << "----------------------------------" << std::endl << "MAP : " << std::endl << std::endl;
    NAMESPACE::stack<std::string>   s;
    std::cout << "EMPTY :" << s.empty() << std::endl;
    for (int i = 0; i < 10; i++)
        s.push(std::to_string(i));
    std::cout << "EMPTY :" << s.empty() << std::endl;
    print_stack(s);
    s.pop();
    s.pop();
    print_stack(s);
    std::cout << "TOP : " << s.top() << std::endl;
}