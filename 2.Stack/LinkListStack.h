#pragma once
#include<stdio.h>
#include<iostream>

template<class ElemType>
struct DataInfo {
	DataInfo* _next;
	ElemType _data;
};


template<class ElemType>
class LinkListStack {
	typedef DataInfo<ElemType>* Node;
public:
	void CreateStack() {
		_head = (Node)malloc(sizeof(DataInfo<ElemType>));
		if (_head) {
			_head->_data = 0;
			_head->_next = nullptr;
		}
	}

	~LinkListStack()
	{
		DestroyStack();
	}

	void Push(ElemType elem) {
		if (_head) {
			Node cur = _head;
			while (cur->_next != nullptr) {
				cur = cur->_next;
			}
			Node tmp = (Node)malloc(sizeof(DataInfo<ElemType>));
			if (tmp) {
				tmp->_data = elem;
				cur->_next = tmp;
				tmp->_next = nullptr;
			}
		}
	}


	void Pop() {
		if (_head&&_head->_next) {
			Node cur = _head->_next;
			size_t length = Size();
			for (size_t i = 1; i < length-1; ++i) {
				cur = cur->_next;	//找到最后一个元素的前一个元素
			}
			if (cur == _head->_next) {	//释放的是第一个节点
				free(cur);
				_head->_next = nullptr;
				return;
			}
			Node tmp = cur->_next;
			cur->_next = nullptr;
			free(tmp);
		}
	}


	size_t Size()const {
		size_t length = 0;
		if (_head) {
			Node cur = _head;
			while (cur->_next!=nullptr)
			{
				cur = cur->_next;
				length++;
			}
		}
		return length;
	}


	void PrintStack()const {
		if (_head) {
			Node cur = _head->_next;
			while (cur) {
				std::cout << "data:" << cur->_data << std::endl;
				cur = cur->_next;
			}
		}
	}

	void DestroyStack() {
		if (_head) {
			Node cur = _head;
			Node tmp = nullptr;
			while (cur->_next != nullptr) {
				tmp = cur->_next;
				free(cur);
				cur = tmp;
			}
			free(cur);
		}
	}

private:
	Node _head;
};