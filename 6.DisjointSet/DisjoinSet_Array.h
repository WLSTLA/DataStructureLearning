#pragma once 
#include<iostream>

/*
 	并查集
	使用路劲压缩 优化find函数 以优化合并效率
	使用数组做为存储结构
*/

const size_t MAX_UNIONSET_NUM = 20;	//集合的个数

class UnionSetArray {
public:
	void InitUnionSetArray() {
		_set = new int[MAX_UNIONSET_NUM+1]();
		// 初始化 每个集合的父节点设为它们自己
		for (size_t i = 1; i <= MAX_UNIONSET_NUM; ++i) {
			_set[i] = i;	
		}
	}

	void UnionElement(int joinEelem, int jointoElem) {
		int child= FindParent(joinEelem);
		int parent = FindParent(jointoElem);
		_set[child] = parent;
	}

	// 判断两个元素是否存在于同一集合中
	bool IsConnected(int elem1, int elem2) {
		return FindParent(elem1) == FindParent(elem2);
	}


	int FindParent(int elem) {
		if (_set[elem] == elem) {
			return elem;
		}
		else {
			_set[elem] = FindParent(_set[elem]);	//优化路劲
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