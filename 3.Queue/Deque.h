#pragma once 
#include<stdio.h>
#include<iostream>

/*
	˫�˶�����ʽ�洢
*/

template<class ElemType>
struct DequeDataInfo {
	ElemType _data;
	DequeDataInfo* _next;
};

template<class ElemType>
class Deque {
	typedef DequeDataInfo<ElemType>* Node;
public:
	void CreateDeque() {
		//��ͷ���ʽ����
		_head = nullptr;
		_rear = _head;
		_length = 0;
	}

	void EnQueueRear(ElemType elem) {
		Node tmp = (Node)malloc(sizeof(DequeDataInfo<ElemType>));
		if (tmp) {
			tmp->_data = elem;
			tmp->_next = nullptr;
			_length++;
			if (IsEmpty()) {	//�ӿ�
				_head = tmp;
				_rear = tmp;
				return;
			}
			_rear->_next = tmp;
			_rear = tmp;
		}
	}

	void EnQueueFront(ElemType elem) {
		Node tmp = (Node)malloc(sizeof(DequeDataInfo<ElemType>));
		if (tmp) {
			tmp->_data = elem;
			_length++;
			if (IsEmpty()) {
				tmp->_next = nullptr;
				_head = tmp;
				_rear = tmp;
				return;
			}
			tmp->_next = _head;
			_head = tmp;
		}
	}


	bool DeQueueRear(ElemType& elemOut) {
		if (IsEmpty())return false;
		Node cur = _rear;
		elemOut = cur->_data;
		if (cur == _head) {	//���ӵ������һ��Ԫ��
			_head = nullptr;
			_rear = nullptr;
			_length = 0;
			free(cur);
			return true;
		}
		cur = _head;
		while (cur->_next != _rear)cur = cur->_next;	//������һ��Ԫ�ص�ǰһ���ڵ�
		cur->_next = nullptr;
		free(_rear);
		_rear = cur;
		--_length;
		return true;
	}


	bool DeQueueFront(ElemType& elemOut) {
		if (IsEmpty())return false;
		Node cur = _head;
		elemOut = cur->_data;
		if (cur == _rear) {	//���ӵ������һ��Ԫ��
			_head = nullptr;
			_rear = nullptr;
			_length = 0;
			free(cur);
			return true;
		}
		_head = cur->_next;
		free(cur);
		--_length;
		return true;
	}


	void PrintDeque()const {
		if (IsEmpty())return;
		Node cur = _head;
		while (cur) {
			std::cout << cur->_data << " ";
			cur = cur->_next;
		}
		std::cout << "\n";
	}



	size_t GetLength()const {
		return _length;
	}

	bool IsEmpty()const {
		return _head == nullptr;
	}

private:
	Node _head;		//ָ���һ��Ԫ��
	Node _rear;		//ָ��βԪ��
	size_t _length;
};