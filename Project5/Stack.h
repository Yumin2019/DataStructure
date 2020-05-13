#pragma once

#include <iostream>
#include <assert.h>

using namespace std;

template <typename T, int SIZE = 10>
class CStack
{
public:
	CStack()
	{
		m_iCapacity = SIZE;

		m_pArray = new T[m_iCapacity];

		m_iSize = 0;
	}
	~CStack()
	{
		delete[] m_pArray;
	}

public:
	bool empty() const
	{
		return m_iSize == 0;
	}

	int size() const
	{
		return m_iSize;
	}

	int capacity() const
	{
		return m_iCapacity;
	}

	void push(const T& data)
	{
		if (m_iSize == m_iCapacity)
		{
			m_iCapacity *= 2;

			T* pArray = new T[m_iCapacity];

			memcpy(pArray, m_pArray, sizeof(T) * m_iSize);

			delete[] m_pArray;

			m_pArray = pArray;

		}

		m_pArray[m_iSize] = data;
		++m_iSize;
	}

	T pop() 
	{
		if (empty())
			assert(false);

		// 맨 나중에 추가된 요소를 뺀다.
		--m_iSize;
		T result = m_pArray[m_iSize];

		return result;
	}

	T& top() const
	{
		if (empty())
			assert(false);

		return m_pArray[m_iSize - 1];
	}

	void reserve(int iCapacity)
	{
		if (m_iCapacity >= iCapacity)
		{
			return;
		}

		m_iCapacity = iCapacity;

		T* pArray = new T[iCapacity];

		memcpy(pArray, m_pArray, sizeof(T) * m_iSize);

		delete[] m_pArray;

		m_pArray = pArray;
	}

	void clear()
	{
		m_iSize = 0;
	}



private:
	T*			m_pArray;
	int			m_iSize;
	int			m_iCapacity;
};

