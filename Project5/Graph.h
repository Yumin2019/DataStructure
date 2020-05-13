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
		// 나 -> pNode로 가는 간선을 추가한다.

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
	// 간선 리스트가 필요하다.
	// 간선에는 방문해야 할 노드만 들고 있으면 된다.
	// 가중치는 필요가 없으니. DFS BFS

	// List<T> 의 형태에 다시 템플릿을 넣으면, 이중 템플릿이 되어 어려워진다.
	// => 동적배열로 구현.

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

		// begin과 end를 연결한다.

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

		// 노드를 뒷쪽에 추가한다.

		// end의 이전노드를 받아온다.
		PNODE pPrev = m_pEnd->m_pPrev;

		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;

		++m_iSize;

	}
	void AddEdge(const T& src, const T& dest)
	{
		// src에서 dest로 가는 간선을 추가한다.

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

			// 여기서 시작 노드와 도착 노드가 같지 않다는 것을 전제로 한다. src != dest

		}

		if (!pSrc || !pDest)
		{
			// 입력된 데이터가 틀려서, 시작 노드와 도착 노드가 잡혀있지 않은 경우
			assert(false);
		}

		// src를 기준으로 dest를 추가하고 dest를 기준으로 src를 추가한다.

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
		// DFS의 경우에는, 모든 노드에 대하여 방문순서가 중요하지.
		// 어느 노드를 반드시 방문해야 하는 것이 아니다.
		// 경로를 구하고자 하는 것이 아님.
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

		// 모든 노드에 대해서 방문처리 false로 만든다.
		pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			pNode->m_bVisit = false;

			pNode = pNode->m_pNext;
		}

		// 출발지 노드를 추가한다.
		CStack<PNODE>		stack;

		stack.push(pSrc);

		while (!stack.empty())
		{
			pNode = stack.pop();

			pFunc(pNode->m_Data);

			pNode->m_bVisit = true;

			for (int i = 0; i < pNode->m_iEdgeSize; ++i)
			{
				// 방문한 노드로부터 연결된 다른 노드를 stack에 추가한다.

				// 이때 방문한 노드의 경우 넣지 않는다.
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

		// 모든 노드에 대해서 방문처리 false로 만든다.
		pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			pNode->m_bVisit = false;

			pNode = pNode->m_pNext;
		}

		// 출발지 노드를 추가한다.
		CQueue<PNODE>		queue;

		queue.push(pSrc);

		while (!queue.empty())
		{
			pNode = queue.pop();

			pFunc(pNode->m_Data);

			pNode->m_bVisit = true;

			for (int i = 0; i < pNode->m_iEdgeSize; ++i)
			{
				// 방문한 노드로부터 연결된 다른 노드를 stack에 추가한다.

				// 이때 방문한 노드의 경우 넣지 않는다.
				if (pNode->m_pEdgeArray[i]->m_bVisit)
					continue;

				else
					queue.push(pNode->m_pEdgeArray[i]);

			}
		}

	}

};


