#pragma once
#include<stdio.h>
#include<iostream>


const int MAX_DOUBLECIRCULAR_NUMBER = 10;
const int INVALID_ELEM = 99999;

template<class ElemType>
struct ListDataInfo {
	ListDataInfo* _prior;
	ListDataInfo* _next;
	ElemType _data;
};


template<class ElemType>
class DoubleCircularList {
	typedef ListDataInfo<ElemType>* Node;
public:
	bool CreateList(const size_t n) {
		_head = (Node)malloc(sizeof(ListDataInfo<ElemType>));
		if (_head != nullptr) {
			_head->_data = 0;
			_head->_next = _head;
			_head->_prior = _head;
			Node cur = _head;
			Node tmp = nullptr;
			for (size_t i = 0; i < n; ++i) {
				while (cur->_next != _head) {
					cur = cur->_next;	//找到尾节点
				}
				tmp = (Node)malloc(sizeof(ListDataInfo<ElemType>));
				if (tmp) {
					tmp->_prior = cur;
					tmp->_next = _head;
					cur->_next = tmp;
					tmp->_data = rand() % MAX_DOUBLECIRCULAR_NUMBER + 1;
				}
				else {
					return false;
				}
			}
			_head->_prior = tmp;
			cur = _head->_next;
			cur->_prior = tmp;
			tmp->_next = cur;
			free(_head);	//删除原来的头节点，现在的头节点是cur
			_head = cur;
			_rear = tmp;	//尾节点
			return true;
		}
		return false;
	}



	~DoubleCircularList()
	{
		if (_head) {
			Node cur = _head;
			Node tmp = nullptr;
			while (cur->_next != _head) {
				tmp = cur->_next;
				free(cur);
				cur = tmp;
			}
			free(cur);
		}
	}

	//头插法
	bool InsertElemFront(const size_t index, ElemType elem) {
		size_t length = GetLength();
		if (index<1 || index>length)return false;
		Node cur = _head;
		for (size_t i = 1; i < index; ++i) {
			cur = cur->_next;
		}
		Node tmp = (Node)malloc(sizeof(ListDataInfo<ElemType>));
		if (tmp != nullptr) {
			tmp->_prior = cur->_prior;
			tmp->_next = cur;
			cur->_prior->_next = tmp;
			cur->_prior = tmp;
			tmp->_data = elem;
			if (index == 1) {	//插入位置为第一位 头节点重新赋值为tmp
				_head = tmp;
			}
		}
		else {
			return false;
		}
		return true;
	}

	//尾插法
	bool InsertElemRear(const size_t index, ElemType elem) {
		size_t length = GetLength();
		if (index<1 || index>length)return false;
		Node cur = _head;
		for (int i = 1; i < index; ++i) {
			cur = cur->_next;
		}
		Node tmp = (Node)malloc(sizeof(ListDataInfo<ElemType>));
		if (tmp != nullptr) {
			tmp->_prior = cur;
			tmp->_next = cur->_next;
			cur->_next->_prior = tmp;
			cur->_next = tmp;
			tmp->_data = elem;
			if (index == length) {	//如果插入位置为最后一位，尾节点重新赋值为tmp
				_rear = tmp;
			}
		}
		else {
			return false;
		}
		return true;
	}


	bool ModifyElemAtIndex(const size_t index, ElemType newValue) {
		size_t length = GetLength();
		if (index<1 || index>length)return false;
		Node cur = _head;
		for (int i = 1; i < index; ++i) {
			cur = cur->_next;
		}
		cur->_data = newValue;
		return true;
	}


	size_t FindElem(const ElemType elem) const{
		Node cur = _head;
		size_t index = 1;
		while (cur->_next != _head) {
			if (cur->_data == elem) {
				return index;
			}
			cur = cur->_next;
			index++;
		}
		if (cur->_data == elem) {	//最后一位相等
			return index;
		}
		return ERROR_INDEX;
	}

	ElemType GetElem(const size_t index) const {
		size_t length = GetLength();
		if (index<1 || index>length)return INVALID_ELEM;
		Node cur = _head;
		for (size_t i = 1; i < index; ++i) {
			cur = cur->_next;
		}
		return cur->_data;
	}

	bool DeleteElemAtIndex(const size_t index) {
		size_t length = GetLength();
		if (index<1 || index>length)return false;
		Node cur = _head;
		for (size_t i = 1; i < index; ++i) {
			cur = cur->_next;
		}
		cur->_prior->_next = cur->_next;
		cur->_next->_prior = cur->_prior;
		if (index == 1) {
			_head = cur->_next;
		}
		else if (index == length) {
			_rear = cur->_prior;
		}
		free(cur);
		return true;
	}

	void printListForward()const {
		if (_head) {
			Node cur = _head;
			while (cur->_next != _head) {
				printf("data:%d\n",cur->_data);
				cur = cur->_next;
			}
			printf("data:%d\n", cur->_data);
			std::cout << "\n";
		}
	}


	void printListReverse()const{
		if (_rear) {
			Node cur = _rear;
			while (cur->_prior != _rear) {
				printf("data:%d\n", cur->_data);
				cur = cur->_prior;
			}
			printf("data:%d\n", cur->_data);
			std::cout << "\n";
		}
	}

	size_t GetLength()const {
		size_t length = 0;
		if (_head) {
			Node cur = _head;
			length++;
			while (cur->_next != _head) {
				cur = cur->_next;
				length++;
			}
		}
		return length;
	}

private:
	Node _head;
	Node _rear;
};
