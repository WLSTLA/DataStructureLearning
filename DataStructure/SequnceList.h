#pragma once
#include<string.h>
#include<iostream>
const size_t SEQUNCE_LIST_MAX_SIZE = 100;
const size_t ERROR_INDEX = 101;
using namespace std;

template<class ElemType>
class SequnceList {
public:
	SequnceList() {
		_Data = (ElemType*)malloc(sizeof(ElemType) * SEQUNCE_LIST_MAX_SIZE);
		_lastData = nullptr;
		_length = 0;
	}
	~SequnceList()
	{
		if (_lastData) {
			_lastData = nullptr;
		}
		free(_Data);
		_length = 0;
	}

	SequnceList(int size, ElemType elem) {
		//_Data = new ElemType[MAX_SIZE];
		_Data = (ElemType*)malloc(sizeof(ElemType)* SEQUNCE_LIST_MAX_SIZE);
		if (!_Data)return;
		for (size_t i = 0; i < size; ++i) {
			_Data[i] = elem;
		}
		_length = size;
		_lastData = &_Data[_length - 1];
	}

	void InsertElem(size_t position, const ElemType& elem) {
		if (position > GetLength()) { //插在最后一位
			_Data[GetLength()] = elem;
		}
		else {
			for (size_t i = _length; i >= position; --i) { //将元素循环向前移动
				_Data[i] = _Data[i - 1];
			}
			_Data[position - 1] = elem;
		}
		++_length;
		_lastData = &_Data[_length - 1];
	}

	void DeleteElem(size_t index) {
		if (index > GetLength()) {	//index超出范围 删除最后一位
			--_length;
		}
		else {
			for (size_t i = index; i < GetLength(); ++i) { //循环向后移动
				_Data[i-1] = _Data[i];
			}
			--_length;
		}
		_lastData = &_Data[_length - 1];
	}

	size_t GetLength()const {
		return _length;
	}

	ElemType* GetLastData() {
		return _lastData;
	}

	void DisplayList()const {
		if (GetLength() == 0)return;
		for (size_t i = 0; i < GetLength(); ++i) {
			cout << _Data[i] << " ";
		}
		cout << endl;
	}

	size_t FindElem(ElemType elem)const {
		for (size_t i = 0; i < GetLength(); ++i) {
			if (_Data[i] == elem) {
				return i+1;
			}
		}
		return ERROR_INDEX;
	}

	bool ModifyElem(size_t index,ElemType elem) {
		if (IsElemValid(index)) {
			_Data[index - 1] = elem;
			return true;
		}
		else
			return false;
	}

protected:
	bool IsElemValid(size_t index)const {
		return index > GetLength() ? false : true;
	}
private:
	ElemType* _Data;
	ElemType* _lastData;
	size_t _length;
};