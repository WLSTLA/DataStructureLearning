#pragma once
#include<iostream>
#include<queue>
#include<vector>
/*
	��С������-prim�㷨
	�㷨˼�룺��ĳһ���㿪ʼ������������ÿ�ν�������С���¶��������������У�ֱ�����ж��㱻����Ϊֹ��
	ʱ�临�Ӷȣ�O(V^2)	�����ڱ߳���,������
*/

/*
	��������ͼ���ڽӾ���洢
*/
const size_t PRIM_MTRIX_VERTEX_NUM = 6;
const int INFINIT = 999;	//����û��ͨ·

class MinSpinningTreePrimMtrix {
public:
	void CreateMinSpinningTreePrimMtrix(int(*inEdge)[PRIM_MTRIX_VERTEX_NUM]) {
		_edges = inEdge;
		memset(_isJoin, 0, PRIM_MTRIX_VERTEX_NUM);
		for (size_t i = 0; i < PRIM_MTRIX_VERTEX_NUM;++i) {
			_lowCost[i] = INFINIT;
		}
	}

	// ������С��������Prim
	int MinSpinningTreePRIM(int vertex) {
		if (!_IsValidVertex(vertex))return 0;
		_isJoin[vertex] = true;
		std::cout << "����" << vertex << "����������\n";
		_UpdateLowcost(vertex);
		int ret = 0;	//��С����������
		while (!_IsAllJoin()) {					
			// ѡ��ǰ�ܹ���������е���С���۶��������
			int minIndex = 0;
			int minWeight = INFINIT;
			for (size_t i = 0; i < PRIM_MTRIX_VERTEX_NUM; ++i) {
				if (_isJoin[i] != true&& minWeight>_lowCost[i]) {
					minIndex = i;
					minWeight = _lowCost[i];
				}
			}
			_isJoin[minIndex] = true;
			_UpdateLowcost(minIndex);
			std::cout << "����" << minIndex << "������������·������" << minWeight << "\n";
			ret += minWeight;
		}
		return ret;
	}
protected:
	// ÿ���¶���ļ������и���
	void _UpdateLowcost(size_t vertexIndex) {
		for (size_t j = 0; j < PRIM_MTRIX_VERTEX_NUM; ++j) {
			//������Сֵ�������Ǹ�������ͨ·����û�м���������
			if (_edges[vertexIndex][j] < _lowCost[j] && _edges[vertexIndex][j] != 0 && _isJoin[j] != true) {
				_lowCost[j] = _edges[vertexIndex][j];	//������Сֵ
			}
		}
	}
	// �ж϶����Ƿ�ȫ������������
	bool _IsAllJoin() {
		for (size_t i = 0; i < PRIM_MTRIX_VERTEX_NUM; ++i) {
			if (_isJoin[i] == false)
				return false;
		}
		return true;
	}


	bool _IsValidVertex(int vertex) {
		return vertex >= 0 && vertex < PRIM_MTRIX_VERTEX_NUM;	//0-4
	}
private:
	int(*_edges)[PRIM_MTRIX_VERTEX_NUM];	//�߶�ά����ָ��
	bool _isJoin[PRIM_MTRIX_VERTEX_NUM] = { false };	//�Ѿ��������еĽڵ�
	int _lowCost[PRIM_MTRIX_VERTEX_NUM] = { INFINIT };		//��¼���ڵ�����������С����
};