#pragma once
#include<stdlib.h>

const int MAX_NUM = 100;

template<class ElemType>
class CycleList {
	typedef CycleList* Node;
public:
	CycleList(size_t n) {
		_head = (Node)malloc(sizeof(CycleList));
		if (_head) {
			_head->_next = _head;
			_head->_data = 0;
			Node tmp = nullptr;
			Node cur = _head;
			for (size_t i = 0; i < n; ++i) {
				while (cur->_next != _head) {
					cur = cur->_next;	//ÕÒµ½Î²½Úµã
				}
				tmp = (Node)malloc(sizeof(CycleList));
				if (tmp) {
					tmp->_next = _head;
					cur->_next = tmp;
					tmp->_data = rand() % MAX_NUM + 1;
				}
			}
			cur = _head->_next;
			tmp->_next = cur;
			free(_head);
			_head = cur;
			_length = n;
		}
		return;
	}

	~CycleList()
	{
		if (_head) {
			Node tmp,cur = _head;
			while (cur->_next != _head) {
				tmp = cur->_next;
				free(cur);
				cur = tmp;
			}
			free(cur);
		}
	}

	void printfList()const {
		if (_head) {
			Node cur = _head;
			while (cur->_next != _head) {
				cout << "data:" << cur->_data << endl;
				cur = cur->_next;
			}
		}
	}

private:
	Node _head;
	Node _next;
	ElemType _data;
	size_t _length;
};