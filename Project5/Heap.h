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

		//// 기본적으로 최소힙으로 정렬
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
		// 데이터를 넣기 전에 일단 배열에 자리가 있는지 확인한다.

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

		// 자리를 찾아준다.
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
		// 가장 최상단 노드의 데이터를 가져오고. 맨 뒤 있는 노드를 맨앞으로 끌고온다.


		--m_iSize;

		m_pArray[0] = m_pArray[m_iSize];

		// 올라온 노드를 기준으로 다시 자리를 잡도록 한다.
		pop(0);

		return data;
	}

private:

	void pop(int iIndex)
	{
		// 올라온 노드를 기준으로 다시 자리를 찾아가는 과정이다.
		// 이 과정은 최상단으로 올라온 노드에서 자식의 노드까지 가는 과정.

		if (iIndex >= m_iSize)
			return;

		// 왼쪽 자식을 받아온다.
		int iLeft = iIndex * 2 + 1;
		int iChild = iLeft;

		// 왼쪽 자식이 없는 경우를 처리한다.
		if (iLeft >= m_iSize)
		{
			return;
			// 왼쪽 자식이 없다는 것은 오른쪽 자식도 없다는 것을 의미한다.
		}

		// 왼쪽 자식이 있는 경우에는 오른쪽 자식과 크기를 비교한다.
		int iRight = iIndex * 2 + 2;

		if (iRight < m_iSize)
		{
			// 오른쪽 자식이 있는 경우에만 왼쪽 자식과 비교한다.
			if (m_pComFunc(m_pArray[iRight], m_pArray[iLeft]))
			{
				// 최대힙을 기준으로 하기에 더 큰 값을 가지는 자식을 잡아야 한다..
				// 왼쪽 자식을 잡고 있는 상황에서 오른쪽 자식이 더 크다면,
				// 오른쪽 자식을 잡는다.

				iChild = iRight;
			}
		}

		// iChild는 자식노드중에서 큰 값을 가지고 있게 된다.

		// 이렇게 받아둔 자식이 가리키는 값과 현재 인덱스가 갖고 있는 값을 비교하여 
		// 자식의 값이 더 크다면, 스왑한다.

		if (m_pComFunc(m_pArray[iChild], m_pArray[iIndex]))
		{
			// 현재 인덱스와 자식의 인덱스에 있는 값을 스왑한다.

			T temp = m_pArray[iChild];
			m_pArray[iChild] = m_pArray[iIndex];
			m_pArray[iIndex] = temp;

			// 자식의 노드를 기준으로 다시 그 자식의 노드와 바꿔야하는지 확인한다.
			pop(iChild);
		}
	

	}
	void insert(int iParent, int iChild)
	{
		if (iParent < 0)
			return;
		
		if (m_pComFunc(m_pArray[iChild], m_pArray[iParent]))
		{
			// 자식이 더 큰 경우에 부모와 자식을 스왑한다.

			T temp = m_pArray[iChild];
			m_pArray[iChild] = m_pArray[iParent];
			m_pArray[iParent] = temp;

			// 여기서 자리가 바뀌었다는 것은 바뀐 노드(여기서는 이제 부모)를 기준으로 
			// 다시 조부모 노드와 비교를 해서 바꿀 필요가 있다는 것을 의미한다.

			insert((iParent + 1) / 2 - 1, iParent);
		}
	}
//
//
//private: // 기본 정렬 함수
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

