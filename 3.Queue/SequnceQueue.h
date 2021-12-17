#pragma once
#include<stdio.h>
#include<iostream>

/*
	循环队列线性存储
*/
const size_t MAX_QUEUE_SIZE = 6;


template<class ElemType>
class SequnceQueue {
public:
	void CreateQueue() {
		_quePtr = (ElemType*)calloc(MAX_QUEUE_SIZE,sizeof(ElemType));
		if (_quePtr) {
			_head = 0;
			_rear = 0;
		}
	}

	bool EnQueue(ElemType elem) {
		if (_quePtr) {
			if ((_rear + 1) % MAX_QUEUE_SIZE == _head)return false;//队满
			_quePtr[_rear] = elem;
			_rear = (_rear + 1) % MAX_QUEUE_SIZE;
			return true;
		}
		else {
			return false;
		}
	}
	

	bool DeQueue(ElemType& elemPop) {
		if (_head == _rear)return false;	//队空
		elemPop = _quePtr[_head];
		_head = (_head + 1) % MAX_QUEUE_SIZE;
		return true;
	}

	ElemType Top()const {
		return _quePtr[_head];
	}


	void PrintQueue()const {
		if (_quePtr) {
			size_t index = _head;
			while ((index + 1) % MAX_QUEUE_SIZE != _rear) {
				std::cout << "data:" << _quePtr[index] << "\n";
				index = (index + 1) % MAX_QUEUE_SIZE;
			}
			std::cout << "data:" << _quePtr[index] << "\n";
		}
	}

	~SequnceQueue()
	{
		if (_quePtr) {
			free(_quePtr);
			_quePtr = nullptr;
		}
	}



private:
	ElemType* _quePtr;	
	size_t _head;	//指向头部
	size_t _rear;	//指向当前元素的下一个位置 缺点是会少一个位置
};