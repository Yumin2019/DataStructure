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

		// In�� Out�� begin�� endó�� ��¡���� ���� �ƴ϶�, ������ ���� �����͸� ����Ų��.
		// In�� ������ �ִ� ������ quque�� Ư���� FIFO ����� �����ϱ� �����̰�,
		// Out�� ������ �ִ� ������ �� ���߿� �߰��� ��带 �������� ���� ����� �ڸ��� �޾ƿ��� �����̴�.

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
		// In���� Out���� ��� ��带 ���ش�.

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

		// ���ο� ��带 �߰��Ѵ�.

		if (empty())
		{
			m_pIn = pNode;
			m_pOut = pNode;
		}
		else
		{
			// ��� ���� �ʴٸ�, In�� ������ �ִ� �������� �������� ���ο� ��带 �߰��Ѵ�.
			m_pIn->m_pNext = pNode;

			// Out�� ���ο� ���� �Ѵ�.
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

		// Out�� ������ �޾Ƶд�.
		PNODE pNext = m_pOut->m_pNext;

		// ���� �����Ҵ��� �ص� ���̱� ������ �����Ѵ�.
		delete m_pOut;

		// Out�� out�� ���� ���� ��´�.
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

