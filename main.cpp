#include <iostream>
#include <vector>
#include <map>
#include <new>
#include <string>
#include <forward_list>
#include "myalocator.h"
#include "unlist.h"
template<typename T>
void printlist(const T& t)
{
    for(const auto& l : t)
        std::cout << l << " ";
    std::cout<<std::endl;
}   

int main(int, char**)
{  
    int t = 100;
   otus::unlist<int, Myallocator<int>> test;
   test.push_back(10);
   test.push_back(t);
   test.push_front(1000);
  
    
 

 //  printlist(test);
//    std::cout<< "\n std::list\n";
     std::forward_list<int, Myallocator<int>> tet;
//     tet.push_front(10);
//     tet.push_front(20);
    
 //   printlist(tet);

    
    // otus::unlist<int, Myallocator<int>> test;
    // test.push_front(10);
    //   std::vector<int, Myallocator<int, 500>> list;
    //     for(std::size_t i =0; i < 10; ++i)
    //      list.push_back(i);
        //  list.push_back("Test string"+std::to_string(i));
    //std::cout << list[0] << std::endl;
//    for(auto& s: list)
    //   std::cout<< s << " ";
    // std::cout << std::endl;


//    //Сделать резервирование памяти в самом алокаторе и уже отуда отдавать ее!!!

    // std::vector<int, Myallocator<int>> vec{10, 10, 10};
  
//    auto m = std::map<
// 		int,
// 		int,
// 		std::less<int>,
// 		Myallocator<
// 			std::pair<
// 				const int, int>>>{};

// 	for (int i = 0; i < 5; ++i) {
// 		m[i] = i;
// 	}

//     for(auto it = m.begin(); it != m.end(); ++it)
//         std::cout<< it->second << std::endl;

    
    return 0;
}