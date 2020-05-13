#pragma once
#include <assert.h>
#include <iostream>
#include "Stack.h"
#include "Queue.h"

using namespace std;

template <typename T>
class CGraphNode
{
	template <typename T>
	friend class CGraph;

private:
	typedef CGraphNode<T>*		PNODE;

private:
	CGraphNode()
	{
		m_bVisit = false;
		m_iEdgeSize = 0;
		m_iEdgeCapacity = 2;

		m_pEdgeArray = new PNODE[m_iEdgeCapacity];

		memset(m_pEdgeArray, 0, sizeof(PNODE) * m_iEdgeCapacity);

		m_pNext = nullptr;
		m_pPrev = nullptr;
	}
	~CGraphNode()
	{
		delete[] m_pEdgeArray;
	}

public:
	void AddEdge(PNODE pNode)
	{
		// �� -> pNode�� ���� ������ �߰��Ѵ�.

		if (m_iEdgeSize == m_iEdgeCapacity)
		{
			m_iEdgeCapacity *= 2;

			CGraphNode<T>** pEdgeArray = new PNODE[m_iEdgeCapacity];

			memcpy(pEdgeArray, m_pEdgeArray, sizeof(PNODE) * m_iEdgeSize);

			delete[] m_pEdgeArray;

			m_pEdgeArray = pEdgeArray;
		}

		m_pEdgeArray[m_iEdgeSize] = pNode;
		++m_iEdgeSize;
	}

private:
	bool	m_bVisit;
	int		m_iEdgeSize;
	// ���� ����Ʈ�� �ʿ��ϴ�.
	// �������� �湮�ؾ� �� ��常 ��� ������ �ȴ�.
	// ����ġ�� �ʿ䰡 ������. DFS BFS

	// List<T> �� ���¿� �ٽ� ���ø��� ������, ���� ���ø��� �Ǿ� ���������.
	// => �����迭�� ����.

	CGraphNode<T>**				m_pEdgeArray;
	int		m_iEdgeCapacity;


	PNODE		m_pNext;
	PNODE		m_pPrev;

	T			m_Data;

};
template <typename T>
class CGraph
{
public:
	CGraph()
	{
		m_pBegin = new NODE;
		m_pEnd = new NODE;

		// begin�� end�� �����Ѵ�.

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}
	~CGraph()
	{
		clear();
		delete m_pBegin;
		delete m_pEnd;
	}

private:
	typedef CGraphNode<T>*		PNODE;
	typedef CGraphNode<T>		NODE;


private:
	PNODE		m_pBegin;
	PNODE		m_pEnd;
	int			m_iSize;

public:
	void AddVertex(const T& data)
	{
		PNODE pNode = new NODE;

		pNode->m_Data = data;

		// ��带 ���ʿ� �߰��Ѵ�.

		// end�� ������带 �޾ƿ´�.
		PNODE pPrev = m_pEnd->m_pPrev;

		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;

		++m_iSize;

	}
	void AddEdge(const T& src, const T& dest)
	{
		// src���� dest�� ���� ������ �߰��Ѵ�.

		PNODE pNode = m_pBegin->m_pNext;

		PNODE pSrc = nullptr;
		PNODE pDest = nullptr;

		while (pNode != m_pEnd)
		{
			if (pNode->m_Data == src)
				pSrc = pNode;

			else if (pNode->m_Data == dest)
				pDest = pNode;

			if (pSrc && pDest)
				break;

			pNode = pNode->m_pNext;

			// ���⼭ ���� ���� ���� ��尡 ���� �ʴٴ� ���� ������ �Ѵ�. src != dest

		}

		if (!pSrc || !pDest)
		{
			// �Էµ� �����Ͱ� Ʋ����, ���� ���� ���� ��尡 �������� ���� ���
			assert(false);
		}

		// src�� �������� dest�� �߰��ϰ� dest�� �������� src�� �߰��Ѵ�.

		pSrc->AddEdge(pDest);
		pDest->AddEdge(pSrc);

	}
	void clear()
	{
		PNODE pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			PNODE pNext = pNode->m_pNext;

			delete pNode;

			pNode = pNext;
		}

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}

	void DFS(const T& data, void(*pFunc)(const T&))
	{
		// DFS�� ��쿡��, ��� ��忡 ���Ͽ� �湮������ �߿�����.
		// ��� ��带 �ݵ�� �湮�ؾ� �ϴ� ���� �ƴϴ�.
		// ��θ� ���ϰ��� �ϴ� ���� �ƴ�.
		PNODE pNode = m_pBegin->m_pNext;

		PNODE pSrc = nullptr;

		while (pNode != m_pEnd)
		{
			if (pNode->m_Data == data)
			{
				pSrc = pNode;
				break;
			}
			pNode = pNode->m_pNext;

		}

		if (!pSrc)
		{
			assert(false);
		}

		// ��� ��忡 ���ؼ� �湮ó�� false�� �����.
		pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			pNode->m_bVisit = false;

			pNode = pNode->m_pNext;
		}

		// ����� ��带 �߰��Ѵ�.
		CStack<PNODE>		stack;

		stack.push(pSrc);

		while (!stack.empty())
		{
			pNode = stack.pop();

			pFunc(pNode->m_Data);

			pNode->m_bVisit = true;

			for (int i = 0; i < pNode->m_iEdgeSize; ++i)
			{
				// �湮�� ���κ��� ����� �ٸ� ��带 stack�� �߰��Ѵ�.

				// �̶� �湮�� ����� ��� ���� �ʴ´�.
				if (pNode->m_pEdgeArray[i]->m_bVisit)
					continue;

				else
					stack.push(pNode->m_pEdgeArray[i]);

			}
		}
		
		
	}


	void BFS(const T& data, void(*pFunc)(const T&))
	{
		PNODE pNode = m_pBegin->m_pNext;

		PNODE pSrc = nullptr;

		while (pNode != m_pEnd)
		{
			if (pNode->m_Data == data)
			{
				pSrc = pNode;
				break;
			}
			pNode = pNode->m_pNext;

		}

		if (!pSrc)
		{
			assert(false);
		}

		// ��� ��忡 ���ؼ� �湮ó�� false�� �����.
		pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			pNode->m_bVisit = false;

			pNode = pNode->m_pNext;
		}

		// ����� ��带 �߰��Ѵ�.
		CQueue<PNODE>		queue;

		queue.push(pSrc);

		while (!queue.empty())
		{
			pNode = queue.pop();

			pFunc(pNode->m_Data);

			pNode->m_bVisit = true;

			for (int i = 0; i < pNode->m_iEdgeSize; ++i)
			{
				// �湮�� ���κ��� ����� �ٸ� ��带 stack�� �߰��Ѵ�.

				// �̶� �湮�� ����� ��� ���� �ʴ´�.
				if (pNode->m_pEdgeArray[i]->m_bVisit)
					continue;

				else
					queue.push(pNode->m_pEdgeArray[i]);

			}
		}

	}

};


