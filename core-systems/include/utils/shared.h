#pragma once

template<typename T>
class Shared
{
public:
	Shared(T* reference = nullptr) :
		m_reference(reference),
		m_referenceCount(nullptr)
	{
		if (m_reference != nullptr)
			m_referenceCount = new size_t(1ULL);
	}

	Shared(const Shared& other) :
		m_reference(other.m_reference),
		m_referenceCount(other.m_referenceCount)
	{
		if (m_referenceCount != nullptr)
			(*m_referenceCount)++;
	}

	Shared(Shared&& other) noexcept :
		m_reference(other.m_reference),
		m_referenceCount(other.m_referenceCount)
	{
		other.m_reference = nullptr;
		other.m_referenceCount = nullptr;
	}

	Shared& operator=(const Shared& other)
	{
		if (this != &other)
		{
			DecrementAndRelease();

			m_reference = other.m_reference;
			m_referenceCount = other.m_referenceCount;

			if (m_referenceCount != nullptr)
				(*m_referenceCount)++;
		}
		return *this;
	}

	Shared& operator=(Shared&& other) noexcept
	{
		if (this != &other)
		{
			DecrementAndRelease();

			m_reference = other.m_reference;
			m_referenceCount = other.m_referenceCount;

			other.m_reference = nullptr;
			other.m_referenceCount = nullptr;
		}
		return *this;
	}

	~Shared()
	{
		DecrementAndRelease();
	}

	T& operator*()
	{
		return *m_reference;
	}

	const T& operator*() const
	{
		return *m_reference;
	}

	T* operator->() noexcept
	{
		return m_reference;
	}

	const T* operator->() const noexcept
	{
		return m_reference;
	}

	bool operator==(T* pointer) const
	{
		return m_reference == pointer;
	}

	bool operator==(const Shared<T>& other) const
	{
		return m_reference == other.m_reference;
	}

	bool operator!=(T* pointer) const
	{
		return m_reference != pointer;
	}

	bool operator!=(const Shared<T>& other) const
	{
		return m_reference != other.m_reference;
	}

	T* Get()
	{
		return m_reference;
	}

	const T* Get() const
	{
		return m_reference;
	}

	void Reset()
	{
		DecrementAndRelease();
	}
private:
	T* m_reference;
	size_t* m_referenceCount;

	void DecrementAndRelease()
	{
		if (m_referenceCount != nullptr)
		{
			(*m_referenceCount)--;
			if (*m_referenceCount == 0ULL)
			{
				delete m_reference;
				delete m_referenceCount;
			}
			m_reference = nullptr;
			m_referenceCount = nullptr;
		}
	}
};
