#include <iostream>
#include <vector>
#include <map>
#include <list>
#include "myalocator.h"
#include "unlist.h"
#include "timer.h"


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
    std::map<int, int, std::less<int>, otus::Myallocator<int, 10>> myalloc;
   
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
    for(auto& [key, set] : myalloc)
        std::cout<< key << " " << set << std::endl;

    otus::unlist<int> myl;
    otus::unlist<int, otus::Myallocator<int, 10>> mylistalloc;

    for(std::size_t i = 0; i < 10; ++i)
    {
        myl.push_back(i);
        mylistalloc.push_back(i);
    }
    
    std::cout<< "\nMy conteiner std::alocator\n";
    for(auto& m: myl)
        std::cout<< m <<" ";
    std::cout<<std::endl;

    std::cout<< "\nMy conteiner Myalocator\n";
    for(auto it = mylistalloc.begin(); it != mylistalloc.end(); ++it)
        std::cout<< *it <<" ";
    std::cout<<std::endl;
 
    std::cout<< "\nMy Allocator test std::list\n";
    std::list<int, otus::Myallocator<int, 6>> listm;
    for(std::size_t i = 0; i < 5; ++i)
        listm.push_front(i);
    
    auto it = listm.begin();
    listm.erase(++it);
    listm.push_front(12);
    listm.push_front(10);

    for(auto& s : listm)
        std::cout<< s << " ";
    std::cout<<std::endl;
    
    std::cout<< "\nMy Allocator test std::vector\n";
    std::vector<int, otus::Myallocator<int, 64>> vecm;
        for(std::size_t i = 0; i < 60; ++i)
        {
            vecm.push_back(i);
        }
    for(auto& s : vecm)
        std::cout<< s << " ";
    std::cout<<std::endl;
    return 0;
}