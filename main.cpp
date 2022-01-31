#include <iostream>
#include <vector>
#include <map>
#include <new>
#include <string>
#include "myalocator.h"
#include "unlist.h"


template<typename T, int te = 10>
class t
{
    const int _t;
    char buff[te];
public:
    t(int t) : _t(t) {}
};

int main(int, char**)
{       

    // otus::unlist<int, Myallocator<int>> test;
    // test.push_front(10);
      std::vector<int, Myallocator<int, 500>> list;
        for(std::size_t i =0; i < 10; ++i)
         list.push_back(i);
        //  list.push_back("Test string"+std::to_string(i));
    //std::cout << list[0] << std::endl;
   for(auto& s: list)
      std::cout<< s << " ";
    std::cout << std::endl;

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