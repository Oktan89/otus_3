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
int main(int, char**)
{  

 
    otus::unlist<my, Myallocator<my, 2>> test;
    for(std::size_t i = 0; i < 2; ++i)
    {
        test.push_back(i);
    }
   
    
     for(auto it = test.begin(); it != test.end(); ++it)
         std::cout<< *it << std::endl;
 
    // auto g = std::find(test.begin(), test.end(), 10);
    // std::cout<< *g << std::endl;
    // for(auto& s : test)
    //     std::cout<< s << " ";
    // std::cout<<std::endl;
 //  printlist(test);
//    std::cout<< "\n std::list\n";
    //  std::forward_list<int, Myallocator<int, 2>> tet;
     
    //  tet.push_front(10);
    //  tet.push_front(20);
     
    
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