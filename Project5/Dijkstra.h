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



	// ���ͽ�Ʈ�� ����, Edge������ �ʿ��ϴ�.
	// ����Ʈ�� ���ø��� ���� �ʰ� �����ϱ� ���ؼ� ����ü�� �̿��� ���̴�.
	// DFS�� BFS�� ��쿡�� ���� ��带 �������� ���� ��常 ������ ���������, 
	// ���ͽ�Ʈ���� ��쿡�� ���������� ���µ� �ɸ��� ����������� �����ؾ� �Ѵ�.
	
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

		// end�� ���� ��带 �޾ƿ´�.

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

		// �� ����� ������ ã�� ���Ŀ��� ���� �����Ѵ�.

		pSrc->AddEdge(pDest, iWeight);
		pDest->AddEdge(pSrc, iWeight);
	}

	void Dijkstra(CLinkedList<T>& list, const T& src, const T& dest)
	{
		// ���� ��忡�� ���ͽ�Ʈ�� �˰����� �����Ͽ� ��� �������� ����� ���ϸ鼭 ���ư���.

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

		// ��� ��忡 ���ؼ� ����ġ�� ���Ѵ�� �����Ѵ�.

		pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			pNode->m_pParent = nullptr;
			pNode->m_iWeight = INT_MAX;

			pNode = pNode->m_pNext;
		}

		// ���ͽ�Ʈ�� �˰����� ����.
		CHeap<FindNode> heap;

		heap.SetSortFunc<CDijkstra>(this, &CDijkstra::VertexSort);

		// heap�� �Լ��� �������ش�.
		// ����ġ�� ���� ���� ��������.

		pSrc->m_iWeight = 0;
		// ���� ����� ����ġ�� 0�̴�.

		// ù ���� �� ���� ��忡 ���� ������ �ְ� �����Ѵ�.

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
					// ó�� �湮�� �ϴ� ���.
					
					tFind.pNode->m_pParent = tFind.pParent;
					tFind.pNode->m_iWeight = tFind.pParent->m_iWeight + tFind.iWeight;

					// ������ ��带 �������� heap�� �ٽ� �߰�.

					for (int i = 0; i < tFind.pNode->m_iEdgeSize; ++i)
					{
						FindNode tFindNode;
						tFindNode.pNode = tFind.pNode->m_pEdgeArray[i].pNode;
						tFindNode.pParent = tFind.pNode;
						tFindNode.iWeight = tFind.pNode->m_pEdgeArray[i].iWeight;

						heap.insert(tFindNode);
					}

				}

				// ���� ������ ���� ��뺸��, �̹� ������ ���� ����� �δٸ� ����� �����Ѵ�.
				else if(tFind.pNode->m_iWeight > tFind.iWeight+ tFind.pParent->m_iWeight)
				{

					tFind.pNode->m_pParent = tFind.pParent;
					tFind.pNode->m_iWeight = tFind.pParent->m_iWeight + tFind.iWeight;

					// ������ ��带 �������� heap�� �ٽ� �߰�.

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

		// ���� ���κ��� ���� �������� ��θ� ���ÿ� ��´�.

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

		// list���� ���۳����� ������������ ������ ����ְ� �ȴ�.
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
	
