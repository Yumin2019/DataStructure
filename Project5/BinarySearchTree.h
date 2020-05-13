#pragma once

#include <assert.h>

template <typename Key, typename Value>
class CBinarySearchTreeNode
{
	template <typename Key, typename Value>
	friend class CBinarySearchTree;

	template <typename Key, typename Value>
	friend class CBinarySearchTreeIterator;

	template <typename Key, typename Value>
	friend class CBinarySearchTreeReverseIterator;

private:
	CBinarySearchTreeNode()
	{
		m_pNext = nullptr;
		m_pPrev = nullptr;
		m_pLeft = nullptr;
		m_pRight = nullptr;
		m_pParent = nullptr;

	}

	~CBinarySearchTreeNode()
	{

	}

private:
	typedef CBinarySearchTreeNode<Key, Value>*		PNODE;

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
class CBinarySearchTreeReverseIterator
{

	template <typename Key, typename Value>
	friend class CBinarySearchTree;


private:
	typedef CBinarySearchTreeNode<Key, Value>*		PNODE;

public:
	CBinarySearchTreeReverseIterator()
	{
		m_pNode = nullptr;
	}

	~CBinarySearchTreeReverseIterator()
	{

	}

public:
	bool operator == (const CBinarySearchTreeReverseIterator<Key, Value>& iter)
	{
		return iter.m_pNode == m_pNode;
	}

	bool operator != (const CBinarySearchTreeReverseIterator<Key, Value>& iter)
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
class CBinarySearchTreeIterator
{

	template <typename Key, typename Value>
	friend class CBinarySearchTree;


private:
	typedef CBinarySearchTreeNode<Key, Value>*		PNODE;

public:
	CBinarySearchTreeIterator()
	{
		m_pNode = nullptr;
	}

	~CBinarySearchTreeIterator()
	{

	}

public:
	bool operator == (const CBinarySearchTreeIterator<Key, Value>& iter)
	{
		return iter.m_pNode == m_pNode;
	}

	bool operator != (const CBinarySearchTreeIterator<Key, Value>& iter)
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
class CBinarySearchTree
{
private:
	typedef CBinarySearchTreeNode<Key, Value>*		PNODE;
	typedef CBinarySearchTreeNode<Key, Value>		NODE;

public:
	typedef CBinarySearchTreeIterator<Key, Value>		 iterator;
	typedef CBinarySearchTreeReverseIterator<Key, Value> reverse_iterator;

public:
	CBinarySearchTree()
	{
		m_pBegin = new NODE;
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;

		m_pRoot = nullptr;

	}

	~CBinarySearchTree()
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

			delete iter.m_pNode;

			result.m_pNode = pNext;


		}

		--m_iSize;

		return result;
	}

	

private:

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

	}

	// begin end

	


private:
	PNODE		m_pBegin;
	PNODE		m_pEnd;
	int			m_iSize;
	PNODE		m_pRoot;

};

