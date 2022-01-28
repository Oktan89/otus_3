#include <iostream>
#include <vector>
#include "myalocator.h"
#include "unlist.h"

int main(int, char**)
{
  
    // otus::unlist<int, Myallocator<int>> list;

    // for(std::size_t i =0; i < 50000; ++i)
    //     list.push_front(i);
    


   //Сделать резервирование памяти в самом алокаторе и уже отуда отдавать ее!!!

    std::vector<int, Myallocator<int>> vec;
    //vec.reserve(10);
    std::cout << "reserv: 10 \n";

    for(int i = 0; i < 10; ++i)
    {
        vec.emplace_back(i);
        std::cout<< i << std::endl;
    }
    return 0;
}