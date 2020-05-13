#pragma once

#include <assert.h>


template <typename T>
class CLinkedListNode
{
	template <typename T>
	friend class CLinkedList;

	template <typename T>
	friend class CLinkedListIterator;

	template <typename T>
	friend class CLinkedListReverseIterator;

public:
	CLinkedListNode()
	{
		m_pPrev = nullptr;
		m_pNext = nullptr;
	}

	~CLinkedListNode()
	{

	}

private:
	CLinkedListNode<T>*			m_pPrev;
	CLinkedListNode<T>*			m_pNext;
	T							m_Data;
};

template <typename T>
class CLinkedListIterator
{

	template <typename T>
	friend class CLinkedList;

public:
	CLinkedListIterator()
	{
		m_pNode = nullptr;
	}

	~CLinkedListIterator()
	{

	}

public:
	bool operator ==(const CLinkedListIterator<T>& iter)
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator !=(const CLinkedListIterator<T>& iter)
	{
		return m_pNode != iter.m_pNode;
	}

	void operator++()
	{
		m_pNode = m_pNode->m_pNext;
	}

	void operator++(int)
	{
		m_pNode = m_pNode->m_pNext;
	}


	void operator--()
	{
		m_pNode = m_pNode->m_pPrev;
	}

	void operator--(int)
	{
		m_pNode = m_pNode->m_pPrev;
	}

	T& operator *()
	{
		return m_pNode->m_Data;
	}

private:
	typedef CLinkedListNode<T>*		PNODE;

private:
	PNODE			m_pNode;
};


template <typename T>
class CLinkedListReverseIterator
{

	template <typename T>
	friend class CLinkedList;

public:
	CLinkedListReverseIterator()
	{
		m_pNode = nullptr;
	}

	~CLinkedListReverseIterator()
	{

	}

public:
	bool operator ==(const CLinkedListReverseIterator<T>& iter)
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator !=(const CLinkedListReverseIterator<T>& iter)
	{
		return m_pNode != iter.m_pNode;
	}

	void operator++()
	{
		m_pNode = m_pNode->m_pPrev;
	}

	void operator++(int)
	{
		m_pNode = m_pNode->m_pPrev;
	}


	void operator--()
	{
		m_pNode = m_pNode->m_pNext;
	}

	void operator--(int)
	{
		m_pNode = m_pNode->m_pNext;
	}

	T& operator *()
	{
		return m_pNode->m_Data;
	}

private:
	typedef CLinkedListNode<T>*		PNODE;

private:
	PNODE			m_pNode;
};


template <typename T>
class CLinkedList
{
public:
	CLinkedList()
	{
		m_pBegin = new NODE;
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}

	~CLinkedList()
	{
		clear();
		delete m_pBegin;
		delete m_pEnd;
	}

private:
	typedef CLinkedListNode<T>		NODE;
	typedef CLinkedListNode<T>*		PNODE;

private:
	PNODE			m_pBegin;
	PNODE			m_pEnd;
	int				m_iSize;

public:
	typedef CLinkedListIterator<T>			iterator;
	typedef CLinkedListReverseIterator<T>	reverse_iterator;



public:
	void clear()
	{
		// begin ~ end ���̿� �ִ� ��带 ��� ���ش�.

		PNODE pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			PNODE pNext = pNode->m_pNext;

			delete pNode;

			pNode = pNext;
		}

		m_iSize = 0;

		// begin�� end�� �����Ѵ�.

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
	}

	void push_back(const T& data)
	{
		PNODE pNode = new NODE;
		pNode->m_Data = data;

		// end�� ������带 �����´�.
		PNODE pPrev = m_pEnd->m_pPrev;

		// end�� ��������� ������ ���� ������ ���
		pPrev->m_pNext = pNode;
		
		// ���� ������ ����� ������ end�� ���� ���
		pNode->m_pPrev = pPrev;

		// ���� ������ ����� ������ end ���
		pNode->m_pNext = m_pEnd;

		// end����� ������ ���� ������ ���
		m_pEnd->m_pPrev = pNode;

		++m_iSize;
	}

	void push_front(const T& data)
	{
		PNODE pNode = new NODE;

		pNode->m_Data = data;

		// begin�� ������带 �����´�.
		PNODE pNext = m_pBegin->m_pNext;

		// begin�� ���� ���� ���� ������ ���
		m_pBegin->m_pNext = pNode;

		// ���� ������ ����� ������ begin ���
		pNode->m_pPrev = m_pBegin;

		// ���� ������ ����� ������ begin�� ���� ���
		pNode->m_pNext = pNext;

		// begin�� ��������� ������ ���� ������ ���
		pNext->m_pPrev = pNode;

		++m_iSize;
	}

	int		size() const
	{
		return m_iSize;
	}

	bool empty() const
	{
		return m_iSize == 0;
	}

	void pop_back()
	{
		if (empty())
		{
			assert(false);
		}

		// �ڿ� �ִ� ��带 �����Ѵ�.
		PNODE pDelete = m_pEnd->m_pPrev;

		// ������ ����� ���� ���� ���� ��带 �޾ƿ´�.
		PNODE pNext = pDelete->m_pNext;
		PNODE pPrev = pDelete->m_pPrev;

		// �������� ���� ��带 �����Ѵ�.

		pPrev->m_pNext = pNext;
		pNext->m_pPrev = pPrev;

		// ��带 �����Ѵ�.
		delete pDelete;

		--m_iSize;
	}

	void pop_front()
	{
		if (empty())
		{
			assert(false);
		}

		// �տ� �ִ� ��带 �����Ѵ�.
		PNODE pDelete = m_pBegin->m_pNext;

		// ������ ����� ���� ���� ���� ��带 �޾ƿ´�.
		PNODE pNext = pDelete->m_pNext;
		PNODE pPrev = pDelete->m_pPrev;

		// �������� ���� ��带 �����Ѵ�.

		pPrev->m_pNext = pNext;
		pNext->m_pPrev = pPrev;

		// ��带 �����Ѵ�.
		delete pDelete;

		--m_iSize;
	}

	T& front() const
	{
		if (empty())
			assert(false);

		return m_pBegin->m_pNext->m_Data;
	}

	T& back() const
	{
		if (empty())
			assert(false);

		return m_pEnd->m_pPrev->m_Data;
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

	iterator erase(iterator iter) 
	{
		if (iter.m_pNode == m_pBegin || iter.m_pNode == m_pEnd || iter.m_pNode == nullptr)
		{
			assert(false);
			return end();
		}

		// ������ ����� ������ ������ �޾ƿ´�.
		PNODE pPrev = iter.m_pNode->m_pPrev;
		PNODE pNext = iter.m_pNode->m_pNext;

		pPrev->m_pNext = pNext;
		pNext->m_pPrev = pPrev;

		delete iter.m_pNode;

		--m_iSize;

		iterator result;
		result.m_pNode = pNext;
		return result;
		
	}

	reverse_iterator erase(reverse_iterator iter) 
	{
		if (iter.m_pNode == m_pBegin || iter.m_pNode == m_pEnd || iter.m_pNode == nullptr)
		{
			assert(false);
			return rend();
		}

		// ������ ����� ������ ������ �޾ƿ´�.
		PNODE pPrev = iter.m_pNode->m_pPrev;
		PNODE pNext = iter.m_pNode->m_pNext;

		pPrev->m_pNext = pNext;
		pNext->m_pPrev = pPrev;

		delete iter.m_pNode;

		--m_iSize;
		
		reverse_iterator result;
		result.m_pNode = pPrev;
		return result;

	}

	void sort() const
	{
		// �⺻������ ������������ ������ �� �ֵ��� �Ѵ�.
		iterator iter;
		iterator iterEnd = end();
		iterator iter1End = iterEnd;

		--iterEnd;

		for (iter = begin(); iter != iterEnd; ++iter)
		{
			iterator result = iter;

			iterator iter1 = iter;
		
			++iter1;

			for (; iter1 != iter1End; ++iter1)
			{
				if ((*result) > (*iter1))
				{
					result = iter1;
				}
			}

			// �ּڰ��� iter�� �ڸ��� ��ȯ�Ѵ�.

			if (iter != result)
			{
				// �� ��尡 ����Ű�� ������踦 ������ ����, ������ ���̼��� ���ؼ� �����Ѵ�.

				T temp = iter.m_pNode->m_Data;
				iter.m_pNode->m_Data = result.m_pNode->m_Data;
				result.m_pNode->m_Data = temp;
				
			}

			
		}
	}

	void sort(bool(*pFunc)(const T&, const T&)) const
	{
		iterator iter;
		iterator iterEnd = end();
		iterator iter1End = iterEnd;

		--iterEnd;

		for (iter = begin(); iter != iterEnd; ++iter)
		{
			iterator result = iter;

			iterator iter1 = iter;
			++iter1;

			for (; iter1 != iter1End; ++iter1)
			{
				if (pFunc(*result, *iter1))
				{
					result = iter1;
				}
			}

			// �ּڰ��� iter�� �ڸ��� ��ȯ�Ѵ�.

			if (iter != result)
			{
				// �� ��尡 ����Ű�� ������踦 ������ ����, ������ ���̼��� ���ؼ� �����Ѵ�.

				T temp = iter.m_pNode->m_Data;
				iter.m_pNode->m_Data = result.m_pNode->m_Data;
				result.m_pNode->m_Data = temp;

			}
		}
	}


};

