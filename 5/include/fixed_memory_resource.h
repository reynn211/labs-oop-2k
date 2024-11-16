#pragma once
#include <memory_resource>
#include <vector>
#include <cstddef>

class FixedMemoryResource : public std::pmr::memory_resource {
private:
    struct Block {
        void* ptr;
        std::size_t size;
        bool in_use;
    };

    char* memory_pool_;
    std::size_t pool_size_;
    std::vector<Block> blocks_;

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

public:
    explicit FixedMemoryResource(std::size_t pool_size);
    ~FixedMemoryResource();
}; 