#include "LinkedList.h"
#include "SequnceList.h"
#include "StaticList.h"

void SequnceListTest() {
	SequnceList<int>l(10, 10);
	l.InsertElem(5, 20);
	l.InsertElem(1, 30);
	l.InsertElem(13, 50);
	l.InsertElem(13, 45);
	cout << *l.GetLastData() << endl;
	cout << l.GetLength() << endl;
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
		cout << index << endl;
	}
	else {
		cout << "ERROR_INDEX!\n";
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
		cout << ptr->GetElem() << endl;
	}
	else {
		cout << "nullptr" << endl;
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
	cout << "--------------------------\n";
	size_t i = l.FindElem(80);
	if (i != ERROR_INDEX) {
		cout << "i:" << i << endl;
	}
	else {
		cout << "ERRORINDEX\n";
	}
	int elem = l.GetElemAtIndex(1);
	cout << "elem:" << elem << endl;
	l.ModifyElemAtIndex(1, 999);
	l.DisplayStaticList();
	//l.DeleteElemAtIndex(1);
	//l.DeleteElemAtIndex(3);
	//l.DisplayStaticList();
	//cout << "length:" << l.GetLength() << endl;

}




int main() {
	StaticListTest();
	return 0;
}