#include "LinkedList.h"
#include "SequnceList.h"
#include "StaticList.h"
#include "CycleList.h"
#include "DoubleList.h"
#include "DoubleCircularList.h"

void SequnceListTest() {
	SequnceList<int>l(10, 10);
	l.InsertElem(5, 20);
	l.InsertElem(1, 30);
	l.InsertElem(13, 50);
	l.InsertElem(13, 45);
	std::cout << *l.GetLastData() << "\n";
	std::cout << l.GetLength() << "\n";
	l.DisplayList();

	l.DeleteElem(50);
	l.DisplayList();

	l.DeleteElem(6);
	l.DisplayList();
	l.DeleteElem(1);
	l.DisplayList();


	l.ModifyElem(l.GetLength(), 12345);
	l.DisplayList();
	size_t index = l.FindElem(192037123);
	if (index != ERROR_INDEX) {
		std::cout << index << "\n";
	}
	else {
		std::cout << "ERROR_INDEX!\n";
	}
}

void LinkedListTest() {
	LinkedList<int>l;
	l.CreateLinkedList(10, 5);
	l.PushBack(20);
	l.PushFront(10);
	l.DisplayLinkedList();
	LinkedList<int>* ptr = l.FindElem(10);
	if (ptr != nullptr) {
		std::cout << ptr->GetElem() << "\n";
	}
	else {
		std::cout << "nullptr" << "\n";
	}
	l.InsertAfter(ptr, 20);
	l.InsertFront(ptr, 99);
	l.DisplayLinkedList();
	l.EraseElem(ptr);
	l.DisplayLinkedList();
}

void StaticListTest() {
	StaticList<int> l;
	l.InitList();
	l.InsertFront(1,10);
	l.InsertFront(2,20);
	l.InsertFront(3,30);
	l.InsertFront(4, 25);
	l.InsertFront(4, 50);
	l.InsertFront(3, 10);
	l.InsertBack(1, 55);
	l.InsertBack(1, 56);
	l.DisplayStaticList();
	std::cout << "--------------------------\n";
	size_t i = l.FindElem(80);
	if (i != ERROR_INDEX) {
		std::cout << "i:" << i << "\n";
	}
	else {
		std::cout << "ERRORINDEX\n";
	}
	int elem = l.GetElemAtIndex(1);
	std::cout << "elem:" << elem << "\n";
	l.ModifyElemAtIndex(1, 999);
	l.DisplayStaticList();
	//l.DeleteElemAtIndex(1);
	//l.DeleteElemAtIndex(3);
	//l.DisplayStaticList();
	//std::cout << "length:" << l.GetLength() << "\n";

}

void CycleListTest() {
	CycleList<int>l(10);
	l.printfList();
}

void DoubleListTest() {
	DoubleList<int>l(10,5);
	l.ForeachListForward();
	std::cout << "\n";
	//l.InsertAtIndexFront(10, 20);
	l.InsertAtIndexRear(1, 10000);
	l.ForeachListForward();
	std::cout << "\n";
	//l.EraseElemAtIndex(1);
	//l.EraseElemAtIndex(10);
	
	//l.EraseElememts(3);
	//l.ForeachListForward();
	//l.ForeachListForward();

	size_t index1 = l.FindElemInverse(3);
	size_t index2 = l.FindElemReverse(3);
	if (index1 != ERROR_DOUBLELIST_INDEX) {
		std::cout << "FindElemInverse 3 Index:" << index1 << "\n";
	}
	if (index2 != ERROR_DOUBLELIST_INDEX) {
		std::cout << "FindElemReverse 3 Index:" << index2 << "\n";
	}


	l.ModifyElements(3, 999);
	l.ModifyElemAtIndex(1, 7865);
	l.ForeachListForward();
}

void DoubleCircularTest() {
	DoubleCircularList<int> l;
	l.CreateList(10);
//	l.printListForward();
//	l.printListReverse();
	l.InsertElemFront(1, 999);
	l.ModifyElemAtIndex(2, 1080);
	size_t length = l.GetLength();
	l.InsertElemRear(length, 12000);
	std::cout << "FindElem(12000):" << l.FindElem(12000) << "\n";
	std::cout << "GetElem(1):" << l.GetElem(1) << "\n";
	length = l.GetLength();
	//l.InsertElemFront(length, 5555);
	l.printListForward();
	l.DeleteElemAtIndex(12);
	l.printListForward();
	l.printListReverse();


}

int main() {
	//StaticListTest();
	//CycleListTest();
	//DoubleListTest();
	DoubleCircularTest();
	return 0;
}