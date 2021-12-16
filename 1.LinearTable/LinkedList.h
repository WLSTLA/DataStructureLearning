#pragma once
#include<iostream>
using namespace std;


/*
	单向链表带头
*/

template<class ElemType>
class LinkedList {
	typedef LinkedList* Node;
public:
	void CreateLinkedList(size_t n, ElemType elem) {
		Node head,cur;
		size_t index;
		head = new LinkedList();
		head->_Next = nullptr;
		cur = head;
		for (size_t i = 0; i < n; ++i) {
			while (cur->_Next != nullptr) { //找到最后一个节点
				cur = cur->_Next;
			}
			Node tmp = (Node)malloc(sizeof(LinkedList));
			if (tmp != nullptr) {
				tmp->_Elem = elem;
				cur->_Next = tmp;
				tmp->_Next = nullptr;
			}
		}
		_Length = n;
		_Head = head;
	}

	//尾插法
	void PushBack(ElemType elem) { 
		if (!_Head)return;
		Node cur = _Head;
		while (cur->_Next != nullptr) { //找到最后一个节点
			cur = cur->_Next;
		}
		Node tmp = (Node)malloc(sizeof(LinkedList));
		if (tmp != nullptr) {
			tmp->_Elem = elem;
			cur->_Next = tmp;
			_Length++;
			tmp->_Next = nullptr;
		}
	}

	//头插法
	void PushFront(ElemType elem) {
		if (!_Head)return;
		Node tmp = (Node)malloc(sizeof(LinkedList));
		tmp->_Elem = elem;
		tmp->_Next = _Head->_Next;
		_Head->_Next = tmp;
		_Length++;
	}


	void DisplayLinkedList()const {
		Node pre, cur;
		pre = _Head;
		cur = pre->_Next;
		while (pre->_Next != nullptr) {
			cout << cur->_Elem << " ";
			pre = cur;
			cur = pre->_Next;
		}
		cout << endl;
	}


	Node FindElem(ElemType elem) {
		if (!_Head)return nullptr;
		Node tmp = _Head;
		while (tmp) {
			if (tmp->_Elem == elem) {
				return tmp;
			}
			tmp = tmp->_Next;
		}
		return nullptr;
	}


	bool InsertAfter(Node pos, ElemType elem) {
		if (!_Head)return false;
		Node cur = _Head;
		while (cur) {
			if (cur == pos) {
				Node tmp = (Node)malloc(sizeof(LinkedList));
				if (tmp != nullptr) {
					tmp->_Next = cur->_Next;
					cur->_Next = tmp;
					tmp->_Elem = elem;
					_Length++;
					return true;
				}
			}
			cur = cur->_Next;
		}
		return false;
	}

	bool InsertFront(Node pos, ElemType elem) {
		if (!_Head||!pos)return false;
		Node cur = _Head;
		for (; cur->_Next != pos; cur = cur->_Next); //移动到cur->Next=pos处
		Node tmp = (Node)malloc(sizeof(LinkedList));
		if (tmp != nullptr) {
			tmp->_Next = cur->_Next;
			cur->_Next = tmp;
			tmp->_Elem = elem;
			_Length++;
		}
		return true;
	}

	bool EraseElem(Node pos) {
		if (!_Head || !pos)return false;
		Node cur = _Head;
		for (; cur->_Next != pos; cur = cur->_Next);
		cur->_Next = pos->_Next;
		free(pos);
		_Length--;
		return true;
	}

	ElemType GetElem()const {
		return _Elem;
	}

	bool IsEmpty()const {
		return _Head->_Next ? true : false;
	}

	size_t GetSize()const {
		return _Length;
	}

	~LinkedList()
	{
		Node pre,cur;
		pre = _Head;
		if (pre) {
			while (pre->_Next) {
				cur = pre->_Next;
				free(pre);
				pre = cur;
			}
			free(pre);
		}
	}
private:
	ElemType _Elem;
	Node _Head;
	Node _Next;
	size_t _Length;
};
