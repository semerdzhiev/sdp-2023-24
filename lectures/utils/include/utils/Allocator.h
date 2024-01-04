#pragma once

#include <unordered_set>
#include <utility>
#include <stdexcept>

template <typename T>
class SimpleAllocator {
public: 
    template<typename...Args>
    T* buy(Args&&...args)
    {
        return new T(std::forward<Args>(args)...);
    }

    void release(T* ptr)
    {
        delete ptr;
    }
};

template <typename T>
class DebugAllocator {
    std::unordered_set<T*> allocations = std::unordered_set<T*>();
    size_t totalAllocations = 0;
    size_t failAfter = std::numeric_limits<size_t>::max();

public:

    DebugAllocator() = default;

    DebugAllocator(size_t failAfter)
        : failAfter(failAfter)
    {
    }

    template<typename...Args>
    T* buy(Args&&...args)
    {
        if(totalAllocations >= failAfter)
            throw std::bad_alloc();
            
        T* newItem = new T(std::forward<Args>(args)...);
        ++totalAllocations;
        return *allocations.insert(newItem).first;        
    }

    void release(T* ptr)
    {
        if( ! ptr ) // do nothing when ptr == nullptr
            return;

        if(allocations.count(ptr) == 0)
            throw std::invalid_argument("Trying to release a pointer not returned by this allocator");

        delete ptr;
        allocations.erase(ptr);
    }

    size_t activeAllocationsCount() const noexcept
    {
        return allocations.size();
    }

    size_t totalAllocationsCount() const noexcept
    {
        return totalAllocations;
    }
};