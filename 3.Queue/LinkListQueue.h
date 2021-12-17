#pragma once
#include<stdio.h>
#include<iostream>


template<class ElemType>
struct DataInfo {
	ElemType _data;
	DataInfo* _next;
};

template<class ElemType>
class LinkListQueue {
	typedef DataInfo<ElemType>* Node;
public:
	void CreateQueue() {
		_head = (Node)malloc(sizeof(DataInfo<ElemType>));	//创建头节点,_head和_rear指向头节点。
		if (_head) {
			_head->_data = 0;
			_head->_next = nullptr;
			_rear = _head;
		}
	}

	~LinkListQueue()
	{
		if (_head) {
			Node cur = _head;
			Node tmp = nullptr;
			while (cur!=_rear) {
				tmp = cur->_next;
				free(cur);
				cur = tmp;
			}
			if (cur == _rear) {	//只有头元素
				free(cur);
				cur = nullptr;
				_rear = nullptr;
				return;
			}
			free(cur);
			cur = nullptr;
			if (_rear) {
				free(_rear);
				_rear = nullptr;
			}
		}
	}

	bool EnQueue(ElemType elem) {
		if (_head) {
			Node cur = _head;
			while (cur != _rear) {
				cur = cur->_next;
			}
			Node tmp = (Node)malloc(sizeof(DataInfo<ElemType>));
			if (tmp) {
				cur->_next = tmp;
				tmp->_data = elem;
				tmp->_next = nullptr;
				_rear = tmp;
				_rear->_next = nullptr;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}


	bool DeQueue(ElemType& elemOut) {
		if (_head == _rear)return false;	//队空
		Node cur = _head->_next;
		elemOut = cur->_data;
		_head->_next = cur->_next;
		if (cur == _rear) {	//最后一个节点出队
			_rear = _head;
		}
		free(cur);
		cur = nullptr;
		return true;
	}

	bool IsEmpty()const {
		return _head ==_rear;
	}

	ElemType Top()const {
		if(!IsEmpty()&&_head)
			return _head->_next->_data;
	}

	void PrintQueue()const {
		if (!_head || IsEmpty()) return;
		Node cur = _head->_next;
		while (cur != _rear) {
			std::cout << "data:" << cur->_data << "\n";
			cur = cur->_next;
		}
		std::cout << "data:" << cur->_data << "\n";
	}

private:
	Node _head;
	Node _rear;
};