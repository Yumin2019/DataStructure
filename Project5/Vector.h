#pragma once
#include <iostream>
#include <assert.h>

using namespace std;

template <typename T>
class CVectorIterator
{
	template <typename T>
	friend class CVector;

public:
	CVectorIterator()
	{
		m_iIndex = 0;
		m_pArray = nullptr;
	}

	~CVectorIterator()
	{

	}

private:
	int			m_iIndex;
	T*			m_pArray;

public:
	bool operator == (const CVectorIterator<T>& iter)
	{
		return m_iIndex == iter.m_iIndex;
	}

	bool operator != (const CVectorIterator<T>& iter)
	{
		return m_iIndex != iter.m_iIndex;
	}

	void operator++ ()
	{
		++m_iIndex;
	}

	void operator++ (int)
	{
		++m_iIndex;
	}

	void operator-- ()
	{
		--m_iIndex;
	}

	void operator-- (int)
	{
		--m_iIndex;
	}

	T& operator * ()
	{
		return m_pArray[m_iIndex];
	}

};


template <typename T>
class CVectorReverseIterator
{
	template <typename T>
	friend class CVector;

public:
	CVectorReverseIterator()
	{
		m_iIndex = 0;
		m_pArray = nullptr;
	}

	~CVectorReverseIterator()
	{

	}

private:
	int			m_iIndex;
	T*			m_pArray;

public:
	bool operator == (const CVectorReverseIterator<T>& iter)
	{
		return m_iIndex == iter.m_iIndex;
	}

	bool operator != (const CVectorReverseIterator<T>& iter)
	{
		return m_iIndex != iter.m_iIndex;
	}

	void operator++ ()
	{
		--m_iIndex;
	}

	void operator++ (int)
	{
		--m_iIndex;
	}

	void operator-- ()
	{
		++m_iIndex;
	}

	void operator-- (int)
	{
		++m_iIndex;
	}

	T& operator * ()
	{
		return m_pArray[m_iIndex];
	}

};

template <typename T>
class CVector
{
public:
	CVector()
	{
		m_iCapacity = 2;

		m_pArray = new	T[m_iCapacity];

		m_iSize = 0;

	}

	~CVector()
	{
		delete[] m_pArray;
	}

public:
	typedef CVectorIterator<T>			iterator;
	typedef CVectorReverseIterator<T>	reverse_iterator;

private:
	T*			m_pArray;
	int			m_iSize;
	int			m_iCapacity;


public:
	bool empty() const
	{
		return m_iSize == 0;
	}

	int capacity() const
	{
		return m_iCapacity;
	}

	int size() const
	{
		return m_iSize;
	}

	void push_back(const T& data)
	{
		if (m_iSize == m_iCapacity)
		{
			// 할당량과 사이즈가 같다면, 새로운 데이터를 추가하기 위해서 추가로 할당이 필요하다.

			m_iCapacity *= 2;

			T* pArray = new T[m_iCapacity];

			// 기존 데이터를 새로운 배열에 옮긴다.
			memcpy(pArray, m_pArray, sizeof(T) * m_iSize);

			// 기존 배열을 삭제한다.
			delete[] m_pArray;

			// 새로운 배열을 잡는다.
			m_pArray = pArray;
		}

		m_pArray[m_iSize] = data;
		++m_iSize;
	}
	
	void pop_back()
	{
		if (empty())
			assert(false);

		--m_iSize;
	}

	void clear()
	{
		m_iSize = 0;
	}


	T& operator[](int iIndex) const
	{
		if (iIndex >= m_iSize)
			assert(false);

		return m_pArray[iIndex];
	}

	T& front() const
	{
		if (empty())
			assert(false);

		return m_pArray[0];
	}

	T& back() const
	{
		if (empty())
			assert(false);

		return m_pArray[m_iSize - 1];
	}

	void reserve(int iCapacity)
	{
		// 미리 할당을 해두는 기능이다.
		// size 자체를 바꾸는 것은 아니다.
		// 단지 할당량만 늘리는 처리.

		if (m_iCapacity >= iCapacity)
		{
			return;
		}

		T* pArray = new T[iCapacity];

		memcpy(pArray, m_pArray, sizeof(T) * m_iSize);

		m_iCapacity = iCapacity;

		delete[] m_pArray;

		m_pArray = pArray;
	}

	void resize(int iCapacity)
	{
		// reserve와 같이 입력받은 할당량에 따라서 크기를 늘려주는 역할을 한다.
		// 다만 차이점은 reserve의 경우 size 자체는 바꾸지 않아서, 새로 할당된 공간에 접근할 수 없다.
		// ex reserve(10) -> size가 5라면, [9]에 접근이 불가. (size가 작음)
		// 하지만, resize의 경우에는 해당 요소에 접근이 가능하도록 size 또한 잡아준다.

		if (m_iCapacity >= iCapacity)
		{
			return;
		}

		T* pArray = new T[iCapacity];

		memcpy(pArray, m_pArray, sizeof(T) * m_iSize);

		m_iCapacity = iCapacity;
		m_iSize = iCapacity;

		delete[] m_pArray;

		m_pArray = pArray;

	}

	void sort() const
	{
		for (int i = 0; i < m_iSize - 1; ++i)
		{
			int iIndex = i;

			for (int j = i + 1; j < m_iSize; ++j)
			{
				if (m_pArray[iIndex] > m_pArray[j])
				{
					iIndex = j;
				}
			}

			if (i != iIndex)
			{
				T temp = m_pArray[i];
				m_pArray[i] = m_pArray[iIndex];
				m_pArray[iIndex] = temp;
			}
		}
	}

	void sort(bool(*pFunc)(const T&, const T&))
	{
		for (int i = 0; i < m_iSize - 1; ++i)
		{
			int iIndex = i;

			for (int j = i + 1; j < m_iSize; ++j)
			{
				if (pFunc(m_pArray[iIndex], m_pArray[j]))
				{
					iIndex = j;
				}
			}

			if (i != iIndex)
			{
				T temp = m_pArray[i];
				m_pArray[i] = m_pArray[iIndex];
				m_pArray[iIndex] = temp;
			}
		}
	}

	iterator begin() const
	{
		iterator iter;
		iter.m_pArray = m_pArray;
		iter.m_iIndex = 0;
		return iter;
	}

	iterator end() const
	{
		iterator iter;
		iter.m_pArray = m_pArray;
		iter.m_iIndex = m_iSize;
		return iter;
	}


	reverse_iterator rbegin() const
	{
		reverse_iterator iter;
		iter.m_pArray = m_pArray;
		iter.m_iIndex = m_iSize - 1;
		return iter;
	}

	reverse_iterator rend() const
	{
		reverse_iterator iter;
		iter.m_pArray = m_pArray;
		iter.m_iIndex = -1;
		return iter;
	}

	iterator erase(const iterator& iter)
	{
		if (iter.m_iIndex < 0 || iter.m_iIndex >= m_iSize)
		{
			assert(false);
		}


		// iter가 가리키는 인덱스를 벡터에서 제외하고, 그 이후에 있는 데이터를 앞으로 옮긴다

		for (int i = iter.m_iIndex; i < m_iSize - 1; ++i)
		{
			m_pArray[i] = m_pArray[i + 1];
		}

		--m_iSize;


		iterator result;
		result.m_iIndex = iter.m_iIndex;
		result.m_pArray = m_pArray;

		return result;
	}

	reverse_iterator erase(const reverse_iterator& iter)
	{
		if (iter.m_iIndex < 0 || iter.m_iIndex >= m_iSize)
		{
			assert(false);
		}


		// iter가 가리키는 인덱스를 벡터에서 제외하고, 그 이후에 있는 데이터를 앞으로 옮긴다

		for (int i = iter.m_iIndex; i < m_iSize - 1; ++i)
		{
			m_pArray[i] = m_pArray[i + 1];
		}

		--m_iSize;


		reverse_iterator result;
		result.m_iIndex = iter.m_iIndex - 1;
		result.m_pArray = m_pArray;
		
		return result;
	}

};

