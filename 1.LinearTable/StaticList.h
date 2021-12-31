#pragma once
#include<iostream>

/*
	静态链表，用数组实现的单链表
	cur 游标	  指向下一个元素对应的数组下标
	data 数据域

	- 备用链表 用来存放未使用的数组元素
	- 数组的第一个元素 cur存放备用链表的第一个节点的下标
	- 数组的最后一个元素	cur存放第一个有数值的下标元素(单链表中的头节点)
*/
const int STATIC_LIST_MAX_SIZE = 10;
const int ERROR_ELEM = 99999;

template<class ParamType>
struct LinkData {
	ParamType _data;
	size_t _cur;	//游标
	bool _valid:1;	//区分备用节点和有值节点
};

template<class ParamType>
class StaticList {
public:
	void InitList() {
		for (size_t i = 0; i < STATIC_LIST_MAX_SIZE; ++i) {
			_dataArray[i]._cur = i + 1;
			_dataArray[i]._data = 0;
			_dataArray[i]._valid = false;
		}
		_dataArray[STATIC_LIST_MAX_SIZE - 1]._cur = 0;
	}
protected:
	size_t MallocList() {
		size_t arrayIndex = _dataArray[0]._cur;	//获取空闲index
		if (arrayIndex) {
			_dataArray[0]._cur = _dataArray[arrayIndex]._cur;	//将头节点的cur等于空闲节点的cur，即指向下一块空闲区域
		}
		return arrayIndex;
	}

	// 将下标为index的空闲数据回收到备用链表
	void FreeAtIndex(size_t index) {
		_dataArray[index]._cur = _dataArray[0]._cur;	//指向下一个空闲节点
		_dataArray[index]._valid = false;
		_dataArray[0]._cur = index;
	}
public:
	bool InsertFront(size_t index, ParamType elem) {
		if (index<1 || index>STATIC_LIST_MAX_SIZE)return false;
		size_t freeIndex = MallocList();
		size_t frontIndex = STATIC_LIST_MAX_SIZE - 1;
		if (freeIndex) {
			_dataArray[freeIndex]._data = elem;
			for (size_t i = 1; i < index; ++i) {	//找到插入位置的前一个元素的下标
				frontIndex = _dataArray[frontIndex]._cur;
			}
			_dataArray[freeIndex]._cur = _dataArray[frontIndex]._cur;	//新插入的元素cur指向前一个元素指向的next节点
			_dataArray[freeIndex]._valid = true;
			_dataArray[frontIndex]._cur = freeIndex;
		}
		return true;
	}

	bool InsertBack(size_t index, ParamType elem) {
		if (index<1 || index>STATIC_LIST_MAX_SIZE)return false;
		size_t freeIndex = MallocList();
		size_t frontIndex = STATIC_LIST_MAX_SIZE - 1;
		if (freeIndex) {
			_dataArray[freeIndex]._data = elem;
			for (size_t i = 1; i <= frontIndex; ++i) {
				frontIndex = _dataArray[frontIndex]._cur; //找到插入位置的下标
			}
			_dataArray[freeIndex]._cur = _dataArray[frontIndex]._cur;
			_dataArray[freeIndex]._valid = true;
			_dataArray[frontIndex]._cur = freeIndex;
			return true;
		}
	}


	ParamType GetElemAtIndex(size_t index) {
		if (index<1 || index>STATIC_LIST_MAX_SIZE)return ERROR_ELEM;
		size_t elemIndex = _dataArray[STATIC_LIST_MAX_SIZE-1]._cur;
		for (size_t i = 1; i < index; ++i) {
			elemIndex = _dataArray[elemIndex]._cur;
		}
		return _dataArray[elemIndex]._data;
	}

	size_t FindElem(ParamType elem) {
		size_t elemIndex = 1;
		size_t Index = _dataArray[STATIC_LIST_MAX_SIZE - 1]._cur;
		while (Index && _dataArray[Index]._valid==true) {
			if (_dataArray[Index]._data == elem) {
				return elemIndex;
			}
			Index = _dataArray[Index]._cur;
			elemIndex++;
		}
		return ERROR_INDEX;
	}

	bool ModifyElemAtIndex(size_t index,ParamType newValue) {
		if (index<1 || index>STATIC_LIST_MAX_SIZE)return false;
		size_t elemIndex = _dataArray[STATIC_LIST_MAX_SIZE - 1]._cur;
		for (size_t i = 1; i < index; ++i) {
			elemIndex = _dataArray[elemIndex]._cur;
		}
		_dataArray[elemIndex]._data = newValue;
		return true;
	}

	bool DeleteElemAtIndex(size_t index) {
		if (index<1 || index>STATIC_LIST_MAX_SIZE)return false;
		size_t frontIndex = STATIC_LIST_MAX_SIZE - 1;
		for (size_t i = 1; i < index; ++i) {
			frontIndex = _dataArray[frontIndex]._cur;					//获取删除节点的前一个节点
		}
		size_t deleteElemIndex = _dataArray[frontIndex]._cur;			//获取删除节点的index
		_dataArray[frontIndex]._cur = _dataArray[deleteElemIndex]._cur;	//前一个节点指向被删除节点指向的next节点
		FreeAtIndex(deleteElemIndex);
		return true;
	}

	void DisplayStaticList()const {
		size_t beginIndex = _dataArray[STATIC_LIST_MAX_SIZE - 1]._cur;
		//&& _dataArray[beginIndex]._valid == true
		while (beginIndex!= STATIC_LIST_MAX_SIZE-1) {
			std::cout << "Index:" << beginIndex << " Elem:" << _dataArray[beginIndex]._data << "\n";
			beginIndex = _dataArray[beginIndex]._cur;
		}
	}

	size_t GetLength()const {
		size_t length = 0;
		size_t beginIndex = _dataArray[STATIC_LIST_MAX_SIZE - 1]._cur;
		while (beginIndex != STATIC_LIST_MAX_SIZE - 1 && _dataArray[beginIndex]._valid == true) {
			beginIndex = _dataArray[beginIndex]._cur;
			++length;
		}
		return length;
	}
private:
	LinkData<ParamType> _dataArray[STATIC_LIST_MAX_SIZE];
};