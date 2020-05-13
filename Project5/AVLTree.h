#pragma once

#include <assert.h>

template <typename Key, typename Value>
class CAVLTreeNode
{
	template <typename Key, typename Value>
	friend class CAVLTree;

	template <typename Key, typename Value>
	friend class CAVLTreeIterator;

	template <typename Key, typename Value>
	friend class CAVLTreeReverseIterator;

private:
	CAVLTreeNode()
	{
		m_pNext = nullptr;
		m_pPrev = nullptr;
		m_pLeft = nullptr;
		m_pRight = nullptr;
		m_pParent = nullptr;

	}

	~CAVLTreeNode()
	{

	}

private:
	typedef CAVLTreeNode<Key, Value>*		PNODE;

private:
	PNODE		m_pNext;
	PNODE		m_pPrev;
	PNODE		m_pLeft;
	PNODE		m_pRight;
	PNODE		m_pParent;

public:
	Key			first;
	Value		second;

public:
	void Output()
	{


		cout << "Key : " << first;

		if (m_pParent)
			cout << "\t부모 Key: " << m_pParent->first << endl;
		else
			cout << endl;

		if (m_pLeft)
		{
			cout << "왼쪽 자식 Key : " << m_pLeft->first << endl;
		}
		else
			cout << "왼쪽 자식 없음" << endl;

		if (m_pRight)
		{
			cout << "오른쪽 자식 Key : " << m_pRight->first << endl;
		}
		else
			cout << "오른쪽 자식 없음" << endl;
	}
};


template <typename Key, typename Value>
class CAVLTreeReverseIterator
{

	template <typename Key, typename Value>
	friend class CAVLTree;


private:
	typedef CAVLTreeNode<Key, Value>*		PNODE;

public:
	CAVLTreeReverseIterator()
	{
		m_pNode = nullptr;
	}

	~CAVLTreeReverseIterator()
	{

	}

public:
	bool operator == (const CAVLTreeReverseIterator<Key, Value>& iter)
	{
		return iter.m_pNode == m_pNode;
	}

	bool operator != (const CAVLTreeReverseIterator<Key, Value>& iter)
	{
		return iter.m_pNode != m_pNode;
	}

	void operator ++ ()
	{
		m_pNode = m_pNode->m_pPrev;
	}

	void operator ++ (int)
	{
		m_pNode = m_pNode->m_pPrev;
	}

	void operator -- ()
	{
		m_pNode = m_pNode->m_pNext;
	}

	void operator -- (int)
	{
		m_pNode = m_pNode->m_pNext;
	}

	PNODE operator -> ()
	{
		return m_pNode;
	}
	// iter->first iter->second



private:
	PNODE	m_pNode;
};

template <typename Key, typename Value>
class CAVLTreeIterator
{

	template <typename Key, typename Value>
	friend class CAVLTree;


private:
	typedef CAVLTreeNode<Key, Value>*		PNODE;

public:
	CAVLTreeIterator()
	{
		m_pNode = nullptr;
	}

	~CAVLTreeIterator()
	{

	}

public:
	bool operator == (const CAVLTreeIterator<Key, Value>& iter)
	{
		return iter.m_pNode == m_pNode;
	}

	bool operator != (const CAVLTreeIterator<Key, Value>& iter)
	{
		return iter.m_pNode != m_pNode;
	}

	void operator ++ ()
	{
		m_pNode = m_pNode->m_pNext;
	}

	void operator ++ (int)
	{
		m_pNode = m_pNode->m_pNext;
	}

	void operator -- ()
	{
		m_pNode = m_pNode->m_pPrev;
	}

	void operator -- (int)
	{
		m_pNode = m_pNode->m_pPrev;
	}

	PNODE operator -> ()
	{
		return m_pNode;
	}
	// iter->first iter->second



private:
	PNODE	m_pNode;
};

template <typename Key, typename Value>
class CAVLTree
{
private:
	typedef CAVLTreeNode<Key, Value>*		PNODE;
	typedef CAVLTreeNode<Key, Value>		NODE;

public:
	typedef CAVLTreeIterator<Key, Value>		 iterator;
	typedef CAVLTreeReverseIterator<Key, Value> reverse_iterator;

public:
	CAVLTree()
	{
		m_pBegin = new NODE;
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;

		m_pRoot = nullptr;

	}

	~CAVLTree()
	{
		clear();
		delete m_pBegin;
		delete m_pEnd;
	}

public:

	bool empty() const
	{
		return m_iSize == 0;
	}

	int size() const
	{
		return m_iSize;
	}

	iterator find(const Key& key) const
	{
		// 노드를 찾아오는 기능이다.

		if (empty())
			assert(false);

		return find(m_pRoot, key);
	}

	void clear()
	{
		// begin과 end사이의 모든 노드를 삭제한다.
		PNODE pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			PNODE pNext = pNode->m_pNext;

			delete pNode;

			pNode = pNext;
		}

		m_iSize = 0;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_pRoot = nullptr;
	}

	void insert(const Key& key, const Value& value)
	{
		if (!m_pRoot)
		{
			// 루트노드에 노드를 추가한다.

			m_pRoot = new NODE;

			m_pRoot->m_pPrev = m_pBegin;
			m_pBegin->m_pNext = m_pRoot;

			m_pRoot->m_pNext = m_pEnd;
			m_pEnd->m_pPrev = m_pRoot;

			m_pRoot->first = key;
			m_pRoot->second = value;
		}

		else
		{
			insert(m_pRoot, key, value);
		}

		++m_iSize;
	}

	iterator begin() const
	{
		iterator iter;
		iter.m_pNode = m_pBegin->m_pNext;

		return iter;
	}

	iterator end() const
	{
		iterator iter;
		iter.m_pNode = m_pEnd;

		return iter;
	}

	reverse_iterator rbegin() const
	{
		reverse_iterator iter;
		iter.m_pNode = m_pEnd->m_pPrev;

		return iter;
	}

	reverse_iterator rend() const
	{
		reverse_iterator iter;
		iter.m_pNode = m_pBegin;

		return iter;
	}

	// erase
	iterator erase(iterator iter)
	{

		// 예외처리.
		if (iter.m_pNode == nullptr || iter.m_pNode == m_pBegin || iter.m_pNode == m_pEnd)
			assert(false);

		else if (empty())
			assert(false);

		iterator result;


		// iter가 가리키는 노드를 삭제한다.
		// 현재 노드의 자식이 없는 경우.
		// 자식이 하나가 있는 경우
		// 자식이 둘 딸린 경우.

		if (!iter.m_pNode->m_pLeft && !iter.m_pNode->m_pRight)
		{
			// 자식이 없다.
			// 이 노드를 없애고, 부모 자식의 관계를 없던 것으로 하면 된다.
			// 리스트의 경우 삭제할 노드의 이전과 다음을 잇는다.

			// 부모 노드를 가져온다.

			PNODE pParent = iter.m_pNode->m_pParent;

			// 부모가 없을지도 모른다.

			if (!pParent)
			{
				// 자식이 없는데 Root 노드만 있는 경우이다.
				m_pRoot = nullptr;
			}
			else
			{
				// 이 노드가 부모의 어느쪽 자식인지를 판단한다.

				if (iter.m_pNode == pParent->m_pLeft)
				{
					// 부모의 왼쪽 자식

					// 부모의 왼쪽 자식을 없는 것으로 한다.
					pParent->m_pLeft = nullptr;
				}

				else
				{
					// 부모의 오른쪽 자식.
					pParent->m_pRight = nullptr;
				}
			}

			// 위에 까지 루트노드를 기준으로 없앴다.

			// 리스트 노드를 기준으로 없앤다.

			// 이전 노드를 받아온다.

			PNODE pPrev = iter.m_pNode->m_pPrev;

			PNODE pNext = iter.m_pNode->m_pNext;

			pPrev->m_pNext = pNext;
			pNext->m_pPrev = pPrev;

			// 부모 노드를 기준으로 ReBalance
			ReBalance(iter.m_pNode->m_pParent);

			// 노드를 삭제한다.

			delete iter.m_pNode;

			result.m_pNode = pNext;

		}

		else if (iter.m_pNode->m_pLeft && iter.m_pNode->m_pRight)
		{
			// 자식이 둘

			// 자식이 둘이라면, 왼쪽이든 오른쪽이든 자신의 위치로 올릴 자식을 가져온다.

			// 왼쪽에서 가장 키가 큰 노드는, 왼쪽 노드들 보다는 항상 키가 크고, 오른쪽 노드들
			// 보다는 항상 키가 작기 때문에 삭제하려고 하는 노드의 자리로 올 자격을 얻는다.

			// 오른쪽에서 가장 키가 작은 노드는 왼쪽 노드들 보다는 항상 키가 크고, 오른쪽 노드들 
			// 보다는 항상 키가 작기 때문에 이 역시 삭제하려고 하는 노드의 자리로 올 자격을 얻는다.

			// 구현은 왼쪽에서 가장 큰 노드를 찾아오는 것으로 한다.

			PNODE pFind = FindMax(iter.m_pNode->m_pLeft);
			PNODE pParent = pFind->m_pParent;


			// 여기서 예외처리를 통해서 찾아온 노드의 부모가 삭제하려고 하는 노드가 아닌지 확인해야한다.

			if (pFind->m_pParent == iter.m_pNode)
			{
				// 삭제하려고 하는 노드와 찾아온 노드의 부모 노드가 같다면.
				// 왼쪽 자식을 루트노르로 올린다.

				// Find노드를 부모로 준다.

				// root 노드의 오른쪽 자식을 받아둔다.
				PNODE pRight = m_pRoot->m_pRight;

				m_pRoot = pFind;
				pFind->m_pParent = nullptr;

				// 찾아온 노드의 오른쪽 자식으로 루트의 오른쪽 자식을 준다.
				// 오른쪽 자식은 부모를 기준으로 


				pFind->m_pRight = pRight;

				// 오른쪽으로 붙여준 자식의 부모를 갱신.

				pRight->m_pParent = pFind;

				// 이 경우에는 iter.m_pNode를 삭제한다.

				PNODE pPrev = iter.m_pNode->m_pPrev;

				PNODE pNext = iter.m_pNode->m_pNext;

				pPrev->m_pNext = pNext;
				pNext->m_pPrev = pPrev;

				// 노드를 삭제한다.

				ReBalance(iter.m_pNode->m_pParent);

				delete iter.m_pNode;

				result.m_pNode = pNext;

				--m_iSize;


				return result;
			}
			else
			{
				// 삭제하려고 하는 노드와 찾아온 노드의 부모 노드가 같지 않다면,

				// 찾아온 노드의 값을 현재 삭제하려고 하는 노드에 덮어 씌우고, 
				// 대신 찾아온 노드를 삭제한다.

				iter.m_pNode->first = pFind->first;
				iter.m_pNode->second = pFind->second;

				// 찾아온 노드를 삭제하리 전에 Find의 부모와 Find의 자식을 연결해준다.

				PNODE pChild = pFind->m_pLeft; // 오른쪽 자식은 없다.

				pParent->m_pRight = pChild;

				if (pChild)
					pChild->m_pParent = pParent;

				// 여기까지 트리구조에서의 삭제이다.

			}

			// 찾아온 노드를 대신 삭제한다.


			PNODE pPrev = pFind->m_pPrev;

			PNODE pNext = pFind->m_pNext;

			pPrev->m_pNext = pNext;
			pNext->m_pPrev = pPrev;

			// 노드를 삭제한다.

			ReBalance(pFind->m_pParent);

			delete pFind;

			result.m_pNode = iter.m_pNode->m_pNext;
		}

		else
		{
			// 자식이 하나

			// 하나있는 자식을 자신의 자리로 올리면 된다.

			// 자식이 하나인데, 부모가 있는 경우. 
			// 자식이 하나인데, 부모가 없는 경우.

			PNODE pParent = iter.m_pNode->m_pParent;

			if (!pParent)
			{
				// 하나있는 자식이 올라와서 루트노드가 된다.

				// 삭제하려는 노드의 자식을 가져온다.
				PNODE pChild = iter.m_pNode->m_pLeft;

				if (!pChild)
					pChild = iter.m_pNode->m_pRight;

				// 자식 노드가 Root 노드가 된다.

				m_pRoot = pChild;

				m_pRoot->m_pParent = nullptr;

				// 자식의 자식들에 대해서는 생각할 필요가 없다.
			}
			else
			{
				// 자식이 하나이고 부모는 없는 경우. (중간에 존재하는 경우)

				// 일단 삭제하려는 노드가 부모의 오른쪽 자식인지 왼쪽 자식인지 알아온다.

				// 자식 노드를 가져온다.
				PNODE pChild = iter.m_pNode->m_pLeft;

				if (!pChild)
					pChild = iter.m_pNode->m_pRight;

				if (iter.m_pNode == pParent->m_pLeft)
				{
					// 삭제하려고 하는 노드가 부모의 왼쪽 자식이다.
					// 삭제하려고 하는 노드의 자식을 부모의 왼쪽자식으로 붙여야한다.
					pParent->m_pLeft = pChild;

				}
				else
				{
					// 삭제하려는 노드가 부모의 오른쪽 자식이다.
					// 자식을 찾아서 이 자식을 부모의 오른쪽 자식으로 붙여야한다.
					pParent->m_pRight = pChild;

				}

				// 자식의 부모로 조부모를 준다.
				pChild->m_pParent = pParent;

				// 자식 이후의 자손은 생각할 필요가 없다.
			}


			PNODE pPrev = iter.m_pNode->m_pPrev;

			PNODE pNext = iter.m_pNode->m_pNext;

			pPrev->m_pNext = pNext;
			pNext->m_pPrev = pPrev;

			// 노드를 삭제한다.

			ReBalance(iter.m_pNode->m_pParent);

			delete iter.m_pNode;

			result.m_pNode = pNext;


		}

		--m_iSize;

		return result;
	}
	


private:
	// 특정 노드의 높이 차이를 구하는 함수.
	int GetHeight(PNODE pNode)
	{
		if (!pNode)
			return 0;

		int iLeft = GetHeight(pNode->m_pLeft);
		int iRight = GetHeight(pNode->m_pRight);

		if (iLeft < iRight)
			return iRight + 1;

		return iLeft + 1;
	}

	int BalanceFactor(PNODE pNode)
	{
		// 특정 노드의 BF값을 구한다. ( 왼쪽 높이 - 오른쪽 높이 )
		return GetHeight(pNode->m_pLeft) - GetHeight(pNode->m_pRight);

		// BF 값이 2 이상 차이가 난다면, 균형이 무너진 것이다.
	}

	void ReBalance(PNODE pNode)
	{
		int iBalanceFactor = BalanceFactor(pNode);

		if (abs(iBalanceFactor) < 2)
			return;
		//  BF 값의 절댓값이 2보다 작다면, 밸런스가 유지됨을 의미한다.

		if (iBalanceFactor < 0)
		{
			// 오른쪽으로 균형이 무너졌다.

			// 어떤 모양으로 균형이 무너졌는지 파악하기 위해.
			// 기준 노드의 오른쪽 노드의 BF값을 구해본다.

			if (BalanceFactor(pNode->m_pRight) > 0)
			{
				// 오른쪽 왼쪽으로 균형이 무너진 것이다.
				
				// 오른쪽 자식 노드를 기준으로 우회전
				// 기준 노드를 기준으로 좌회전.

				RotationRight(pNode->m_pRight);

				RotationLeft(pNode);

			}
			else
			{
				// 오른쪽 오른쪽으로 균형이 무너진 것이다.

				RotationLeft(pNode);

			}
		}
		else
		{
			// 왼쪽으로 균형이 무너졌다.

			if (BalanceFactor(pNode->m_pLeft) < 0)
			{
				// 왼쪽 오른쪽으로 균형이 무너진 것이다.

				// 왼쪽 자식 노드를 기준으로 좌회전.
				// 기준 노드를 기준으로 우회전.

				RotationLeft(pNode->m_pLeft);

				RotationRight(pNode);

			}
			else
			{
				// 왼쪽 왼쪽으로 균형이 무너진 것이다.

				// 기준 노드를 기준으로 우회전.

				RotationRight(pNode);

			}
		}
	}
	
	/*
	int GetHeight(PNODE pNode)
	{
		if (!pNode)
			return 0;

		int iLeft = GetHeight(pNode->m_pLeft);
		int iRight = GetHeight(pNode->m_pRight);

		if (iLeft > iRight)
			return iLeft + 1;

		return iRight + 1;
	}

	int BalanceFactor(PNODE pNode)
	{
		return GetHeight(pNode->m_pLeft) - GetHeight(pNode->m_pRight);
	}

	void ReBalance(PNODE pNode)
	{
		int iBalanceFactor = BalanceFactor(pNode);

		// 변경할 필요가 없다.
		if (abs(iBalanceFactor) < 2)
			return;


		if (iBalanceFactor < 0)
		{
			// 오른쪽으로 균형이 깨진 경우

			if (BalanceFactor(pNode->m_pRight) <= 0)
			{
				// 오른쪽 오른쪽으로 균형이 깨진 경우
				RotationLeft(pNode);
				
			}
			else
			{
				// 오른쪽 왼쪽으로 균형이 깨진 경우 

				// 기준노드의 오른쪽 자식을 기준으로 우회전.
				RotationRight(pNode->m_pRight);

				// 좌회전.
				RotationLeft(pNode);
			}
		}
		else
		{
			// 왼쪽으로 균형이 깨진 경우

			if (BalanceFactor(pNode->m_pLeft) <= 0)
			{
				// 왼쪽 오른쪽으로 균형이 깨진 경우

				// 기준노드의 왼쪽 자식을 기준으로 좌회전
				RotationLeft(pNode->m_pLeft);

				// 우회전
				RotationRight(pNode);
			}
			else
			{
				// 왼쪽 왼쪽으로 균형이 깨진 경우
				RotationRight(pNode);
			}
		}

	}

	
	*/

	iterator find(PNODE pParent, const Key& key) const
	{

		if (!pParent)
			return end();

		if (pParent->first == key)
		{
			iterator iter;
			iter.m_pNode = pParent;
			return iter;
		}

		else if (pParent->first > key)
		{
			return find(pParent->m_pLeft, key);
		}

		return find(pParent->m_pRight, key);
	}

	// 왼쪽 자식을 넣어서 마지막 오른쪽 자식을 찾아오는 함수.

	PNODE FindMax(PNODE pParent)
	{
		if (pParent->m_pRight)
			return FindMax(pParent->m_pRight);

		return pParent;
	}

	void insert(PNODE pParent, const Key& key, const Value& value)
	{
		// 기준 노드를 찾는다.

		if (pParent->first > key)
		{
			// 기준 노드의 왼쪽에 추가한다.

			if (!pParent->m_pLeft)
			{
				// 왼쪽에 자식이 없는 경우에는 왼쪽 노드에 해당 노드를 추가한다.
				PNODE pNode = new NODE;

				pNode->first = key;
				pNode->second = value;

				pParent->m_pLeft = pNode;
				pNode->m_pParent = pParent;

				// 부모의 이전 노드를 받아온다.
				PNODE pPrev = pParent->m_pPrev;

				// 부모의 이전노드를 새로 생성한 노드의 이전으로 준다.
				pNode->m_pPrev = pPrev;

				// 부모의 이전노드의 다음을 새로 생성한 노드로 준다.
				pPrev->m_pNext = pNode;

				// 새로 생성한 노드의 다음을 부모노드로 준다.
				pNode->m_pNext = pParent;

				// 부모노드의 이전을 새로생성한 노드로 준다.
				pParent->m_pPrev = pNode;



				return;
			}
			else
			{
				// 이미 왼쪽에 자식이 있는 경우에는 왼쪽 자식 노드를 기준으로 다시 함수를 호출한다.
				insert(pParent->m_pLeft, key, value);
			}
		}
		else
		{
			// 기준노드의 오른쪽에 추가한다.

			if (!pParent->m_pRight)
			{
				// 오른쪽에 자식이 없는 경우에는 노드를 오른쪽 자식으로 준다.
				PNODE pNode = new NODE;

				pNode->first = key;
				pNode->second = value;

				pNode->m_pParent = pParent;
				pParent->m_pRight = pNode;

				// 부모의 다음노드를 받아온다.
				PNODE pNext = pParent->m_pNext;

				// 부모의 다음으로 새로생성한 노드를 준다.
				pParent->m_pNext = pNode;
				pNode->m_pPrev = pParent;

				// 새로 생성한 노드의 다음으로 부모의 다음 노드를 준다.
				pNode->m_pNext = pNext;
				pNext->m_pPrev = pNode;

				return;
			}
			else
			{
				// 오른쪽에 이미 자식이 있는 경우에는 오른쪽 노드를 기준으로 다시 함수를 호출한다.
				insert(pParent->m_pRight, key, value);
			}
		}

		ReBalance(pParent);
		// 새로운 노드를 추가한 이후에 재귀적으로 밸러스를 체크하면서 문제가 있다면 교체한다.

	}


	// 기준 노드를 가지고 회전하는 함수를 만든다.

	PNODE RotationLeft(PNODE pNode)
	{

		// 기준 노드의 부모노드를 얻어온다.
		PNODE pParent = pNode->m_pParent;

		// 기준 노드의 오른쪽 자식 노드를 얻어온다.
		PNODE pChild = pNode->m_pRight;

		// 기준 노드의 오른쪽 자식 노드의 왼쪽 자식을 얻어온다.
		PNODE pLeft = pChild->m_pLeft;

		// 부모가 있을 경우 부모의 어느 자식인지 파악한다.

		if (pParent)
		{
			// 기준 노드의 위치가 부모의 어느쪽에 있었느냐에 따라서 
			// 기준 노드의 자식 노드를 연결해야 하는 위치가 달라진다.
			
			if (pParent->m_pLeft == pNode)
			{
				// 부모의 왼쪽 자식이 기준 노드
				// 자식 노드를 부모의 왼쪽으로 준다.
				pParent->m_pLeft = pChild;
			}
			else
			{
				// 부모의 오른쪽 자식이 기준 노드
				// 자식 노드를 부모의 오른쪽으로 준다.
				pParent->m_pRight = pChild;

			}

			pChild->m_pParent = pParent;
		}
		else
		{
			// 기준이 되는 노드가 Root 노드다.
			// Child 노드가 Root노드가 된다.

			m_pRoot = pChild;
			m_pRoot->m_pParent = nullptr;
		}

		// 기준 노드의 오른쪽에 Left를 붙여준다.
		pNode->m_pRight = pLeft;

		if(pLeft)
		pLeft->m_pParent = pNode;

		// Child노드의 왼쪽으로 기준 노드를 준다.
		pChild->m_pLeft = pNode;

		pNode->m_pParent = pChild;

		return pChild;
	}

	PNODE RotationRight(PNODE pNode)
	{

		// 기준 노드의 부모노드를 얻어온다.
		PNODE pParent = pNode->m_pParent;

		// 기준 노드의 왼쪽 자식 노드를 얻어온다.
		PNODE pChild = pNode->m_pLeft;

		// 기준 노드의 왼쪽 자식 노드의 오른쪽 자식을 얻어온다.
		PNODE pRight = pChild->m_pRight;

		// 부모가 있을 경우 부모의 어느 자식인지 파악한다.

		if (pParent)
		{
			// 기준 노드의 위치가 부모의 어느쪽에 있었느냐에 따라서 
			// 기준 노드의 자식 노드를 연결해야 하는 위치가 달라진다.
			
			if (pParent->m_pLeft == pNode)
			{
				// 부모의 왼쪽 자식이 기준 노드
				// 자식 노드를 부모의 왼쪽으로 준다.
				pParent->m_pLeft = pChild;
			}
			else
			{
				// 부모의 오른쪽 자식이 기준 노드
				// 자식 노드를 부모의 오른쪽으로 준다.
				pParent->m_pRight = pChild;

			}

			pChild->m_pParent = pParent;
		}
		else
		{
			// 기준이 되는 노드가 Root 노드다.
			// Child 노드가 Root노드가 된다.

			m_pRoot = pChild;
			m_pRoot->m_pParent = nullptr;
		}

		// 기준 노드의 왼쪽에 Right를 붙여준다.
		pNode->m_pLeft = pRight;

		if(pRight)
			pRight->m_pParent = pNode;

		// Child노드의 오른쪽으로 기준 노드를 준다.
		pChild->m_pRight = pNode;

		pNode->m_pParent = pChild;

		return pChild;
	}



private:
	PNODE		m_pBegin;
	PNODE		m_pEnd;
	int			m_iSize;
	PNODE		m_pRoot;

};


