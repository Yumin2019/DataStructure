#pragma once
#include <assert.h>

template <typename T>
class CQueueNode
{
	template <typename T>
	friend class CQueue;

private:
	CQueueNode()
	{
		m_pNext = nullptr;
	}

	~CQueueNode()
	{

	}

private:
	typedef CQueueNode<T>*		PNODE;

private:
	PNODE		m_pNext;
	T			m_Data;
};

template <typename T>
class CQueue
{
public:
	CQueue()
	{
		m_pIn = nullptr;
		m_pOut = nullptr;

		// In과 Out은 begin과 end처럼 상징적인 값이 아니라, 실제로 나올 데이터를 가리킨다.
		// In을 가지고 있는 이유는 quque의 특성상 FIFO 방식을 구현하기 위함이고,
		// Out을 가지고 있는 이유는 맨 나중에 추가한 노드를 기준으로 다음 노드의 자리를 받아오기 위함이다.

		m_iSize = 0;
	}

	~CQueue()
	{
		clear();
	}


private:
	typedef CQueueNode<T>*		PNODE;
	typedef CQueueNode<T>		NODE;	

public:

	bool empty() const
	{
		return m_iSize == 0;
	}

	int size() const
	{
		return m_iSize;
	}

	void clear()
	{
		// In부터 Out까지 모든 노드를 없앤다.

		PNODE pNode = m_pIn;

		while (pNode)
		{
			PNODE pNext = pNode->m_pNext;

			delete pNode;

			pNode = pNext;
		}

		m_iSize = 0;
		m_pIn = nullptr;
		m_pOut = nullptr;
	}

	void push(const T& data)
	{
		PNODE pNode = new NODE;

		pNode->m_Data = data;

		// 새로운 노드를 추가한다.

		if (empty())
		{
			m_pIn = pNode;
			m_pOut = pNode;
		}
		else
		{
			// 비어 있지 않다면, In이 가지고 있던 데이터의 다음으로 새로운 노드를 추가한다.
			m_pIn->m_pNext = pNode;

			// Out을 새로운 노드로 한다.
			m_pIn = pNode;
		}

		++m_iSize;
	}

	T& front() const
	{
		if (empty())
			assert(false);

		return m_pOut->m_Data;
	}

	T& back() const
	{
		if (empty())
			assert(false);

		return m_pIn->m_Data;
	}

	T pop() 
	{
		if (empty())
			assert(false);

		--m_iSize;

		T data = m_pOut->m_Data;

		// Out의 다음을 받아둔다.
		PNODE pNext = m_pOut->m_pNext;

		// 노드는 동적할당을 해둔 것이기 때문에 삭제한다.
		delete m_pOut;

		// Out을 out을 다음 노드로 잡는다.
		m_pOut = pNext;

		if (empty())
			m_pIn = nullptr;

		return data;
	}
private:
	PNODE		m_pIn;
	PNODE		m_pOut;
	int			m_iSize;
};

