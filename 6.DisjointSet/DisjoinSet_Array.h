#pragma once 
#include<iostream>

/*
 	���鼯
	ʹ��·��ѹ�� �Ż�find���� ���Ż��ϲ�Ч��
	ʹ��������Ϊ�洢�ṹ
*/

const size_t MAX_UNIONSET_NUM = 20;	//���ϵĸ���

class UnionSetArray {
public:
	void InitUnionSetArray() {
		_set = new int[MAX_UNIONSET_NUM+1]();
		// ��ʼ�� ÿ�����ϵĸ��ڵ���Ϊ�����Լ�
		for (size_t i = 1; i <= MAX_UNIONSET_NUM; ++i) {
			_set[i] = i;	
		}
	}

	void UnionElement(int joinEelem, int jointoElem) {
		int child= FindParent(joinEelem);
		int parent = FindParent(jointoElem);
		_set[child] = parent;
	}

	// �ж�����Ԫ���Ƿ������ͬһ������
	bool IsConnected(int elem1, int elem2) {
		return FindParent(elem1) == FindParent(elem2);
	}


	int FindParent(int elem) {
		if (_set[elem] == elem) {
			return elem;
		}
		else {
			_set[elem] = FindParent(_set[elem]);	//�Ż�·��
			return _set[elem];
		}
	}

	~UnionSetArray()
	{
		if (!_set)return;
		delete []_set;
		_set = nullptr;
	}
private:
	int* _set;
};