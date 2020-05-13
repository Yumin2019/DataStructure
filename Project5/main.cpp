
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
		// i는 a외의 다른 int형 변수의 주소를 가질 수 없고, 역참조를 통해서 값을 변경할 수도 없다.
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
		cout << "정적 함수" << endl;
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
//	//a.output(); // 정적 멤버함수도 객체를 통해서 접근할 수 있다(일반 멤버 함수긴 하다)
//	//// 객체로도 접근할 수 있지만, 클래스의 이름을 통해서도 접근이 가능하다.
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
//	//iRef = 5; // iRef 는 NULL을 가진 레퍼런스로서, 값을 변경할 수 없다.
//			// 읽기 전용이다.
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
//	// 상수를 초기화 하지 않으면 해당 값을 사용할 수 없다.
//	// 단순한 출력도 컴파일 오류.
//
//	// 클래스에 const 멤버가 존재하는 경우 해당 값을 생성자 이니셜라이저를 통해서 초기화하지 않은 경우에 사용이 불가하다.
//	// static 멤버변수의 경우. 외부에 이 멤버 변수의 존재를 알리지 않으면 사용이 불가하다.
//
//	// -> 하지만 왜 ? 
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
//	// 삽입은 OK
//
//	//tree.insert(3, 3);
//	//tree.insert(5, 5);
//	//tree.insert(10, 10);
//	//tree.insert(20, 20);
//
//	// 이 상태에서 20을 삭제하면 다시 밸런스를 맞춰야 한다.
///*
//	tree.insert(5, 5);
//	tree.insert(1, 1);
//	tree.insert(10, 10);
//	tree.insert(15, 15);
//	tree.insert(0, 0);
//	tree.insert(20, 20);*/
//
//	// 예외처리가 필요하다.
//	tree.insert(10, 10);
//	tree.insert(5, 5);
//	tree.insert(15, 15);
//	tree.insert(4, 4);
//	tree.insert(7, 7);
//	tree.insert(20, 20);
//	tree.insert(3, 3);
//
//	// 자식이 둘, 자식이 하나, 자식이 없는 경우에서 삭제후에 밸런스 조정이 잘 되고 있다.
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

	cout << "1을 지운 이후에 iterator " << *iter << endl;

	for (iter = IntList.begin(); iter != iterEnd; ++iter)
	{
		cout << *iter << endl;
	}

	cout << " ======================= reverse iterator =======================" << endl;


	CLinkedList<int>::reverse_iterator riter;
	CLinkedList<int>::reverse_iterator riterEnd = IntList.rend();

	riter = IntList.rbegin();
	riter = IntList.erase(riter);

	cout << "10을 지우고, reverse_iterator " << *riter << endl;

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

cout << " ======================= 두 자식이 없는 경우 erase 5 =======================" << endl;

iter = tree.begin();

iter = tree.erase(iter);

cout << "지운 다음 노드" << endl;
iter->Output();

cout << " ======================= 자식이 하나 erase 10 =======================" << endl;


tree.erase(iter);

iterEnd = tree.end();

for (iter = tree.begin(); iter != iterEnd; ++iter)
{
iter->Output();
cout << endl;
}

cout << " ======================= 자식이 둘 근접한 관계의 노드 삭제 15 =======================" << endl;

iter = tree.begin();

++iter;

tree.erase(iter); // 15 삭제

iterEnd = tree.end();

for (iter = tree.begin(); iter != iterEnd; ++iter)
{
iter->Output();
cout << endl;
}

tree.clear();

cout << " ======================= 자식이 둘 인접하지 않은 노드에서15 삭제 =======================" << endl;

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

cout << " ======================= 삽입 =======================" << endl;

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

cout << " ======================= 100 push 후 clear =======================" << endl;

queue.push(100);
queue.clear();

cout << "size : " << queue.size() << endl;


*/
/*
CStack<int> stackInt;

cout << " ======================= push 이전 =======================" << endl;

cout << "capacity : " << stackInt.capacity() << endl;
cout << "size : " << stackInt.size() << endl;
cout << "empty : " << stackInt.empty() << endl;

for (int i = 0; i < 20; ++i)
{
stackInt.push(i);
cout << i << endl;
}

cout << " ======================= push 이후 =======================" << endl;


cout << "capacity : " << stackInt.capacity() << endl;
cout << "size : " << stackInt.size() << endl;
cout << "empty : " << stackInt.empty() << endl;

while (!stackInt.empty())
cout << stackInt.pop() << endl;

for (int i = 0; i < 5; ++i)
stackInt.push(i + 1);

cout << " ======================= top = 10 =======================" << endl;

stackInt.top() = 10;


cout << " ======================= reserve 30 top = 10이면 데이터 유지 =======================" << endl;

stackInt.reserve(30);

cout << "capacity : " << stackInt.capacity() << endl;
cout << "size : " << stackInt.size() << endl;
cout << "empty : " << stackInt.empty() << endl;
cout << "top : " << stackInt.top() << endl;

cout << " ======================= clear 이후  =======================" << endl;

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
// size는 그대로이고, 할당량만 증가했다는 것을 보자.

cout << " ======================= resize 40 =======================" << endl;

Intvec.resize(40);

iterEnd = Intvec.end();

for (iter = Intvec.begin(); iter != iterEnd; ++iter)
{
cout << *iter << endl;
}

cout << "capacity : " << Intvec.capacity() << endl;
cout << "size : " << Intvec.size() << endl;

// 할당량을 포함하여 사이즈까지 함께 바뀐다는 것을 보자.
// size가 바뀌어서 출력하는 정보도 달라진다.


cout << " ======================= clear =======================" << endl;

Intvec.clear();

iterEnd = Intvec.end();

for (iter = Intvec.begin(); iter != iterEnd; ++iter)
{
cout << *iter << endl;
}

cout << "깔끔" << endl;

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

cout << "1을 없애고  다음은 ? " << *iter << endl;

cout << " ======================= 출력 =======================" << endl;


iterEnd = Intvec.end();

for (iter = Intvec.begin(); iter != iterEnd; ++iter)
{
cout << *iter << endl;
}

riter = Intvec.rbegin();

riter = Intvec.erase(riter);

cout << "10을 없애고 다음은 : " << *riter << endl;


cout << " ======================= 출력 =======================" << endl;


iterEnd = Intvec.end();

for (iter = Intvec.begin(); iter != iterEnd; ++iter)
{
cout << *iter << endl;
}

cout << " ======================= 중간 삭제 =======================" << endl;

iterEnd = Intvec.end();

for (iter = Intvec.begin(); iter != iterEnd;)
{
cout << *iter << endl;

if (*iter == 3)
{
iter = Intvec.erase(iter);
iterEnd = Intvec.end();
cout << "3 삭제 이후" << endl;
}
else
++iter;
}

cout << "size : " << Intvec.size() << endl;


iterator 부분이 매우 간단하지만, iterator 구현이 되어 있지 않으면 STL의 느낌이 전혀 안 나기 때문에
간단하게 나마 구현했다.

STL 부분과 다른 부분도 명확히 존재한다.
나는 최소한 흉내만 냈다. iterator 를 이용할 수 있도록.
*/





