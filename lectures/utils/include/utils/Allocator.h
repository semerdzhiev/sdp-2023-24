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
    std::unordered_set<T*> m_allocations = std::unordered_set<T*>();
    size_t m_totalAllocations = 0;
    size_t m_failAfter = std::numeric_limits<size_t>::max();

public:

    DebugAllocator() = default;

    DebugAllocator(size_t failAfter)
        : m_failAfter(failAfter)
    {
    }

    template<typename...Args>
    T* buy(Args&&...args)
    {
        if(m_totalAllocations >= m_failAfter)
            throw std::bad_alloc();
            
        T* newItem = new T(std::forward<Args>(args)...);
        ++m_totalAllocations;
        return *m_allocations.insert(newItem).first;        
    }

    void release(T* ptr)
    {
        if( ! ptr ) // do nothing when ptr == nullptr
            return;

        if(m_allocations.count(ptr) == 0)
            throw std::invalid_argument("Trying to release a pointer not returned by this allocator");

        delete ptr;
        m_allocations.erase(ptr);
    }

    size_t activeAllocationsCount() const noexcept
    {
        return m_allocations.size();
    }

    size_t totalAllocationsCount() const noexcept
    {
        return m_totalAllocations;
    }

    void failAfter(size_t value)
    {
        m_failAfter = value;
    }
};