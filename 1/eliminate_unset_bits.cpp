#include "eliminate_unset_bits.h"
#include <cmath>

long eliminate_unset_bits(std::string number) {
    long result = 0;
    int power = 0;
    
    for (auto it = number.rbegin(); it != number.rend(); ++it) {
        if (*it == '1' && power < 8) {
            result += std::pow(2, power);
            power++;
        }
    }
    
    return result;
}