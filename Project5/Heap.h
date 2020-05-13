#pragma once
#include <assert.h>
#include <functional>
#include <iostream>

using namespace std;

template <typename T, int SIZE = 50>
class CHeap
{
public:
	CHeap()
	{
		m_iCapacity = SIZE;

		m_pArray = new T[m_iCapacity];

		m_iSize = 0;

		//// �⺻������ �ּ������� ����
		//m_pComFunc = bind(&CHeap::Sort, this, placeholders::_1, placeholders::_2);
	}

	~CHeap()
	{
		delete[] m_pArray;
	}

public:
	void SetSortFunc(bool(*pFunc)(const T&, const T&))
	{
		m_pComFunc = bind(pFunc, placeholders::_1, placeholders::_2);
	}

	template <typename Class>
	void SetSortFunc(Class* pObj, bool(Class::*pFunc)(const T&, const T&))
	{
		m_pComFunc = bind(pFunc, pObj, placeholders::_1, placeholders::_2);
	}

	void insert(const T& data)
	{
		// �����͸� �ֱ� ���� �ϴ� �迭�� �ڸ��� �ִ��� Ȯ���Ѵ�.

		if (m_iSize == m_iCapacity)
		{
			m_iCapacity *= 2;

			T* pArray = new T[m_iCapacity];

			for (int i = 0; i < m_iSize; ++i)
			{
				pArray[i] = m_pArray[i];
			}

			delete[] m_pArray;

			m_pArray = pArray;
		}

		m_pArray[m_iSize] = data;

		++m_iSize;

		// �ڸ��� ã���ش�.
		insert(m_iSize / 2 - 1, m_iSize - 1);
	}

	void clear()
	{
		m_iSize = 0;
	}

	bool empty() const
	{
		return m_iSize == 0;
	}

	int size() const
	{
		return m_iSize;
	}

	T pop() 
	{
		if (empty())
			assert(false);

		T data = m_pArray[0];
		// ���� �ֻ�� ����� �����͸� ��������. �� �� �ִ� ��带 �Ǿ����� ����´�.


		--m_iSize;

		m_pArray[0] = m_pArray[m_iSize];

		// �ö�� ��带 �������� �ٽ� �ڸ��� �⵵�� �Ѵ�.
		pop(0);

		return data;
	}

private:

	void pop(int iIndex)
	{
		// �ö�� ��带 �������� �ٽ� �ڸ��� ã�ư��� �����̴�.
		// �� ������ �ֻ������ �ö�� ��忡�� �ڽ��� ������ ���� ����.

		if (iIndex >= m_iSize)
			return;

		// ���� �ڽ��� �޾ƿ´�.
		int iLeft = iIndex * 2 + 1;
		int iChild = iLeft;

		// ���� �ڽ��� ���� ��츦 ó���Ѵ�.
		if (iLeft >= m_iSize)
		{
			return;
			// ���� �ڽ��� ���ٴ� ���� ������ �ڽĵ� ���ٴ� ���� �ǹ��Ѵ�.
		}

		// ���� �ڽ��� �ִ� ��쿡�� ������ �ڽİ� ũ�⸦ ���Ѵ�.
		int iRight = iIndex * 2 + 2;

		if (iRight < m_iSize)
		{
			// ������ �ڽ��� �ִ� ��쿡�� ���� �ڽİ� ���Ѵ�.
			if (m_pComFunc(m_pArray[iRight], m_pArray[iLeft]))
			{
				// �ִ����� �������� �ϱ⿡ �� ū ���� ������ �ڽ��� ��ƾ� �Ѵ�..
				// ���� �ڽ��� ��� �ִ� ��Ȳ���� ������ �ڽ��� �� ũ�ٸ�,
				// ������ �ڽ��� ��´�.

				iChild = iRight;
			}
		}

		// iChild�� �ڽĳ���߿��� ū ���� ������ �ְ� �ȴ�.

		// �̷��� �޾Ƶ� �ڽ��� ����Ű�� ���� ���� �ε����� ���� �ִ� ���� ���Ͽ� 
		// �ڽ��� ���� �� ũ�ٸ�, �����Ѵ�.

		if (m_pComFunc(m_pArray[iChild], m_pArray[iIndex]))
		{
			// ���� �ε����� �ڽ��� �ε����� �ִ� ���� �����Ѵ�.

			T temp = m_pArray[iChild];
			m_pArray[iChild] = m_pArray[iIndex];
			m_pArray[iIndex] = temp;

			// �ڽ��� ��带 �������� �ٽ� �� �ڽ��� ���� �ٲ���ϴ��� Ȯ���Ѵ�.
			pop(iChild);
		}
	

	}
	void insert(int iParent, int iChild)
	{
		if (iParent < 0)
			return;
		
		if (m_pComFunc(m_pArray[iChild], m_pArray[iParent]))
		{
			// �ڽ��� �� ū ��쿡 �θ�� �ڽ��� �����Ѵ�.

			T temp = m_pArray[iChild];
			m_pArray[iChild] = m_pArray[iParent];
			m_pArray[iParent] = temp;

			// ���⼭ �ڸ��� �ٲ���ٴ� ���� �ٲ� ���(���⼭�� ���� �θ�)�� �������� 
			// �ٽ� ���θ� ���� �񱳸� �ؼ� �ٲ� �ʿ䰡 �ִٴ� ���� �ǹ��Ѵ�.

			insert((iParent + 1) / 2 - 1, iParent);
		}
	}
//
//
//private: // �⺻ ���� �Լ�
//	bool Sort(const T& a1, const T& a2)
//	{
//		return a1 < a2;
//	}

private:
	T*		m_pArray;
	int		m_iSize;
	int		m_iCapacity;
	function<bool(const T&, const T&)> m_pComFunc;
};

