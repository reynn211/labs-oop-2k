#ifndef BITSTRING_H
#define BITSTRING_H

#include <cstddef>

class BitString {
public:
    BitString();
    BitString(const unsigned char* t);
    BitString(const BitString& other);
    BitString(BitString&& other) noexcept;
    virtual ~BitString() noexcept;

    BitString& operator=(const BitString& other);
    BitString& operator=(BitString&& other) noexcept;

    BitString operator+(const BitString& other) const;
    BitString operator-(const BitString& other) const;
    BitString& operator+=(const BitString& other);
    BitString& operator-=(const BitString& other);

    bool operator>(const BitString& other) const;
    bool operator<(const BitString& other) const;
    bool operator==(const BitString& other) const;

    BitString operator&(const BitString& other) const;
    BitString operator|(const BitString& other) const;
    BitString operator^(const BitString& other) const;
    BitString operator~() const;

    size_t size() const;
    unsigned char get(size_t index) const;
    void set(size_t index, unsigned char value);
    bool isValidBitString(const unsigned char* str, size_t len);

private:
    unsigned char* data;
    size_t length;

    void allocate(size_t size);
    void deallocate();
};

#endif