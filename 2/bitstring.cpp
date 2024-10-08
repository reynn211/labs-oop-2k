#include "bitstring.h"
#include <stdexcept>
#include <algorithm>

// Конструктор по умолчанию
BitString::BitString() : data("") {}

// Конструктор из строки
BitString::BitString(const std::string& t) : data(t) {
    for (char c : data) {
        if (c != '0' && c != '1') {
            throw std::invalid_argument("String must contain only '0' and '1'");
        }
    }
}

// Конструктор копирования
BitString::BitString(const BitString& other) : data(other.data) {}

// Конструктор перемещения
BitString::BitString(BitString&& other) noexcept : data(std::move(other.data)) {}

// Деструктор
BitString::~BitString() noexcept {}

// Оператор присваивания копированием
BitString& BitString::operator=(const BitString& other) {
    if (this != &other) {
        data = other.data;
    }
    return *this;
}

// Оператор присваивания перемещением
BitString& BitString::operator=(BitString&& other) noexcept {
    if (this != &other) {
        data = std::move(other.data);
    }
    return *this;
}

// Оператор сложения
BitString BitString::operator+(const BitString& other) const {
    std::string result;
    int carry = 0;
    int i = data.length() - 1;
    int j = other.data.length() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        if (i >= 0) sum += data[i] - '0';
        if (j >= 0) sum += other.data[j] - '0';
        
        result = char((sum % 2) + '0') + result;
        carry = sum / 2;
        
        i--; j--;
    }

    // Удаление ведущих нулей
    result.erase(0, result.find_first_not_of('0'));
    if (result.empty()) result = "0";

    return BitString(result);
}

// Оператор вычитания
BitString BitString::operator-(const BitString& other) const {
    if (*this < other) {
        throw std::runtime_error("Cannot subtract a larger BitString from a smaller one");
    }

    std::string result;
    int borrow = 0;
    int i = data.length() - 1;
    int j = other.data.length() - 1;

    while (i >= 0) {
        int diff = (data[i] - '0') - borrow;
        if (j >= 0) diff -= (other.data[j] - '0');

        if (diff < 0) {
            diff += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result = char(diff + '0') + result;
        i--; j--;
    }

    result.erase(0, result.find_first_not_of('0'));
    if (result.empty()) result = "0";

    return BitString(result);
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
    if (data.length() != other.data.length()) { // (Сравнение по длине)
        return data.length() > other.data.length();
    }
    return data > other.data; // (Лексикографическое сравнение)
}

// Оператор <
bool BitString::operator<(const BitString& other) const {
    if (data.length() != other.data.length()) {
        return data.length() < other.data.length();
    }
    return data < other.data;
}

// Оператор ==
bool BitString::operator==(const BitString& other) const {
    return data == other.data;
}

// Оператор побитового И
BitString BitString::operator&(const BitString& other) const {
    std::string result;
    int i = data.length() - 1;
    int j = other.data.length() - 1;

    while (i >= 0 && j >= 0) {
        result = char(((data[i] - '0') & (other.data[j] - '0')) + '0') + result;
        i--; j--;
    }

    return BitString(result);
}

// Оператор побитового ИЛИ
BitString BitString::operator|(const BitString& other) const {
    std::string result;
    int i = data.length() - 1;
    int j = other.data.length() - 1;

    while (i >= 0 || j >= 0) {
        int bit1 = (i >= 0) ? (data[i] - '0') : 0;
        int bit2 = (j >= 0) ? (other.data[j] - '0') : 0;
        result = char((bit1 | bit2) + '0') + result;
        i--; j--;
    }

    return BitString(result);
}

// Оператор побитового исключающего ИЛИ
BitString BitString::operator^(const BitString& other) const {
    std::string result;
    int i = data.length() - 1;
    int j = other.data.length() - 1;

    while (i >= 0 || j >= 0) {
        int bit1 = i >= 0 ? data[i] - '0' : 0;
        int bit2 = j >= 0 ? other.data[j] - '0' : 0;
        result = char((bit1 ^ bit2) + '0') + result;
        i--; j--;
    }

    return BitString(result);
}

// Оператор побитового НЕ
BitString BitString::operator~() const {
    std::string result = data;
    for (char& c : result) {
        c = (c == '0') ? '1' : '0';
    }
    return BitString(result);
}

// Получение размера битовой строки
size_t BitString::size() const {
    return data.length();
}

// Получение бита по индексу
char BitString::get(size_t index) const {
    if (index >= data.length()) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Установка бита по индексу
void BitString::set(size_t index, char value) {
    if (index >= data.length()) {
        throw std::out_of_range("Index out of range");
    }
    data[index] = (value == '1') ? '1' : '0';
}