#pragma once
#include<iostream>
#include<assert.h>
/*
	�ѵ�˳��洢
	���ӵ��±�:  i*2+1;	   iΪ���ڵ���±�
	�Һ��ӵ��±�:  i*2+2;	   iΪ���ڵ���±�
	���ڵ���±�:  i-1/2;	   iΪ��ǰ�ڵ��±�
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
		if (_length >= _maxSize)return;	//����
		_length++;
		_array[_length - 1] = elem;
		_SiftUp(_length - 1);
	}

	ElemType GetTop()const {
		return _array[0];
	}

	void Pop() {
		if (_length <= 0 || !_array)return;	//�ն�
		_array[0] = _array[_length - 1];	//����Ԫ�ص������һ��Ԫ��
		_length - 1;	//���һ��Ԫ�س���
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
		//��ǰ�ڵ�������±��ڷ�Χ�� �Ž���ѭ��
		while (_GetLeftChildIndex(index) < _length) {	
			size_t lChildIndex = _GetLeftChildIndex(index);
			size_t swapIndex = lChildIndex;	//Ĭ�ϱȽϵ��±�������
			// �Һ��Ӵ��ڵ������,ȡ�������ӵ����ֵ�븸�ڵ���бȽ�
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
		assert(index >= 1);	//index<1�ж�
		return (index - 1) / 2;
	}

	size_t _GetLeftChildIndex(size_t index) {
		assert(index >= 0);	//index<0�ж�
		return index*2+1;
	}

	size_t _GetRightChildIndex(size_t index) {
		assert(index >= 0);	//index<0�ж�
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
	CmpFunctorType _cmpFunctor;	//�ȽϺ�����ָ��
	size_t _length;
};