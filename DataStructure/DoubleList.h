#pragma once
#include<stdio.h>
#include<iostream>

template<class ElemType>
struct DataInfo {
	typedef DataInfo* Node;
	Node _priori;
	Node _next;
	ElemType _data;
};

const int ERROR_DOUBLELIST_INDEX = 99999;

template<class ElemType>
class DoubleList {
	typedef DataInfo<ElemType>* Node;
public:
	DoubleList(size_t n, ElemType elem) {
		_head = (Node)malloc(sizeof(DataInfo<ElemType>));
		if (_head) {
			_head->_data = 0;
			_head->_next = nullptr;
			_head->_priori = nullptr;
			Node cur = _head;
			for (size_t i = 0; i < n; ++i) {
				while (cur->_next != nullptr) {
					cur = cur->_next;
				}
				Node tmp = (Node)malloc(sizeof(DataInfo<ElemType>));
				if (tmp) {
					tmp->_data = rand() % 5 + 1;
					tmp->_next = nullptr;
					cur->_next = tmp;
					tmp->_priori = cur;
					_rear = tmp;
				}
			}
			_length = n;
		}
	}


	bool InsertAtIndexFront(const size_t index, ElemType elem){
		size_t length = GetLength();
		if (index<1 || index>length)return false;
		Node cur = _head->_next;
		for (size_t i = 1; i < index;++i) {
			cur = cur->_next;
		}
		Node tmp = (Node)malloc(sizeof(DataInfo<ElemType>));
		if (tmp&&cur) {
			tmp->_data = elem;
			tmp->_next = cur;
			tmp->_priori = cur->_priori;
			cur->_priori->_next = tmp;
			cur->_priori = tmp;
		}
		else {
			return false;
		}
		return true;
	}

	bool InsertAtIndexRear(const size_t index,ElemType elem){
		size_t length = GetLength();
		if (index<1 || index>length)return false;
		Node cur = _head->_next;
		for (size_t i = 1; i < index; ++i) {
			cur = cur->_next;
		}
		Node tmp = (Node)malloc(sizeof(DataInfo<ElemType>));
		if (tmp&&cur) {
			tmp->_data = elem;
			tmp->_priori = cur;
			if (cur->_next) {
				tmp->_next = cur->_next;
				cur->_next->_priori = tmp;
				cur->_next = tmp;
			}else{
				cur->_next = tmp;						//���������һ��Ԫ�صĺ���
				tmp->_next = nullptr;
				_rear = tmp;
			}
		}
		else {
			return false;
		}
		return true;
	}
	
	//ɾ��index�±��elem
	bool EraseElemAtIndex(const size_t index) {
		size_t length = GetLength();
		if (index<1 || index>length)return false;
		Node cur = _head->_next;
		for (size_t i = 1; i < index; ++i) {
			cur = cur->_next;
		}
		if (cur!=nullptr) {
			if (cur->_next) {
				cur->_priori->_next = cur->_next;
				cur->_next->_priori = cur->_priori;
			}
			else {	//ɾ�����һ��Ԫ��
				cur->_priori->_next = nullptr;
				_rear = cur->_priori;
			}
			free(cur);
		}
		else {
			return false;
		}
	}

	//ɾ�����к�elem��ȵ�Ԫ��
	bool EraseElememts(const ElemType elem) {
		Node cur = _head->_next;
		Node temp;
		while (cur) {
			temp = cur->_next;
			if (cur->_data == elem) {
				//��һ��Ԫ��
				if (cur->_priori == nullptr) {
					cur->_next->_priori = nullptr;
					free(cur);
				}
				//���һ��Ԫ��
				else if (cur->_next == nullptr) {
					cur->_priori->_next = nullptr;
					_rear = cur->_priori;
					free(cur);
				}
				//����Ԫ��
				else {
					cur->_priori->_next = cur->_next;
					cur->_next->_priori = cur->_priori;
					free(cur);
				}
			}
			cur = temp;
		}
		return true;
	}

	size_t FindElemInverse(const ElemType elem)const {
		Node cur = _head->_next;
		size_t index = 1;
		while (cur) {
			if (cur->_data == elem) {
				return index;
			}
			index++;
			cur = cur->_next;
		}
		return ERROR_DOUBLELIST_INDEX;
	}

	size_t FindElemReverse(const ElemType elem)const {
		Node cur = _rear;
		size_t index = 1;
		while (cur) {
			if (cur->_data == elem) {
				return index;
			}
			index++;
			cur = cur->_priori;
		}
		return ERROR_DOUBLELIST_INDEX;
	}

	void ForeachListForward()const {
		if (_head) {
			Node cur = _head->_next;
			while (cur) {
				std::cout << "data: " << cur->_data << std::endl;
				cur = cur->_next;
			}
		}
	}

	void ForeachListBackward()const {
		if (_rear) {
			Node cur = _rear;
			while (cur->_priori != nullptr) {
				std::cout << "data: " << cur->_data << std::endl;
				cur = cur->_priori;
			}
		}
	}


	// �޸���elem��ȵ�����Ԫ��Ϊ�µ�ֵ
	void ModifyElements(ElemType elem, ElemType newValue) {
		Node cur = _head->_next;
		while (cur) {
			if (cur->_data == elem) {
				cur->_data = newValue;
			}
			cur = cur->_next;
		}
	}

	bool ModifyElemAtIndex(size_t index, ElemType newValue) {
		size_t length = GetLength();
		if (index<1 || index>length)return false;
		Node cur = _head->_next;
		for (size_t i = 1; i < index; ++i) {
			cur = cur->_next;
		}
		if (cur) {
			cur->_data = newValue;
		}
		else {
			return false;
		}
		return true;
	}

	size_t GetLength()const {
		Node tmp = _head;
		size_t length = 0;
		while (tmp->_next != nullptr) {
			tmp = tmp->_next;
			length++;
		}
		return length;
	}

	~DoubleList()
	{
		if (_head) {
			Node cur = _head;
			Node tmp;
			while (cur->_next != nullptr) {
				tmp = cur->_next;
				free(cur);
				cur = tmp;
			}
			free(cur);
		}
	}

private:
	DataInfo<ElemType>* _head;
	DataInfo<ElemType>* _rear;
	size_t _length;
};