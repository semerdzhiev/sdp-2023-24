#pragma once

template <typename T>
class FixedSizeArray {
	T* m_data = nullptr;
	size_t m_size = 0;

public:

	/// Constructs an empty array
	FixedSizeArray() noexcept = default;

	/// Creates an array with a specified size
	/// @exception std::bad_alloc if memory allocation fails
	FixedSizeArray(size_t size)
	{
		if (size != 0) {
			m_data = new T[size];
			m_size = size;
		}
	}

	///
	/// Copies the values from another array into the current object
	/// 
	/// The function copies min(size(), other.size()) elements
	/// 
	void fillFrom(const FixedSizeArray& other)
	{
		size_t limit = std::min(size(), other.size());
			
		for (size_t i = 0; i < limit; ++i)
			m_data[i] = other.m_data[i];
	}

	/// Creates a copy of another array
	FixedSizeArray(const FixedSizeArray& other)
		: FixedSizeArray(other.m_size)
	{
		fillFrom(other);
	}

	/// Copies the contents of another array
	FixedSizeArray& operator=(const FixedSizeArray& other)
	{
		if(this != &other) {
			FixedSizeArray copy(other);
			swap(copy);
		}

		return *this;
	}

	FixedSizeArray(FixedSizeArray&& other) noexcept
	{
		swap(other);
	}

	FixedSizeArray& operator=(FixedSizeArray&& other) noexcept
	{
		FixedSizeArray temp(std::move(other));
		swap(temp);
		return *this;
	}

	~FixedSizeArray() noexcept
	{
		delete [] m_data;
	}

	size_t size() const noexcept
	{
		return m_size;
	}

	bool empty() const noexcept
	{
		return m_size == 0;
	}

	T* data() noexcept
	{
		return m_data;
	}

	const T* data() const noexcept
	{
		return m_data;
	}

	T& at(size_t index)
	{
		if (index >= m_size)
			throw std::out_of_range("index is out of the bounds of the array");

		return m_data[index];
	}

	const T& at(size_t index) const
	{
		if (index >= m_size)
			throw std::out_of_range("index is out of the bounds of the array");

		return m_data[index];
	}

	T& operator[](size_t index) noexcept
	{
		return m_data[index];
	}

	const T& operator[](size_t index) const noexcept
	{
		return m_data[index];
	}

	void swap(FixedSizeArray& other) noexcept
	{
		std::swap(m_data, other.m_data);
		std::swap(m_size, other.m_size);
	}

	///
	/// @brief Checks whether two arrays have the same size and contain the same sequence of elements
	///
	/// The elements of the array must be comparable with `==`.
	/// 
	bool operator==(const FixedSizeArray& other) const
	{
		if (size() != other.size())
			return false;
		
		for (size_t i = 0; i < size(); i++) {
			if (m_data[i] != other.m_data[i])
				return false;
		}

		return true;
	}
};