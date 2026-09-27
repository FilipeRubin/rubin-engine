#pragma once
#include <algorithm>
#include <initializer_list>

template<typename T>
class FixedArray
{
public:
	FixedArray(size_t elementCount) :
		m_data(new T[elementCount]),
		m_size(elementCount)
	{
	}

	FixedArray(std::initializer_list<T> values) :
		m_data(new T[values.size()]),
		m_size(values.size())
	{
		std::copy(values.begin(), values.end(), m_data);
	}

	FixedArray(const FixedArray& other) :
		m_data(new T[other.m_size]),
		m_size(other.m_size)
	{
		std::copy(other.m_data, other.m_data + m_size, m_data);
	}

	FixedArray(FixedArray&& other) noexcept :
		m_data(other.m_data),
		m_size(other.m_size)
	{
		other.m_data = nullptr;
		other.m_size = 0ULL;
	}

	~FixedArray()
	{
		delete[] m_data;
	}

	FixedArray& operator=(const FixedArray& other)
	{
		if (this != &other)
		{
			delete[] m_data;
			
			m_data = new T[other.m_size];
			m_size = other.m_size;
			std::copy(other.m_data, other.m_data + m_size, m_data);
		}
		return *this;
	}

	FixedArray& operator=(FixedArray&& other) noexcept
	{
		if (this != &other)
		{
			delete[] m_data;

			m_data = other.m_data;
			m_size = other.m_size;
			
			other.m_data = nullptr;
			other.m_size = 0ULL;
		}
		return *this;
	}

	T& operator[](size_t index) noexcept
	{
		return m_data[index];
	}

	const T& operator[](size_t index) const noexcept
	{
		return m_data[index];
	}

	size_t GetSize() const
	{
		return m_size;
	}

	T* GetData()
	{
		return m_data;
	}

	const T* GetData() const
	{
		return m_data;
	}
private:
	T* m_data;
	size_t m_size;
};
