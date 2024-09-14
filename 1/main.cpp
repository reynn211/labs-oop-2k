#include <iostream>
#include "eliminate_unset_bits.h"

int main() {
    std::string input;
    std::cin >> input;
    
    long result = eliminate_unset_bits(input);
    std::cout << result << std::endl;
    
    return 0;
}