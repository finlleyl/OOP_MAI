#include "custom_mr.hpp"
#include <memory_resource>
#include <list>
#include <cstddef>

CustomMemoryResource::CustomMemoryResource() = default;

CustomMemoryResource::~CustomMemoryResource() {
    for (const auto& [ptr, size] : allocated_blocks_) {
        ::operator delete(ptr, std::align_val_t{size.alignment});
    }

    for (const auto& [ptr, info] : cleared_blocks_) {
        ::operator delete(ptr, std::align_val_t{info.alignment});
    }
}

void * CustomMemoryResource::do_allocate(std::size_t _bytes, std::size_t _alignment) {
    for (auto it = cleared_blocks_.begin(); it != cleared_blocks_.end(); ++it) {
        if (it->second.size >= _bytes && it->second.alignment == _alignment) {
            void* ptr = it->first;
            allocated_blocks_[ptr] = it->second;
            cleared_blocks_.erase(it);
            return ptr;
        }
    }

    void* ptr = ::operator new(_bytes, std::align_val_t{_alignment});
    allocated_blocks_[ptr] = {_bytes, _alignment};

    return ptr;
}

void CustomMemoryResource::do_deallocate(void *_ptr, std::size_t _bytes, std::size_t _alignment) {
    auto it = allocated_blocks_.find(_ptr);
    if (it != allocated_blocks_.end()) {
        cleared_blocks_[_ptr] = it->second;
        allocated_blocks_.erase(it);
    }
}

bool CustomMemoryResource::do_is_equal(const std::pmr::memory_resource &other) const noexcept {
    return this == &other;
}



