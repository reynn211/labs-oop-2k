#include "fixed_memory_resource.h"
#include <algorithm>
#include <cassert>

FixedMemoryResource::FixedMemoryResource(std::size_t pool_size)
    : pool_size_(pool_size) {
    memory_pool_ = new char[pool_size];
    blocks_.reserve(pool_size / 8);
    blocks_.push_back({memory_pool_, pool_size, false});
}

FixedMemoryResource::~FixedMemoryResource() {
    delete[] memory_pool_;
}

void* FixedMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    for (size_t i = 0; i < blocks_.size(); ++i) {
        auto& block = blocks_[i];
        if (!block.in_use && block.size >= bytes) {
            if (block.size > bytes) {
                blocks_.push_back({
                    static_cast<char*>(block.ptr) + bytes,
                    block.size - bytes,
                    false
                });
                block.size = bytes;
            }
            block.in_use = true;
            return block.ptr;
        }
    }
    throw std::bad_alloc();
}

void FixedMemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    for (size_t i = 0; i < blocks_.size(); ++i) {
        auto& block = blocks_[i];
        if (block.ptr == p) {
            block.in_use = false;

            if (i > 0) {
                auto& prev_block = blocks_[i - 1];
                if (!prev_block.in_use && 
                    static_cast<char*>(prev_block.ptr) + prev_block.size == block.ptr) {
                    prev_block.size += block.size;
                    blocks_.erase(blocks_.begin() + i);
                    i--;
                    block = prev_block;
                }
            }

            if (i + 1 < blocks_.size()) {
                auto& next_block = blocks_[i + 1];
                if (!next_block.in_use && 
                    static_cast<char*>(block.ptr) + block.size == next_block.ptr) {
                    block.size += next_block.size;
                    blocks_.erase(blocks_.begin() + i + 1);
                }
            }
            return;
        }
    }
    assert(false && "Некорректный указатель");
}

bool FixedMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
} 