#ifndef CUSTOM_MR_HPP
#define CUSTOM_MR_HPP

#include <memory_resource>
#include <list>
#include <map>
#include <cstddef>

class CustomMemoryResource : public std::pmr::memory_resource {
public:
    CustomMemoryResource();

    ~CustomMemoryResource() override;

protected:
    struct BlockInfo {
        std::size_t size;
        std::size_t alignment;
    };

    void* do_allocate(std::size_t _bytes, std::size_t _alignment) override;

    void do_deallocate(void* _ptr, std::size_t _bytes, std::size_t _alignment) override;

    [[nodiscard]] bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;


private:
    std::map<void*, BlockInfo> allocated_blocks_;
    std::map<void*, BlockInfo> cleared_blocks_;
};

#endif //CUSTOM_MR_HPP
