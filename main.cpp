#include <iostream>
#include <vector>
#include <map>
#include <new>
#include "myalocator.h"
#include "unlist.h"

int main(int, char**)
{
  
      std::vector<std::string, Myallocator<std::string>> list;
        for(std::size_t i =0; i < 5; ++i)
         list.push_back("i");
    std::cout << list[0] << std::endl;
   

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