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
			// �Ҵ緮�� ����� ���ٸ�, ���ο� �����͸� �߰��ϱ� ���ؼ� �߰��� �Ҵ��� �ʿ��ϴ�.

			m_iCapacity *= 2;

			T* pArray = new T[m_iCapacity];

			// ���� �����͸� ���ο� �迭�� �ű��.
			memcpy(pArray, m_pArray, sizeof(T) * m_iSize);

			// ���� �迭�� �����Ѵ�.
			delete[] m_pArray;

			// ���ο� �迭�� ��´�.
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
		// �̸� �Ҵ��� �صδ� ����̴�.
		// size ��ü�� �ٲٴ� ���� �ƴϴ�.
		// ���� �Ҵ緮�� �ø��� ó��.

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
		// reserve�� ���� �Է¹��� �Ҵ緮�� ���� ũ�⸦ �÷��ִ� ������ �Ѵ�.
		// �ٸ� �������� reserve�� ��� size ��ü�� �ٲ��� �ʾƼ�, ���� �Ҵ�� ������ ������ �� ����.
		// ex reserve(10) -> size�� 5���, [9]�� ������ �Ұ�. (size�� ����)
		// ������, resize�� ��쿡�� �ش� ��ҿ� ������ �����ϵ��� size ���� ����ش�.

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


		// iter�� ����Ű�� �ε����� ���Ϳ��� �����ϰ�, �� ���Ŀ� �ִ� �����͸� ������ �ű��

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


		// iter�� ����Ű�� �ε����� ���Ϳ��� �����ϰ�, �� ���Ŀ� �ִ� �����͸� ������ �ű��

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

