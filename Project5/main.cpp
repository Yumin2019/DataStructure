
#include <iostream>
#include <time.h>
#include <list>
#include "LinkedList.h"
#include <vector>
#include "Vector.h"
#include <stack>
#include "Stack.h"
#include <queue>
#include "Queue.h"
#include "Graph.h"
#include "Heap.h"
#include "Dijkstra.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"

using namespace std;

bool Sort(const int& i1, const int& i2)
{
	return i1 > i2;
}

void Output(const char& a)
{
	cout << a << "  ->";
}

class A
{
public:
	A()
	{
		this;
	}

	~A()
	{

	}

	void Output() const
	{
		const int* const i = &a;
		// i�� a���� �ٸ� int�� ������ �ּҸ� ���� �� ����, �������� ���ؼ� ���� ������ ���� ����.
		this;
		cout << a << endl;
		cout << b << endl;
		cout << c << endl;
	}

	void Output2()
	{
		cout << a << endl;
		cout << b << endl;
		cout << c << endl;
	}

	void Output1()
	{
		cout << a << endl;
		cout << b << endl;
		cout << c << endl;
	}

	static void output()
	{
		cout << "���� �Լ�" << endl;
	}

	void Ref(const int& i)
	{
		cout << i << endl;
	}

private:
	int a;
	int b;
	int c;

};

class ConstMember
{
public:
	ConstMember() :
		m_iNumber(3)
	{
	}

public:
	const int m_iNumber;
	static int m_sInt;
	int m_iInt;

};

int ConstMember::m_sInt;


int main()
{
	srand((unsigned int)time(0));
	rand();

//	A a;
//	A b;
//	a.Output();
//	//a.output(); // ���� ����Լ��� ��ü�� ���ؼ� ������ �� �ִ�(�Ϲ� ��� �Լ��� �ϴ�)
//	//// ��ü�ε� ������ �� ������, Ŭ������ �̸��� ���ؼ��� ������ �����ϴ�.
//
//	//A::output();
//	cout << "sizeof(A) : " << sizeof(a) << endl;
//	cout << "sizeof(A) : " << sizeof(b) << endl;
//
//	cout << "sizeof(void*) : " << sizeof(void*) << endl;
//	cout << "sizeof(int*) : " << sizeof(int*) << endl;
//	cout << "sizeof(float*) : " << sizeof(float*) << endl;
//	cout << "sizeof(double*) : " << sizeof(double*) << endl;
//	cout << "sizeof(char*) : " << sizeof(char*) << endl;
//
//	int i = 0;
//
//	int* pInt = NULL;
//
//	a.Ref(NULL);
//
//
//	const int& iRef = NULL;
//
//	//iRef = 5; // iRef �� NULL�� ���� ���۷����μ�, ���� ������ �� ����.
//			// �б� �����̴�.
//
//	cout << pInt << endl;
//	cout << iRef << endl;
//
//	ConstMember cm;
//
//	cout << cm.m_iNumber << endl;
//
//	const int iNum = 3;
//
//	cout << iNum << endl;
//
//	/*const double cDouble;
//
//	cout << cDouble << endl;
//
//	const char cChar;
//
//	cout << cChar << endl;
//
//	const bool cBool;
//
//	cout << cBool << endl;*/
//
//	cout << cm.m_sInt << endl;
//	cout << cm.m_iInt << endl;
//
//	// ����� �ʱ�ȭ ���� ������ �ش� ���� ����� �� ����.
//	// �ܼ��� ��µ� ������ ����.
//
//	// Ŭ������ const ����� �����ϴ� ��� �ش� ���� ������ �̴ϼȶ������� ���ؼ� �ʱ�ȭ���� ���� ��쿡 ����� �Ұ��ϴ�.
//	// static ��������� ���. �ܺο� �� ��� ������ ���縦 �˸��� ������ ����� �Ұ��ϴ�.
//
//	// -> ������ �� ? 
//
//
//
////
//	CAVLTree<int, int> tree;
//
//	/*tree.insert(10, 10);
//	tree.insert(5, 5);
//	tree.insert(15, 15);
//	tree.insert(4, 4);
//	tree.insert(7, 7);
//	tree.insert(20, 20);
//	tree.insert(3, 3);*/
//
//	//tree.insert(10, 10);
//	//tree.insert(5, 5);
//	//tree.insert(3, 3);
//	//tree.insert(20, 20);
//	//tree.insert(30, 30); 
//	// ������ OK
//
//	//tree.insert(3, 3);
//	//tree.insert(5, 5);
//	//tree.insert(10, 10);
//	//tree.insert(20, 20);
//
//	// �� ���¿��� 20�� �����ϸ� �ٽ� �뷱���� ����� �Ѵ�.
///*
//	tree.insert(5, 5);
//	tree.insert(1, 1);
//	tree.insert(10, 10);
//	tree.insert(15, 15);
//	tree.insert(0, 0);
//	tree.insert(20, 20);*/
//
//	// ����ó���� �ʿ��ϴ�.
//	tree.insert(10, 10);
//	tree.insert(5, 5);
//	tree.insert(15, 15);
//	tree.insert(4, 4);
//	tree.insert(7, 7);
//	tree.insert(20, 20);
//	tree.insert(3, 3);
//
//	// �ڽ��� ��, �ڽ��� �ϳ�, �ڽ��� ���� ��쿡�� �����Ŀ� �뷱�� ������ �� �ǰ� �ִ�.
//	cout << " ======================= iterator =======================" << endl;
//
//	CAVLTree<int, int>::iterator iter;
//	CAVLTree<int, int>::iterator iterEnd = tree.end();
//
//	iter = tree.find(20);
//	tree.erase(iter);
//
//	for (iter = tree.begin(); iter != iterEnd; ++iter)
//	{
//		iter->Output();
//		cout << endl;
//	}
//
//



	CLinkedList<int> IntList;

	for (int i = 1; i <= 10; ++i)
	{
		IntList.push_back(i);
	}

	cout << " ======================= iterator =======================" << endl;

	CLinkedList<int>::iterator iter;
	CLinkedList<int>::iterator iterEnd = IntList.end();

	iter = IntList.begin();

	iter = IntList.erase(iter);

	cout << "1�� ���� ���Ŀ� iterator " << *iter << endl;

	for (iter = IntList.begin(); iter != iterEnd; ++iter)
	{
		cout << *iter << endl;
	}

	cout << " ======================= reverse iterator =======================" << endl;


	CLinkedList<int>::reverse_iterator riter;
	CLinkedList<int>::reverse_iterator riterEnd = IntList.rend();

	riter = IntList.rbegin();
	riter = IntList.erase(riter);

	cout << "10�� �����, reverse_iterator " << *riter << endl;

	for (riter = IntList.rbegin(); riter != riterEnd; ++riter)
	{
		cout << *riter << endl;
	}

	IntList.clear();

	cout << "empty " << IntList.empty() << endl;
	cout << "size " << IntList.size() << endl;

	cout << " ======================= 1 ~ 10 push_front =======================" << endl;

	for (int i = 1; i <= 10; ++i)
	{
		IntList.push_front(i);
	}

	iterEnd = IntList.end();

	for (iter = IntList.begin(); iter != iterEnd; ++iter)
	{
		cout << *iter << endl;
	}

	IntList.pop_back();
	IntList.pop_front();

	cout << " ======================= pop back, front =======================" << endl;

	iterEnd = IntList.end();

	for (iter = IntList.begin(); iter != iterEnd; ++iter)
	{
		cout << *iter << endl;
	}



	IntList.clear();

	cout << " ======================= random data =======================" << endl;

	for (int i = 0; i < 10; ++i)
	{
		int iRandom = rand();
		IntList.push_back(iRandom);

		cout << iRandom << endl;
	}


	IntList.sort(Sort); // IntList.sort();

	cout << " ======================= sort =======================" << endl;

	iterEnd = IntList.end();

	for (iter = IntList.begin(); iter != iterEnd; ++iter)
	{
		cout << *iter << endl;
	}



	
	return 0;
}


/*

CBinarySearchTree<int, int> tree;

tree.insert(10, 10);
tree.insert(5, 5);
tree.insert(15, 15);
tree.insert(12, 12);
tree.insert(20, 20);

cout << " ======================= iterator =======================" << endl;

CBinarySearchTree<int, int>::iterator iter;
CBinarySearchTree<int, int>::iterator iterEnd = tree.end();

for (iter = tree.begin(); iter != iterEnd; ++iter)
{
iter->Output();
cout << endl;
}

cout << "empty : " << tree.empty() << endl;
cout << "size : " << tree.size() << endl;

cout << " ======================= reverse_iterator =======================" << endl;


CBinarySearchTree<int, int>::reverse_iterator riter;
CBinarySearchTree<int, int>::reverse_iterator riterEnd = tree.rend();

for (riter = tree.rbegin(); riter != riterEnd; ++riter)
{
riter->Output();
cout << endl;
}

cout << " ======================= �� �ڽ��� ���� ��� erase 5 =======================" << endl;

iter = tree.begin();

iter = tree.erase(iter);

cout << "���� ���� ���" << endl;
iter->Output();

cout << " ======================= �ڽ��� �ϳ� erase 10 =======================" << endl;


tree.erase(iter);

iterEnd = tree.end();

for (iter = tree.begin(); iter != iterEnd; ++iter)
{
iter->Output();
cout << endl;
}

cout << " ======================= �ڽ��� �� ������ ������ ��� ���� 15 =======================" << endl;

iter = tree.begin();

++iter;

tree.erase(iter); // 15 ����

iterEnd = tree.end();

for (iter = tree.begin(); iter != iterEnd; ++iter)
{
iter->Output();
cout << endl;
}

tree.clear();

cout << " ======================= �ڽ��� �� �������� ���� ��忡��15 ���� =======================" << endl;

tree.insert(10, 10);
tree.insert(5, 5);
tree.insert(15, 15);
tree.insert(12, 12);
tree.insert(20, 20);
tree.insert(11, 11);
tree.insert(13, 13);

iter = tree.find(15);

tree.erase(iter);


iterEnd = tree.end();

for (iter = tree.begin(); iter != iterEnd; ++iter)
{
iter->Output();
cout << endl;
}
*/

/*


CLinkedList<const char*> list;
CDijkstra<const char*> graph;

graph.AddNode("A");
graph.AddNode("B");
graph.AddNode("C");
graph.AddNode("D");
graph.AddNode("E");
graph.AddNode("F");

graph.AddEdge("A", "B", 1);
graph.AddEdge("B", "C", 1);
graph.AddEdge("A", "C", 3);
graph.AddEdge("C", "D", 5);
graph.AddEdge("D", "F", 3);
graph.AddEdge("C", "F", 10);
graph.AddEdge("C", "E", 5);
graph.AddEdge("E", "F", 2);

graph.Dijkstra(list, "A", "F");

CLinkedList<const char*>::iterator iter;
CLinkedList<const char*>::iterator iterEnd = list.end();

for (iter = list.begin(); iter != iterEnd; ++iter)
{
cout << *iter << " -> ";
}


*/
/*

CHeap<int> heap;

cout << " ======================= ���� =======================" << endl;

for (int i = 0; i < 10; ++i)
{
int iRandom = rand();
heap.insert(iRandom);

cout << iRandom << endl;
}

cout << " ======================= pop =======================" << endl;


while (!heap.empty())
cout << heap.pop() << endl;

*/
/*
CGraph<char> charGraph;

charGraph.AddVertex('A');
charGraph.AddVertex('B');
charGraph.AddVertex('C');
charGraph.AddVertex('D');
charGraph.AddVertex('E');


charGraph.AddEdge('A', 'B');
charGraph.AddEdge('A', 'C');
charGraph.AddEdge('C', 'D');
charGraph.AddEdge('C', 'E');

cout << " ======================= DFS =======================" << endl;
charGraph.DFS('A', Output);
cout << endl;

cout << " ======================= BFS =======================" << endl;
charGraph.BFS('A', Output);
cout << endl;


*/

/*

CQueue<int>		queue;
cout << " ======================= push 1 ~ 5 =======================" << endl;


for (int i = 1; i <= 5; ++i)
{
queue.push(i);
}

cout << "size : " << queue.size() << endl;
cout << "front : " << queue.front() << endl;
cout << "back : " << queue.back() << endl;

cout << " ======================= pop =======================" << endl;

while (!queue.empty())
{
cout << queue.pop() << endl;
}

cout << " ======================= 100 push �� clear =======================" << endl;

queue.push(100);
queue.clear();

cout << "size : " << queue.size() << endl;


*/
/*
CStack<int> stackInt;

cout << " ======================= push ���� =======================" << endl;

cout << "capacity : " << stackInt.capacity() << endl;
cout << "size : " << stackInt.size() << endl;
cout << "empty : " << stackInt.empty() << endl;

for (int i = 0; i < 20; ++i)
{
stackInt.push(i);
cout << i << endl;
}

cout << " ======================= push ���� =======================" << endl;


cout << "capacity : " << stackInt.capacity() << endl;
cout << "size : " << stackInt.size() << endl;
cout << "empty : " << stackInt.empty() << endl;

while (!stackInt.empty())
cout << stackInt.pop() << endl;

for (int i = 0; i < 5; ++i)
stackInt.push(i + 1);

cout << " ======================= top = 10 =======================" << endl;

stackInt.top() = 10;


cout << " ======================= reserve 30 top = 10�̸� ������ ���� =======================" << endl;

stackInt.reserve(30);

cout << "capacity : " << stackInt.capacity() << endl;
cout << "size : " << stackInt.size() << endl;
cout << "empty : " << stackInt.empty() << endl;
cout << "top : " << stackInt.top() << endl;

cout << " ======================= clear ����  =======================" << endl;

stackInt.clear();

while (!stackInt.empty())
cout << stackInt.pop() << endl;

*/

/*
CVector<int> Intvec;

cout << " ======================= push_back =======================" << endl;

for (int i = 1; i <= 10; ++i)
{
Intvec.push_back(i);
cout << i << endl;
}

cout << " ======================= iterator =======================" << endl;

CVector<int>::iterator iter;
CVector<int>::iterator iterEnd = Intvec.end();

for (iter = Intvec.begin(); iter != iterEnd; ++iter)
{
cout << *iter << endl;
}

cout << " ======================= reverse iterator =======================" << endl;

CVector<int>::reverse_iterator riter;
CVector<int>::reverse_iterator riterEnd = Intvec.rend();

for (riter = Intvec.rbegin(); riter != riterEnd; ++riter)
{
cout << *riter << endl;
}

cout << "empty : " << Intvec.empty() << endl;
cout << "size : " << Intvec.size() << endl;
cout << "capacity : " << Intvec.capacity() << endl;

Intvec.pop_back();

cout << " ======================= pop back =======================" << endl;

iterEnd = Intvec.end();

for (iter = Intvec.begin(); iter != iterEnd; ++iter)
{
cout << *iter << endl;
}

cout << " ======================= front 100  back 200 =======================" << endl;

Intvec.front() = 100;
Intvec.back() = 200;

iterEnd = Intvec.end();

for (iter = Intvec.begin(); iter != iterEnd; ++iter)
{
cout << *iter << endl;
}

cout << "capapcity : " << Intvec.capacity() << endl;
cout << "size : " << Intvec.size() << endl;

cout << " ======================= reserve 30 =======================" << endl;

Intvec.reserve(30);

iterEnd = Intvec.end();

for (iter = Intvec.begin(); iter != iterEnd; ++iter)
{
cout << *iter << endl;
}

cout << "capacity : " << Intvec.capacity() << endl;
cout << "size : " << Intvec.size() << endl;
// size�� �״���̰�, �Ҵ緮�� �����ߴٴ� ���� ����.

cout << " ======================= resize 40 =======================" << endl;

Intvec.resize(40);

iterEnd = Intvec.end();

for (iter = Intvec.begin(); iter != iterEnd; ++iter)
{
cout << *iter << endl;
}

cout << "capacity : " << Intvec.capacity() << endl;
cout << "size : " << Intvec.size() << endl;

// �Ҵ緮�� �����Ͽ� ��������� �Բ� �ٲ�ٴ� ���� ����.
// size�� �ٲ� ����ϴ� ������ �޶�����.


cout << " ======================= clear =======================" << endl;

Intvec.clear();

iterEnd = Intvec.end();

for (iter = Intvec.begin(); iter != iterEnd; ++iter)
{
cout << *iter << endl;
}

cout << "���" << endl;

cout << " ======================= random data =======================" << endl;

for (int i = 0; i < 10; ++i)
{
int iData = rand();

Intvec.push_back(iData);

cout << iData << endl;
}

cout << " ======================= sort =======================" << endl;

Intvec.sort(Sort); // Intvec.sort();

iterEnd = Intvec.end();

for (iter = Intvec.begin(); iter != iterEnd; ++iter)
{
cout << *iter << endl;
}

Intvec.clear();

cout << " ======================= clear & 1 ~ 10 push =======================" << endl;

for (int i = 1; i <= 10; ++i)
{
Intvec.push_back(i);
cout << i << endl;

}

iter = Intvec.begin();

iter = Intvec.erase(iter);

cout << "1�� ���ְ�  ������ ? " << *iter << endl;

cout << " ======================= ��� =======================" << endl;


iterEnd = Intvec.end();

for (iter = Intvec.begin(); iter != iterEnd; ++iter)
{
cout << *iter << endl;
}

riter = Intvec.rbegin();

riter = Intvec.erase(riter);

cout << "10�� ���ְ� ������ : " << *riter << endl;


cout << " ======================= ��� =======================" << endl;


iterEnd = Intvec.end();

for (iter = Intvec.begin(); iter != iterEnd; ++iter)
{
cout << *iter << endl;
}

cout << " ======================= �߰� ���� =======================" << endl;

iterEnd = Intvec.end();

for (iter = Intvec.begin(); iter != iterEnd;)
{
cout << *iter << endl;

if (*iter == 3)
{
iter = Intvec.erase(iter);
iterEnd = Intvec.end();
cout << "3 ���� ����" << endl;
}
else
++iter;
}

cout << "size : " << Intvec.size() << endl;


iterator �κ��� �ſ� ����������, iterator ������ �Ǿ� ���� ������ STL�� ������ ���� �� ���� ������
�����ϰ� ���� �����ߴ�.

STL �κа� �ٸ� �κе� ��Ȯ�� �����Ѵ�.
���� �ּ��� �䳻�� �´�. iterator �� �̿��� �� �ֵ���.
*/





