#pragma once
#include <iostream>
#include <assert.h>
#include "Heap.h"
#include "Stack.h"
#include "LinkedList.h"

using namespace std;

template <typename T>
class CDijkstraNode
{
	template <typename T>
	friend class CDijkstra;


private:
	typedef CDijkstraNode<T>*		PNODE;


private:
	CDijkstraNode()
	{
		m_pNext = nullptr;
		m_pPrev = nullptr;
		m_pParent = nullptr;
		m_iWeight = INT_MAX;

		m_iCapacity = 2;
		m_pEdgeArray = new Edge[m_iCapacity];

		memset(m_pEdgeArray, 0, sizeof(Edge) * m_iCapacity);

		m_iEdgeSize = 0;

	}

	~CDijkstraNode()
	{
		delete[] m_pEdgeArray;
	}

	typedef struct _tagEdge
	{
		PNODE		pNode;
		int			iWeight;

	}Edge, *PEdge;


public:
	void AddEdge(PNODE pNode, int iWeight)
	{
		if (m_iEdgeSize == m_iCapacity)
		{
			m_iCapacity *= 2;

			_tagEdge* pArray = new Edge[m_iCapacity];

			memset(pArray, 0, sizeof(Edge) * m_iCapacity);

			memcpy(pArray, m_pEdgeArray, sizeof(_tagEdge) * m_iEdgeSize);

			delete[]  m_pEdgeArray;

			m_pEdgeArray = pArray;

		}

		m_pEdgeArray[m_iEdgeSize].pNode = pNode;
		m_pEdgeArray[m_iEdgeSize].iWeight = iWeight;

		++m_iEdgeSize;
	}


private:
	PNODE		m_pNext;
	PNODE		m_pPrev;
	PNODE		m_pParent;
	int			m_iWeight;



	// 다익스트라 또한, Edge정보가 필요하다.
	// 리스트에 템플릿을 넣지 않고 구현하기 위해서 구조체를 이용할 것이다.
	// DFS나 BFS의 경우에는 시작 노드를 기준으로 도착 노드만 있으면 상관없지만, 
	// 다익스트라의 경우에는 도착노드까지 가는데 걸리는 비용정보까지 포함해야 한다.
	
	_tagEdge*		m_pEdgeArray;
	int				m_iEdgeSize;
	int				m_iCapacity;
	T				m_Data;
};

template <typename T>
class CDijkstra
{

private:
	typedef CDijkstraNode<T>		NODE;
	typedef CDijkstraNode<T>*		PNODE;

private:
	typedef struct _tagFindNode
	{
		PNODE pParent;
		PNODE pNode;
		int iWeight;
	}FindNode, *PFindNode;

public:
	CDijkstra()
	{
		m_pBegin = new NODE;
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}

	~CDijkstra()
	{
		clear();
		delete m_pBegin;
		delete m_pEnd;
	}

public:
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

	void AddNode(const T& data)
	{
		PNODE pNode = new NODE;

		pNode->m_Data = data;

		// end의 이전 노드를 받아온다.

		PNODE pPrev = m_pEnd->m_pPrev;

		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;

		++m_iSize;
		
	}

	void AddEdge(const T& src, const T& dest, int iWeight) const
	{
		PNODE pNode = m_pBegin->m_pNext;
		PNODE pSrc = nullptr;
		PNODE pDest = nullptr;

		while (pNode != m_pEnd)
		{
			if (pNode->m_Data == src)
				pSrc = pNode;

			if (pNode->m_Data == dest)
				pDest = pNode;

			if (pSrc && pDest)
				break;

			pNode = pNode->m_pNext;
		}

		if (!pSrc || !pDest)
		{
			assert(false);
		}

		// 두 노드의 정보를 찾은 이후에는 서로 연결한다.

		pSrc->AddEdge(pDest, iWeight);
		pDest->AddEdge(pSrc, iWeight);
	}

	void Dijkstra(CLinkedList<T>& list, const T& src, const T& dest)
	{
		// 현재 노드에서 다익스트라 알고리즘을 시작하여 모든 노드까지의 비용을 구하면서 나아간다.

		PNODE pNode = m_pBegin->m_pNext;
		PNODE pSrc = nullptr;
		PNODE pDest = nullptr;

		while (pNode != m_pEnd)
		{
			if (pNode->m_Data == src)
			{
				pSrc = pNode;
			}
			else if (pNode->m_Data == dest)
			{
				pDest = pNode;
			}

			if (pSrc && pDest)
				break;

			pNode = pNode->m_pNext;
		}

		if (!pNode || !pDest)
			assert(false);

		// 모든 노드에 대해서 가중치를 무한대로 설정한다.

		pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			pNode->m_pParent = nullptr;
			pNode->m_iWeight = INT_MAX;

			pNode = pNode->m_pNext;
		}

		// 다익스트라 알고리즘을 시작.
		CHeap<FindNode> heap;

		heap.SetSortFunc<CDijkstra>(this, &CDijkstra::VertexSort);

		// heap에 함수를 설정해준다.
		// 가중치가 작은 것을 기준으로.

		pSrc->m_iWeight = 0;
		// 시작 노드의 가중치는 0이다.

		// 첫 노드와 그 다음 노드에 대한 정보를 넣고 시작한다.

		for (int i = 0; i < pSrc->m_iEdgeSize; ++i)
		{
			FindNode tFind;
			tFind.iWeight = pSrc->m_pEdgeArray[i].iWeight;
			tFind.pNode = pSrc->m_pEdgeArray[i].pNode;
			tFind.pParent = pSrc;

			heap.insert(tFind);
		}

		while (!heap.empty())
		{
			FindNode tFind = heap.pop();

				
				if (tFind.pNode->m_iWeight == INT_MAX)
				{
					// 처음 방문을 하는 경우.
					
					tFind.pNode->m_pParent = tFind.pParent;
					tFind.pNode->m_iWeight = tFind.pParent->m_iWeight + tFind.iWeight;

					// 도착지 노드를 기준으로 heap에 다시 추가.

					for (int i = 0; i < tFind.pNode->m_iEdgeSize; ++i)
					{
						FindNode tFindNode;
						tFindNode.pNode = tFind.pNode->m_pEdgeArray[i].pNode;
						tFindNode.pParent = tFind.pNode;
						tFindNode.iWeight = tFind.pNode->m_pEdgeArray[i].iWeight;

						heap.insert(tFindNode);
					}

				}

				// 이전 간선에 의한 비용보다, 이번 간선에 의한 비용이 싸다면 비용을 갱신한다.
				else if(tFind.pNode->m_iWeight > tFind.iWeight+ tFind.pParent->m_iWeight)
				{

					tFind.pNode->m_pParent = tFind.pParent;
					tFind.pNode->m_iWeight = tFind.pParent->m_iWeight + tFind.iWeight;

					// 도착지 노드를 기준으로 heap에 다시 추가.

					for (int i = 0; i < tFind.pNode->m_iEdgeSize; ++i)
					{
						FindNode tFindNode;
						tFindNode.pNode = tFind.pNode->m_pEdgeArray[i].pNode;
						tFindNode.pParent = tFind.pNode;
						tFindNode.iWeight = tFind.pNode->m_pEdgeArray[i].iWeight;

						heap.insert(tFindNode);
					}
				}
				
		}

		// 도착 노드로부터 시작 노드까지의 경로를 스택에 담는다.

		CStack<PNODE> stack;

		pNode = pDest;

		while (pNode)
		{
			stack.push(pNode);

			pNode = pNode->m_pParent;
		}

		while (!stack.empty())
		{
			pNode = stack.pop();
			list.push_back(pNode->m_Data);
		}

		// list에는 시작노드부터 도착노드까지의 정보가 들어있게 된다.
	}

private:

	bool VertexSort(const _tagFindNode& tSrc, const _tagFindNode& tDest)
	{
		return tDest.iWeight < tDest.iWeight;
	}

private:
	PNODE			m_pBegin;
	PNODE			m_pEnd;
	int				m_iSize;

};
	
