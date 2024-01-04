#pragma once

#include <algorithm>
#include <functional>
#include <vector>
#include <list>
#include <utility>
#include <stdexcept>

// Included for comparison only
template <typename ElementType>
class VectorOfUnorderedElements {
public:
    using value_type = ElementType;

private:
    std::vector<value_type> m_data;

public:
    void insert(const value_type& value)
    {
        m_data.push_back(value);
    }

    bool contains(const value_type& value) const
    {
        return std::find(m_data.begin(), m_data.end(), value) != m_data.end();
    }

    size_t size() const
    {
        return m_data.size();
    }

    double load_factor() const
    {
        return static_cast<double>(m_data.size()) / static_cast<double>(m_data.capacity());
    }
};

// Included for comparison only
template <typename ElementType>
class VectorWithBinarySearch {
public:
    using value_type = ElementType;

private:
    std::vector<value_type> m_data;

public:
    void insert(const value_type& value)
    {
        m_data.insert(std::upper_bound(m_data.begin(), m_data.end(), value), value);
    }

    bool contains(const value_type& value) const
    {
        return std::binary_search(m_data.begin(), m_data.end(), value);
    }

    size_t size() const
    {
        return m_data.size();
    }

    double load_factor() const
    {
        return static_cast<double>(m_data.size()) / static_cast<double>(m_data.capacity());
    }
};

template <typename ElementType, typename Hash = std::hash<ElementType> >
class SeparateChainingHash {
public:
    using value_type = ElementType;
    using hasher = Hash;

private:
    std::vector<std::list<ElementType>> m_buckets = std::vector<std::list<ElementType>>(8);
    mutable hasher m_hash = hasher();
    size_t m_size = 0;
    double m_maxLoadFactor = 1.0;

public:
    size_t size() const noexcept
    {
        return m_size;
    }

    double load_factor() const noexcept
    {
        return static_cast<double>(m_size) / static_cast<double>(m_buckets.size());
    }

    double max_load_factor() const noexcept
    {
        return m_maxLoadFactor;
    }

    void max_load_factor(double value)
    {
        if(value <= 0)
            throw std::invalid_argument("load factor must be a positive number");

        m_maxLoadFactor = value;
    }

    void swap(SeparateChainingHash& other) noexcept
    {
        m_buckets.swap(other.m_buckets);
        std::swap(m_hash, other.m_hash);
        std::swap(m_size, other.m_size);
    }    

private:
    size_t calculateHash(const value_type& value) const
    {
        return m_hash(value) % m_buckets.size();
    }

    bool rehashRequired() const
    {
        return max_load_factor() < (static_cast<double>(m_size + 1) / static_cast<double>(m_buckets.size()));
    }
    
    size_t howManyBucketsFor(size_t elementsCount)
    {
        return (elementsCount == 0) ? 8 : (elementsCount / max_load_factor());
    }

    void rehash(size_t bucketCount)
    {
        size_t newCount = std::max(bucketCount, howManyBucketsFor(m_size));

        // We already have enough buckets. Nothing to do.
        if(newCount <= m_buckets.size())
            return;

        SeparateChainingHash temp(bucketCount);

        for(const auto& bucket : m_buckets) {
            for(const auto & value : bucket)
                temp.insert(value);
        }

        swap(temp);
    }

    void reserve(size_t elementsCount)
    {
        rehash(static_cast<double>(elementsCount) / max_load_factor());
    }

public:
    SeparateChainingHash() = default;

    SeparateChainingHash(size_t bucketCount, hasher hash = hasher())
        : m_buckets(bucketCount == 0 ? 8 : bucketCount), m_hash(hash)
    {
        // Nothing to do here
    }

    void insert(const value_type& value)
    {
        if(rehashRequired())
            reserve(m_size * 2);

        size_t bucket = calculateHash(value);
        m_buckets[bucket].push_back(value);
        ++m_size;
    }

    bool contains(const value_type& value) const
    {
        size_t bucket = calculateHash(value);
        return std::find(m_buckets[bucket].begin(), m_buckets[bucket].end(), value) != m_buckets[bucket].end();
    }
};

