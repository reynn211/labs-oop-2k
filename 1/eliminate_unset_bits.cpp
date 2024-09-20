#include "eliminate_unset_bits.h"
#include <cmath>
#include <stdexcept>

long eliminate_unset_bits(std::string number) {
    long result = 0;
    int power = 0;
    
    for (int i = 0; i < number.length(); ++i) {
        if (number[i] == '1') {
            if (power < 8) {
                result += std::pow(2, power);
                power++;
            }
        } else if (number[i] != '0') {
            throw std::invalid_argument("non-binary character");
        }
    }
    
    return result;
}