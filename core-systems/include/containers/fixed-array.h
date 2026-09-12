#pragma once
#include <algorithm>
#include <initializer_list>

template<typename T>
class FixedArray
{
public:
	FixedArray(size_t elementCount) :
		m_data(new T[elementCount]),
		m_elementCount(elementCount)
	{
	}

	FixedArray(std::initializer_list<T> values) :
		m_data(new T[values.size()]),
		m_elementCount(values.size())
	{
		std::copy(values.begin(), values.end(), m_data);
	}

	FixedArray(const FixedArray& other) :
		m_data(new T[other.m_elementCount]),
		m_elementCount(other.m_elementCount)
	{
		std::copy(other.m_data, other.m_data + m_elementCount, m_data);
	}

	FixedArray(FixedArray&& other) noexcept :
		m_data(other.m_data),
		m_elementCount(other.m_elementCount)
	{
		other.m_data = nullptr;
		other.m_elementCount = 0ULL;
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
			
			m_data = new T[other.m_elementCount];
			m_elementCount = other.m_elementCount;
			std::copy(other.m_data, other.m_data + m_elementCount, m_data);
		}
		return *this;
	}

	FixedArray& operator=(FixedArray&& other) noexcept
	{
		if (this != &other)
		{
			delete[] m_data;

			m_data = other.m_data;
			m_elementCount = other.m_elementCount;
			
			other.m_data = nullptr;
			other.m_elementCount = 0ULL;
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

	size_t GetElementCount() const
	{
		return m_elementCount;
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
	size_t m_elementCount;
};
