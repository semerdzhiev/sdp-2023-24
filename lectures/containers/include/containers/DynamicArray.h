#pragma once

#include "FixedSizeArray.h"

template <typename T>
class DynamicArray {

	FixedSizeArray<T> m_data;
	size_t m_used = 0;

public:

	/// Thrown when an operation, that requires the array to have at least one element,
	/// was performed on an empty array.
	class EmptyArrayException : public std::logic_error {
	public:
		EmptyArrayException()
			: std::logic_error("Operation was performed on an empty array")
		{}
	};

public:
	/// Constructs an empty array with zero capacity
	DynamicArray() = default;

	/// Constructs an array with size and capacity equal to initialSize
	/// @exception std::bad_alloc Memory allocation failed
	DynamicArray(size_t initialCapacity)
		: m_data(initialCapacity), m_used(initialCapacity)
	{}

	DynamicArray(const DynamicArray&) = default;
	DynamicArray& operator=(const DynamicArray&) = default;
	
	DynamicArray(DynamicArray&& other)
		: m_data(std::move(other.m_data))
	{
		m_used = other.m_used;
		other.m_used = 0;
	}

	DynamicArray& operator=(DynamicArray&& other)
	{
		if (this != &other) {
			m_data = std::move(other.m_data);
			m_used = other.m_used;
			other.m_used = 0;
		}
		
		return *this;
	}

	/// Number of elements stored in the array
	size_t size() const noexcept {
		return m_used;
	}

	/// Size of the underlying buffer
	size_t capacity() const noexcept {
		return m_data.size();
	}

	/// Retrieve the element at index 
	/// @exception std::out_of_range If the index is out of the bounds of the array 
	T& at(size_t index)
	{
		return m_data.at(index);
	}

	/// Retrieve the element at index 
	/// @exception std::out_of_range If the index is out of the bounds of the array 
	const T& at(size_t index) const
	{
		return m_data.at(index);
	}

	/// Retrieve the element at index 
	T& operator[](size_t index)
	{
		return m_data[index];
	}
	
	/// Retrieve the element at index 
	const T& operator[](size_t index) const
	{
		return m_data[index];
	}

	/// Retrieve the underlying buffer
	T* data() noexcept
	{
		return m_data.data();
	}

	/// Retrieve the underlying buffer
	const T* data() const noexcept
	{
		return m_data.data();
	}

	/// Append value to the array
	void push_back(const T& value)
	{
		reserve(m_used + 1);
		m_data[m_used++] = value;
	}

	/// Remove the last element from the array
	void pop_back()
	{
		if (m_used == 0)
			throw EmptyArrayException();

		--m_used;
	}

	/// Ensure the underlying buffer has at least a minimal capacity
	void reserve(size_t desiredCapacity)
	{
		if (desiredCapacity <= capacity())
			return;

		size_t newCapacity = std::max(desiredCapacity, capacity() * 2);
		
		FixedSizeArray<T> buffer(newCapacity);
		buffer.fillFrom(m_data);
		m_data = std::move(buffer);
	}
	
	/// Set the size of the array to a specific value.
	void resize(size_t desiredSize)
	{
		reserve(desiredSize);
		m_used = desiredSize;
	}

	/// If possible, reduce the memory used by the array
	void shrink_to_fit()
	{
		FixedSizeArray<T> buffer(m_used);
		buffer.fillFrom(m_data);
		m_data = std::move(buffer);
	}

	/// Quickly swaps the contents of this object with that of another
	void swap(DynamicArray& other)
	{
		m_data.swap(other.m_data);
		std::swap(m_used, other.m_used);
	}
};
