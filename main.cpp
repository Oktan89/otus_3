#include <iostream>
#include <vector>
#include <map>
#include <new>
#include <string>
#include <forward_list>
#include <algorithm>
#include "myalocator.h"
#include "unlist.h"

class my
{
    int b;
    friend std::ostream& operator<<(std::ostream& out, const my& m);
public:
    my(){}
    my(int a) : b(a)
    {
        std::cout<<"construct my "<<b <<"\n";
    }
    ~my()
    {
        std::cout<<"destruct ~my "<<b<<"\n";
    }
};

std::ostream& operator<<(std::ostream& out, const my& m)
{
    out << m.b;
    return out;
}

std::size_t fact(std::size_t n)
{
    std::size_t r = 1;
    for (std::size_t i = 2; i <= n; ++i)
        r *= i;
    return r;            
}


int main(int, char**)
{  

    std::map<int, int> standart;
    std::map<int, int, std::less<int>, Myallocator<int, 10>> myalloc;

    for(std::size_t i = 0; i < 10; ++i)
    {
        std::size_t f = fact(i);
        standart[i] = f;
        myalloc[i] = f;
    }

    std::cout<< "\nMAP std::alocator\n";
    for(auto& [key, set] : standart)
        std::cout<< key << " " << set << std::endl;
    
    std::cout<< "\nMAP Myalocator\n";
    for(auto& [key, set] : standart)
        std::cout<< key << " " << set << std::endl;
    
    
    otus::unlist<int> my;
    otus::unlist<int, Myallocator<int, 10>> mylistalloc;
    for(std::size_t i = 0; i < 10; ++i)
    {
        my.push_back(i);
        mylistalloc.push_back(i);
    }
    
    std::cout<< "\nMy conteiner std::alocator\n";
    for(auto& m: my)
        std::cout<< m <<std::endl;

    std::cout<< "\nMy conteiner Myalocator\n";
    for(auto it = mylistalloc.begin(); it != mylistalloc.end(); ++it)
        std::cout<< *it <<std::endl;
    
    return 0;
}