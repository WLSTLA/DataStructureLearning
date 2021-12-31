#pragma once
#include<iostream>

/*
	��̬����������ʵ�ֵĵ�����
	cur �α�	  ָ����һ��Ԫ�ض�Ӧ�������±�
	data ������

	- �������� �������δʹ�õ�����Ԫ��
	- ����ĵ�һ��Ԫ�� cur��ű�������ĵ�һ���ڵ���±�
	- ��������һ��Ԫ��	cur��ŵ�һ������ֵ���±�Ԫ��(�������е�ͷ�ڵ�)
*/
const int STATIC_LIST_MAX_SIZE = 10;
const int ERROR_ELEM = 99999;

template<class ParamType>
struct LinkData {
	ParamType _data;
	size_t _cur;	//�α�
	bool _valid:1;	//���ֱ��ýڵ����ֵ�ڵ�
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
		size_t arrayIndex = _dataArray[0]._cur;	//��ȡ����index
		if (arrayIndex) {
			_dataArray[0]._cur = _dataArray[arrayIndex]._cur;	//��ͷ�ڵ��cur���ڿ��нڵ��cur����ָ����һ���������
		}
		return arrayIndex;
	}

	// ���±�Ϊindex�Ŀ������ݻ��յ���������
	void FreeAtIndex(size_t index) {
		_dataArray[index]._cur = _dataArray[0]._cur;	//ָ����һ�����нڵ�
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
			for (size_t i = 1; i < index; ++i) {	//�ҵ�����λ�õ�ǰһ��Ԫ�ص��±�
				frontIndex = _dataArray[frontIndex]._cur;
			}
			_dataArray[freeIndex]._cur = _dataArray[frontIndex]._cur;	//�²����Ԫ��curָ��ǰһ��Ԫ��ָ���next�ڵ�
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
				frontIndex = _dataArray[frontIndex]._cur; //�ҵ�����λ�õ��±�
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
			frontIndex = _dataArray[frontIndex]._cur;					//��ȡɾ���ڵ��ǰһ���ڵ�
		}
		size_t deleteElemIndex = _dataArray[frontIndex]._cur;			//��ȡɾ���ڵ��index
		_dataArray[frontIndex]._cur = _dataArray[deleteElemIndex]._cur;	//ǰһ���ڵ�ָ��ɾ���ڵ�ָ���next�ڵ�
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