#include <iostream>
#include "fixed_memory_resource.h"
#include "forward_list.h"

struct TestStruct {
    int x;
    double y;
    std::string z;
};

int main() {
    FixedMemoryResource resource(1024);

    ForwardList<int> list_int(&resource);
    
    list_int.push_front(1);
    list_int.push_front(2);
    list_int.push_front(3);

    std::cout << "Список целых чисел: ";
    for (const auto& value : list_int) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    ForwardList<TestStruct> list_struct(&resource);
    
    list_struct.push_front({1, 1.1, "один"});
    list_struct.push_front({2, 2.2, "два"});

    std::cout << "Список структур: \n";
    for (const auto& value : list_struct) {
        std::cout << "x: " << value.x << ", y: " << value.y 
                  << ", z: " << value.z << "\n";
    }

    return 0;
} 