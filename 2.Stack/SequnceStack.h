#pragma once
#include<stdio.h>
#include<iostream>
const size_t SIZE = 5;

template<class ElemType>
class SequnceStack {
public:
	void CreateStack() {
		_stackArrayPtr = (ElemType*)malloc(sizeof(ElemType)*SIZE);
		if (_stackArrayPtr) {
			_top = 0;
			_capacity = SIZE;
			printf("当前容量为:%u \n", _capacity);
			for (size_t i = 0; i < SIZE; ++i) {
				_stackArrayPtr[i] = 0;
			}
		}
	}

	~SequnceStack()
	{
		DestroyStack();
	}


	void Push(ElemType elem) {
		if (_capacity == _top) {
			// 容量满了 需要扩容
			_capacity *= 2;
			printf("进行扩容,当前容量%u \n", _capacity);
			_stackArrayPtr = (ElemType*)realloc(_stackArrayPtr, sizeof(ElemType)*_capacity);
		}
		if (_stackArrayPtr) {
			_stackArrayPtr[_top] = elem;
			_top++;
		}
	}


	void Pop() {
		--_top;
	}

	void DestroyStack() {
		if (_stackArrayPtr) {
			free(_stackArrayPtr);
			_top = 0;
		}
	}

	size_t Size() {
		return _top;
	}

	void PrintStack()const {
		for (size_t i = 0; i < _top; ++i) {
			std::cout << _stackArrayPtr[i] << " ";
		}
		std::cout << std::endl;
	}


	size_t GetCapacity()const {
		return _capacity;
	}

	ElemType Top() {
		return _stackArrayPtr[_top - 1];
	}

private:
	ElemType* _stackArrayPtr;
	size_t _top;
	size_t _capacity;
};