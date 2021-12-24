#pragma once
#include<iostream>
#include<assert.h>
/*
	堆的顺序存储
	左孩子的下标:  i*2+1;	   i为父节点的下标
	右孩子的下标:  i*2+2;	   i为父节点的下标
	父节点的下标:  i-1/2;	   i为当前节点下标
*/


template<class ElemType>
class SqHeap {
	typedef bool (*CmpFunctorType)(const ElemType* val1, const ElemType* val2);
public:
	SqHeap() :_maxSize(0), _array(nullptr), _cmpFunctor(nullptr) {};

	SqHeap(size_t size, CmpFunctorType functor) {
		_maxSize = size;
		_array = new ElemType[_maxSize]();
		_cmpFunctor = functor;
		_length = 0;
	}

	~SqHeap()
	{
		if (!_array)return;
		delete[] _array;
		_array = nullptr;
		_cmpFunctor = nullptr;
	}

	void InsertElem(ElemType elem) {
		if (_length >= _maxSize)return;	//已满
		_length++;
		_array[_length - 1] = elem;
		_SiftUp(_length - 1);
	}

	ElemType GetTop()const {
		return _array[0];
	}

	void Pop() {
		if (_length <= 0 || !_array)return;	//空堆
		_array[0] = _array[_length - 1];	//堆首元素等于最后一个元素
		_length - 1;	//最后一个元素出堆
		_SiftDown(0);
	}

	void printHeap()const {
		for (size_t i = 0; i < _length; ++i) {
			std::cout << _array[i] << " ";
		}
		std::cout << "\n";
	}

protected:
	bool _CompareValue(const ElemType* val1, const ElemType* val2) {
		if (!_cmpFunctor)return false;
		return _cmpFunctor(val1, val2);
	}

	void _SiftDown(size_t index) {
		//当前节点的左孩子下标在范围内 才进行循环
		while (_GetLeftChildIndex(index) < _length) {	
			size_t lChildIndex = _GetLeftChildIndex(index);
			size_t swapIndex = lChildIndex;	//默认比较的下标是左孩子
			// 右孩子存在的情况下,取两个孩子的最大值与父节点进行比较
			if (_GetRightChildIndex(index) < _length) {
				if (_array[lChildIndex] < _array[_GetRightChildIndex(index)])
					swapIndex = _GetRightChildIndex(index);
			}
			ElemType* curElemPtr = &_array[index];
			ElemType* cmpElemPtr = &_array[swapIndex];
			if (_cmpFunctor(cmpElemPtr, curElemPtr)) {
				_SwapElem(index,swapIndex);
				index = swapIndex;
			}
			else {
				break;
			}
		}
	}

	void _SiftUp(size_t index) {
		while (index>0)
		{
			size_t parentIndex = _GetParentIndex(index);
			ElemType* curElemPtr = &_array[index];
			ElemType* parentElemPtr = &_array[parentIndex];
			if (_cmpFunctor(curElemPtr, parentElemPtr)) {
				_SwapElem(index,parentIndex);
				index = parentIndex;
			}
			else {
				break;
			}
		}
	}

	size_t _GetParentIndex(size_t index) {
		assert(index >= 1);	//index<1中断
		return (index - 1) / 2;
	}

	size_t _GetLeftChildIndex(size_t index) {
		assert(index >= 0);	//index<0中断
		return index*2+1;
	}

	size_t _GetRightChildIndex(size_t index) {
		assert(index >= 0);	//index<0中断
		return index * 2 + 2;
	}

	void _SwapElem(size_t index1, size_t index2) {
		ElemType tmp = _array[index1];
		_array[index1] = _array[index2];
		_array[index2] = tmp;
	}

private:
	size_t _maxSize;
	ElemType* _array;
	CmpFunctorType _cmpFunctor;	//比较函数的指针
	size_t _length;
};