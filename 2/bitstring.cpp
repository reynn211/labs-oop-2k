#include "bitstring.h"
#include <stdexcept>
#include <algorithm>

// Вспомогательные функции
void BitString::allocate(size_t size) {
    data = new unsigned char[size];
    length = size;
}

void BitString::deallocate() {
    delete[] data;
    data = nullptr;
    length = 0;
}

bool BitString::isValidBitString(const unsigned char* str, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }
    return true;
}

// Конструктор по умолчанию
BitString::BitString() : data(nullptr), length(0) {
    allocate(1);
    data[0] = '0';
}

// Конструктор из строки
BitString::BitString(const unsigned char* t) {
    length = 0;
    while (t[length] != '\0') {
        ++length;
    }
    
    if (!isValidBitString(t, length)) {
        throw std::invalid_argument("String must contain only '0' and '1'");
    }
    
    allocate(length);
    for (size_t i = 0; i < length; ++i) {
        data[i] = t[i];
    }
}

// Конструктор копирования
BitString::BitString(const BitString& other) {
    allocate(other.length);
    for (size_t i = 0; i < length; ++i) {
        data[i] = other.data[i];
    }
}

// Конструктор перемещения
BitString::BitString(BitString&& other) noexcept : data(other.data), length(other.length) {
    other.data = nullptr;
    other.length = 0;
}

// Деструктор
BitString::~BitString() noexcept {
    deallocate();
}

// Оператор присваивания копированием
BitString& BitString::operator=(const BitString& other) {
    if (this != &other) {
        deallocate();
        allocate(other.length);
        for (size_t i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

// Оператор присваивания перемещением
BitString& BitString::operator=(BitString&& other) noexcept {
    if (this != &other) {
        deallocate();
        data = other.data;
        length = other.length;
        other.data = nullptr;
        other.length = 0;
    }
    return *this;
}

// Оператор сложения
BitString BitString::operator+(const BitString& other) const {
    size_t max_length = std::max(length, other.length) + 1;
    unsigned char* result = new unsigned char[max_length];

    int carry = 0;
    int i = length - 1;
    int j = other.length - 1;
    int k = max_length - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        if (i >= 0) sum += data[i] - '0';
        if (j >= 0) sum += other.data[j] - '0';
        
        result[k] = (sum % 2) + '0';
        carry = sum / 2;
        
        i--; j--; k--;
    }

    // Удаление ведущих нулей
    int start = 0;
    while (start < max_length - 1 && result[start] == '0') start++;

    BitString bs;
    bs.deallocate();
    bs.length = max_length - start;
    bs.data = new unsigned char[bs.length];
    for (size_t i = 0; i < bs.length; i++) {
        bs.data[i] = result[start + i];
    }

    delete[] result;
    return bs;
}

// Оператор вычитания
BitString BitString::operator-(const BitString& other) const {
    if (*this < other) {
        throw std::runtime_error("Cannot subtract a larger BitString from a smaller one");
    }

    unsigned char* result = new unsigned char[length];

    int borrow = 0;
    int i = length - 1;
    int j = other.length - 1;
    int k = length - 1;

    while (i >= 0) {
        int diff = (data[i] - '0') - borrow;
        if (j >= 0) diff -= (other.data[j] - '0');

        if (diff < 0) {
            diff += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result[k] = diff + '0';
        i--; j--; k--;
    }

    // Удаление ведущих нулей
    int start = 0;
    while (start < length - 1 && result[start] == '0') start++;

    BitString bs;
    bs.deallocate();
    bs.length = length - start;
    bs.data = new unsigned char[bs.length];
    for (size_t i = 0; i < bs.length; i++) {
        bs.data[i] = result[start + i];
    }

    delete[] result;
    return bs;
}

// Оператор +=
BitString& BitString::operator+=(const BitString& other) {
    *this = *this + other;
    return *this;
}

// Оператор -=
BitString& BitString::operator-=(const BitString& other) {
    *this = *this - other;
    return *this;
}

// Оператор >
bool BitString::operator>(const BitString& other) const {
    if (length != other.length) {
        return length > other.length;
    }
    for (size_t i = 0; i < length; ++i) {
        if (data[i] != other.data[i]) {
            return data[i] > other.data[i];
        }
    }
    return false;
}

// Оператор <
bool BitString::operator<(const BitString& other) const {
    if (length != other.length) {
        return length < other.length;
    }
    for (size_t i = 0; i < length; ++i) {
        if (data[i] != other.data[i]) {
            return data[i] < other.data[i];
        }
    }
    return false;
}

// Оператор ==
bool BitString::operator==(const BitString& other) const {
    if (length != other.length) {
        return false;
    }
    for (size_t i = 0; i < length; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

// Оператор побитового И
BitString BitString::operator&(const BitString& other) const {
    size_t min_length = std::min(length, other.length);
    unsigned char* result = new unsigned char[min_length + 1];
    result[min_length] = '\0';

    for (size_t i = 0; i < min_length; ++i) {
        result[i] = ((data[length - min_length + i] - '0') & (other.data[other.length - min_length + i] - '0')) + '0';
    }

    BitString bs(result);
    delete[] result;
    return bs;
}

// Оператор побитового ИЛИ
BitString BitString::operator|(const BitString& other) const {
    size_t max_length = std::max(length, other.length);
    unsigned char* result = new unsigned char[max_length + 1];
    result[max_length] = '\0';

    for (size_t i = 0; i < max_length; ++i) {
        unsigned char bit1 = (i < length) ? data[length - 1 - i] : '0';
        unsigned char bit2 = (i < other.length) ? other.data[other.length - 1 - i] : '0';
        result[max_length - 1 - i] = ((bit1 - '0') | (bit2 - '0')) + '0';
    }

    BitString bs(result);
    delete[] result;
    return bs;
}

// Оператор побитового исключающего ИЛИ
BitString BitString::operator^(const BitString& other) const {
    size_t max_length = std::max(length, other.length);
    unsigned char* result = new unsigned char[max_length + 1];
    result[max_length] = '\0';

    for (size_t i = 0; i < max_length; ++i) {
        unsigned char bit1 = (i < length) ? data[length - 1 - i] : '0';
        unsigned char bit2 = (i < other.length) ? other.data[other.length - 1 - i] : '0';
        result[max_length - 1 - i] = ((bit1 - '0') ^ (bit2 - '0')) + '0';
    }

    BitString bs(result);
    delete[] result;
    return bs;
}

// Оператор побитового НЕ
BitString BitString::operator~() const {
    unsigned char* result = new unsigned char[length + 1];
    result[length] = '\0';

    for (size_t i = 0; i < length; ++i) {
        result[i] = (data[i] == '0') ? '1' : '0';
    }

    BitString bs(result);
    delete[] result;
    return bs;
}

// Получение размера битовой строки
size_t BitString::size() const {
    return length;
}

// Получение бита по индексу
unsigned char BitString::get(size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Установка бита по индексу
void BitString::set(size_t index, unsigned char value) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    if (value != '0' && value != '1') {
        throw std::invalid_argument("Value must be '0' or '1'");
    }
    data[index] = value;
}
