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
			cout << "\t�θ� Key: " << m_pParent->first << endl;
		else
			cout << endl;

		if (m_pLeft)
		{
			cout << "���� �ڽ� Key : " << m_pLeft->first << endl;
		}
		else
			cout << "���� �ڽ� ����" << endl;

		if (m_pRight)
		{
			cout << "������ �ڽ� Key : " << m_pRight->first << endl;
		}
		else
			cout << "������ �ڽ� ����" << endl;
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
		// ��带 ã�ƿ��� ����̴�.

		if (empty())
			assert(false);

		return find(m_pRoot, key);
	}

	void clear()
	{
		// begin�� end������ ��� ��带 �����Ѵ�.
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
			// ��Ʈ��忡 ��带 �߰��Ѵ�.

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

		// ����ó��.
		if (iter.m_pNode == nullptr || iter.m_pNode == m_pBegin || iter.m_pNode == m_pEnd)
			assert(false);

		else if (empty())
			assert(false);

		iterator result;


		// iter�� ����Ű�� ��带 �����Ѵ�.
		// ���� ����� �ڽ��� ���� ���.
		// �ڽ��� �ϳ��� �ִ� ���
		// �ڽ��� �� ���� ���.

		if (!iter.m_pNode->m_pLeft && !iter.m_pNode->m_pRight)
		{
			// �ڽ��� ����.
			// �� ��带 ���ְ�, �θ� �ڽ��� ���踦 ���� ������ �ϸ� �ȴ�.
			// ����Ʈ�� ��� ������ ����� ������ ������ �մ´�.

			// �θ� ��带 �����´�.

			PNODE pParent = iter.m_pNode->m_pParent;

			// �θ� �������� �𸥴�.

			if (!pParent)
			{
				// �ڽ��� ���µ� Root ��常 �ִ� ����̴�.
				m_pRoot = nullptr;
			}
			else
			{
				// �� ��尡 �θ��� ����� �ڽ������� �Ǵ��Ѵ�.

				if (iter.m_pNode == pParent->m_pLeft)
				{
					// �θ��� ���� �ڽ�

					// �θ��� ���� �ڽ��� ���� ������ �Ѵ�.
					pParent->m_pLeft = nullptr;
				}

				else
				{
					// �θ��� ������ �ڽ�.
					pParent->m_pRight = nullptr;
				}
			}

			// ���� ���� ��Ʈ��带 �������� ���ݴ�.

			// ����Ʈ ��带 �������� ���ش�.

			// ���� ��带 �޾ƿ´�.

			PNODE pPrev = iter.m_pNode->m_pPrev;

			PNODE pNext = iter.m_pNode->m_pNext;

			pPrev->m_pNext = pNext;
			pNext->m_pPrev = pPrev;

			// �θ� ��带 �������� ReBalance
			ReBalance(iter.m_pNode->m_pParent);

			// ��带 �����Ѵ�.

			delete iter.m_pNode;

			result.m_pNode = pNext;

		}

		else if (iter.m_pNode->m_pLeft && iter.m_pNode->m_pRight)
		{
			// �ڽ��� ��

			// �ڽ��� ���̶��, �����̵� �������̵� �ڽ��� ��ġ�� �ø� �ڽ��� �����´�.

			// ���ʿ��� ���� Ű�� ū ����, ���� ���� ���ٴ� �׻� Ű�� ũ��, ������ ����
			// ���ٴ� �׻� Ű�� �۱� ������ �����Ϸ��� �ϴ� ����� �ڸ��� �� �ڰ��� ��´�.

			// �����ʿ��� ���� Ű�� ���� ���� ���� ���� ���ٴ� �׻� Ű�� ũ��, ������ ���� 
			// ���ٴ� �׻� Ű�� �۱� ������ �� ���� �����Ϸ��� �ϴ� ����� �ڸ��� �� �ڰ��� ��´�.

			// ������ ���ʿ��� ���� ū ��带 ã�ƿ��� ������ �Ѵ�.

			PNODE pFind = FindMax(iter.m_pNode->m_pLeft);
			PNODE pParent = pFind->m_pParent;


			// ���⼭ ����ó���� ���ؼ� ã�ƿ� ����� �θ� �����Ϸ��� �ϴ� ��尡 �ƴ��� Ȯ���ؾ��Ѵ�.

			if (pFind->m_pParent == iter.m_pNode)
			{
				// �����Ϸ��� �ϴ� ���� ã�ƿ� ����� �θ� ��尡 ���ٸ�.
				// ���� �ڽ��� ��Ʈ�븣�� �ø���.

				// Find��带 �θ�� �ش�.

				// root ����� ������ �ڽ��� �޾Ƶд�.
				PNODE pRight = m_pRoot->m_pRight;

				m_pRoot = pFind;
				pFind->m_pParent = nullptr;

				// ã�ƿ� ����� ������ �ڽ����� ��Ʈ�� ������ �ڽ��� �ش�.
				// ������ �ڽ��� �θ� �������� 


				pFind->m_pRight = pRight;

				// ���������� �ٿ��� �ڽ��� �θ� ����.

				pRight->m_pParent = pFind;

				// �� ��쿡�� iter.m_pNode�� �����Ѵ�.

				PNODE pPrev = iter.m_pNode->m_pPrev;

				PNODE pNext = iter.m_pNode->m_pNext;

				pPrev->m_pNext = pNext;
				pNext->m_pPrev = pPrev;

				// ��带 �����Ѵ�.

				ReBalance(iter.m_pNode->m_pParent);

				delete iter.m_pNode;

				result.m_pNode = pNext;

				--m_iSize;


				return result;
			}
			else
			{
				// �����Ϸ��� �ϴ� ���� ã�ƿ� ����� �θ� ��尡 ���� �ʴٸ�,

				// ã�ƿ� ����� ���� ���� �����Ϸ��� �ϴ� ��忡 ���� �����, 
				// ��� ã�ƿ� ��带 �����Ѵ�.

				iter.m_pNode->first = pFind->first;
				iter.m_pNode->second = pFind->second;

				// ã�ƿ� ��带 �����ϸ� ���� Find�� �θ�� Find�� �ڽ��� �������ش�.

				PNODE pChild = pFind->m_pLeft; // ������ �ڽ��� ����.

				pParent->m_pRight = pChild;

				if (pChild)
					pChild->m_pParent = pParent;

				// ������� Ʈ������������ �����̴�.

			}

			// ã�ƿ� ��带 ��� �����Ѵ�.


			PNODE pPrev = pFind->m_pPrev;

			PNODE pNext = pFind->m_pNext;

			pPrev->m_pNext = pNext;
			pNext->m_pPrev = pPrev;

			// ��带 �����Ѵ�.

			ReBalance(pFind->m_pParent);

			delete pFind;

			result.m_pNode = iter.m_pNode->m_pNext;
		}

		else
		{
			// �ڽ��� �ϳ�

			// �ϳ��ִ� �ڽ��� �ڽ��� �ڸ��� �ø��� �ȴ�.

			// �ڽ��� �ϳ��ε�, �θ� �ִ� ���. 
			// �ڽ��� �ϳ��ε�, �θ� ���� ���.

			PNODE pParent = iter.m_pNode->m_pParent;

			if (!pParent)
			{
				// �ϳ��ִ� �ڽ��� �ö�ͼ� ��Ʈ��尡 �ȴ�.

				// �����Ϸ��� ����� �ڽ��� �����´�.
				PNODE pChild = iter.m_pNode->m_pLeft;

				if (!pChild)
					pChild = iter.m_pNode->m_pRight;

				// �ڽ� ��尡 Root ��尡 �ȴ�.

				m_pRoot = pChild;

				m_pRoot->m_pParent = nullptr;

				// �ڽ��� �ڽĵ鿡 ���ؼ��� ������ �ʿ䰡 ����.
			}
			else
			{
				// �ڽ��� �ϳ��̰� �θ�� ���� ���. (�߰��� �����ϴ� ���)

				// �ϴ� �����Ϸ��� ��尡 �θ��� ������ �ڽ����� ���� �ڽ����� �˾ƿ´�.

				// �ڽ� ��带 �����´�.
				PNODE pChild = iter.m_pNode->m_pLeft;

				if (!pChild)
					pChild = iter.m_pNode->m_pRight;

				if (iter.m_pNode == pParent->m_pLeft)
				{
					// �����Ϸ��� �ϴ� ��尡 �θ��� ���� �ڽ��̴�.
					// �����Ϸ��� �ϴ� ����� �ڽ��� �θ��� �����ڽ����� �ٿ����Ѵ�.
					pParent->m_pLeft = pChild;

				}
				else
				{
					// �����Ϸ��� ��尡 �θ��� ������ �ڽ��̴�.
					// �ڽ��� ã�Ƽ� �� �ڽ��� �θ��� ������ �ڽ����� �ٿ����Ѵ�.
					pParent->m_pRight = pChild;

				}

				// �ڽ��� �θ�� ���θ� �ش�.
				pChild->m_pParent = pParent;

				// �ڽ� ������ �ڼ��� ������ �ʿ䰡 ����.
			}


			PNODE pPrev = iter.m_pNode->m_pPrev;

			PNODE pNext = iter.m_pNode->m_pNext;

			pPrev->m_pNext = pNext;
			pNext->m_pPrev = pPrev;

			// ��带 �����Ѵ�.

			ReBalance(iter.m_pNode->m_pParent);

			delete iter.m_pNode;

			result.m_pNode = pNext;


		}

		--m_iSize;

		return result;
	}
	


private:
	// Ư�� ����� ���� ���̸� ���ϴ� �Լ�.
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
		// Ư�� ����� BF���� ���Ѵ�. ( ���� ���� - ������ ���� )
		return GetHeight(pNode->m_pLeft) - GetHeight(pNode->m_pRight);

		// BF ���� 2 �̻� ���̰� ���ٸ�, ������ ������ ���̴�.
	}

	void ReBalance(PNODE pNode)
	{
		int iBalanceFactor = BalanceFactor(pNode);

		if (abs(iBalanceFactor) < 2)
			return;
		//  BF ���� ������ 2���� �۴ٸ�, �뷱���� �������� �ǹ��Ѵ�.

		if (iBalanceFactor < 0)
		{
			// ���������� ������ ��������.

			// � ������� ������ ���������� �ľ��ϱ� ����.
			// ���� ����� ������ ����� BF���� ���غ���.

			if (BalanceFactor(pNode->m_pRight) > 0)
			{
				// ������ �������� ������ ������ ���̴�.
				
				// ������ �ڽ� ��带 �������� ��ȸ��
				// ���� ��带 �������� ��ȸ��.

				RotationRight(pNode->m_pRight);

				RotationLeft(pNode);

			}
			else
			{
				// ������ ���������� ������ ������ ���̴�.

				RotationLeft(pNode);

			}
		}
		else
		{
			// �������� ������ ��������.

			if (BalanceFactor(pNode->m_pLeft) < 0)
			{
				// ���� ���������� ������ ������ ���̴�.

				// ���� �ڽ� ��带 �������� ��ȸ��.
				// ���� ��带 �������� ��ȸ��.

				RotationLeft(pNode->m_pLeft);

				RotationRight(pNode);

			}
			else
			{
				// ���� �������� ������ ������ ���̴�.

				// ���� ��带 �������� ��ȸ��.

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

		// ������ �ʿ䰡 ����.
		if (abs(iBalanceFactor) < 2)
			return;


		if (iBalanceFactor < 0)
		{
			// ���������� ������ ���� ���

			if (BalanceFactor(pNode->m_pRight) <= 0)
			{
				// ������ ���������� ������ ���� ���
				RotationLeft(pNode);
				
			}
			else
			{
				// ������ �������� ������ ���� ��� 

				// ���س���� ������ �ڽ��� �������� ��ȸ��.
				RotationRight(pNode->m_pRight);

				// ��ȸ��.
				RotationLeft(pNode);
			}
		}
		else
		{
			// �������� ������ ���� ���

			if (BalanceFactor(pNode->m_pLeft) <= 0)
			{
				// ���� ���������� ������ ���� ���

				// ���س���� ���� �ڽ��� �������� ��ȸ��
				RotationLeft(pNode->m_pLeft);

				// ��ȸ��
				RotationRight(pNode);
			}
			else
			{
				// ���� �������� ������ ���� ���
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

	// ���� �ڽ��� �־ ������ ������ �ڽ��� ã�ƿ��� �Լ�.

	PNODE FindMax(PNODE pParent)
	{
		if (pParent->m_pRight)
			return FindMax(pParent->m_pRight);

		return pParent;
	}

	void insert(PNODE pParent, const Key& key, const Value& value)
	{
		// ���� ��带 ã�´�.

		if (pParent->first > key)
		{
			// ���� ����� ���ʿ� �߰��Ѵ�.

			if (!pParent->m_pLeft)
			{
				// ���ʿ� �ڽ��� ���� ��쿡�� ���� ��忡 �ش� ��带 �߰��Ѵ�.
				PNODE pNode = new NODE;

				pNode->first = key;
				pNode->second = value;

				pParent->m_pLeft = pNode;
				pNode->m_pParent = pParent;

				// �θ��� ���� ��带 �޾ƿ´�.
				PNODE pPrev = pParent->m_pPrev;

				// �θ��� ������带 ���� ������ ����� �������� �ش�.
				pNode->m_pPrev = pPrev;

				// �θ��� ��������� ������ ���� ������ ���� �ش�.
				pPrev->m_pNext = pNode;

				// ���� ������ ����� ������ �θ���� �ش�.
				pNode->m_pNext = pParent;

				// �θ����� ������ ���λ����� ���� �ش�.
				pParent->m_pPrev = pNode;



				return;
			}
			else
			{
				// �̹� ���ʿ� �ڽ��� �ִ� ��쿡�� ���� �ڽ� ��带 �������� �ٽ� �Լ��� ȣ���Ѵ�.
				insert(pParent->m_pLeft, key, value);
			}
		}
		else
		{
			// ���س���� �����ʿ� �߰��Ѵ�.

			if (!pParent->m_pRight)
			{
				// �����ʿ� �ڽ��� ���� ��쿡�� ��带 ������ �ڽ����� �ش�.
				PNODE pNode = new NODE;

				pNode->first = key;
				pNode->second = value;

				pNode->m_pParent = pParent;
				pParent->m_pRight = pNode;

				// �θ��� ������带 �޾ƿ´�.
				PNODE pNext = pParent->m_pNext;

				// �θ��� �������� ���λ����� ��带 �ش�.
				pParent->m_pNext = pNode;
				pNode->m_pPrev = pParent;

				// ���� ������ ����� �������� �θ��� ���� ��带 �ش�.
				pNode->m_pNext = pNext;
				pNext->m_pPrev = pNode;

				return;
			}
			else
			{
				// �����ʿ� �̹� �ڽ��� �ִ� ��쿡�� ������ ��带 �������� �ٽ� �Լ��� ȣ���Ѵ�.
				insert(pParent->m_pRight, key, value);
			}
		}

		ReBalance(pParent);
		// ���ο� ��带 �߰��� ���Ŀ� ��������� �뷯���� üũ�ϸ鼭 ������ �ִٸ� ��ü�Ѵ�.

	}


	// ���� ��带 ������ ȸ���ϴ� �Լ��� �����.

	PNODE RotationLeft(PNODE pNode)
	{

		// ���� ����� �θ��带 ���´�.
		PNODE pParent = pNode->m_pParent;

		// ���� ����� ������ �ڽ� ��带 ���´�.
		PNODE pChild = pNode->m_pRight;

		// ���� ����� ������ �ڽ� ����� ���� �ڽ��� ���´�.
		PNODE pLeft = pChild->m_pLeft;

		// �θ� ���� ��� �θ��� ��� �ڽ����� �ľ��Ѵ�.

		if (pParent)
		{
			// ���� ����� ��ġ�� �θ��� ����ʿ� �־����Ŀ� ���� 
			// ���� ����� �ڽ� ��带 �����ؾ� �ϴ� ��ġ�� �޶�����.
			
			if (pParent->m_pLeft == pNode)
			{
				// �θ��� ���� �ڽ��� ���� ���
				// �ڽ� ��带 �θ��� �������� �ش�.
				pParent->m_pLeft = pChild;
			}
			else
			{
				// �θ��� ������ �ڽ��� ���� ���
				// �ڽ� ��带 �θ��� ���������� �ش�.
				pParent->m_pRight = pChild;

			}

			pChild->m_pParent = pParent;
		}
		else
		{
			// ������ �Ǵ� ��尡 Root ����.
			// Child ��尡 Root��尡 �ȴ�.

			m_pRoot = pChild;
			m_pRoot->m_pParent = nullptr;
		}

		// ���� ����� �����ʿ� Left�� �ٿ��ش�.
		pNode->m_pRight = pLeft;

		if(pLeft)
		pLeft->m_pParent = pNode;

		// Child����� �������� ���� ��带 �ش�.
		pChild->m_pLeft = pNode;

		pNode->m_pParent = pChild;

		return pChild;
	}

	PNODE RotationRight(PNODE pNode)
	{

		// ���� ����� �θ��带 ���´�.
		PNODE pParent = pNode->m_pParent;

		// ���� ����� ���� �ڽ� ��带 ���´�.
		PNODE pChild = pNode->m_pLeft;

		// ���� ����� ���� �ڽ� ����� ������ �ڽ��� ���´�.
		PNODE pRight = pChild->m_pRight;

		// �θ� ���� ��� �θ��� ��� �ڽ����� �ľ��Ѵ�.

		if (pParent)
		{
			// ���� ����� ��ġ�� �θ��� ����ʿ� �־����Ŀ� ���� 
			// ���� ����� �ڽ� ��带 �����ؾ� �ϴ� ��ġ�� �޶�����.
			
			if (pParent->m_pLeft == pNode)
			{
				// �θ��� ���� �ڽ��� ���� ���
				// �ڽ� ��带 �θ��� �������� �ش�.
				pParent->m_pLeft = pChild;
			}
			else
			{
				// �θ��� ������ �ڽ��� ���� ���
				// �ڽ� ��带 �θ��� ���������� �ش�.
				pParent->m_pRight = pChild;

			}

			pChild->m_pParent = pParent;
		}
		else
		{
			// ������ �Ǵ� ��尡 Root ����.
			// Child ��尡 Root��尡 �ȴ�.

			m_pRoot = pChild;
			m_pRoot->m_pParent = nullptr;
		}

		// ���� ����� ���ʿ� Right�� �ٿ��ش�.
		pNode->m_pLeft = pRight;

		if(pRight)
			pRight->m_pParent = pNode;

		// Child����� ���������� ���� ��带 �ش�.
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


