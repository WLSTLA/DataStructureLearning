#pragma once
#include<iostream>
#include<queue>
#include<vector>
/*
	最小生成树-prim算法
	算法思想：从某一顶点开始构建生成树，每次将代价最小的新顶点纳入生成树中，直到所有顶点被纳入为止。
	时间复杂度：O(V^2)	适用于边稠密,顶点少
*/

/*
	采用无向图，邻接矩阵存储
*/
const size_t PRIM_MTRIX_VERTEX_NUM = 6;
const int INFINIT = 999;	//代表没有通路

class MinSpinningTreePrimMtrix {
public:
	void CreateMinSpinningTreePrimMtrix(int(*inEdge)[PRIM_MTRIX_VERTEX_NUM]) {
		_edges = inEdge;
		memset(_isJoin, 0, PRIM_MTRIX_VERTEX_NUM);
		for (size_t i = 0; i < PRIM_MTRIX_VERTEX_NUM;++i) {
			_lowCost[i] = INFINIT;
		}
	}

	// 构建最小生成树—Prim
	int MinSpinningTreePRIM(int vertex) {
		if (!_IsValidVertex(vertex))return 0;
		_isJoin[vertex] = true;
		std::cout << "顶点" << vertex << "加入生成树\n";
		_UpdateLowcost(vertex);
		int ret = 0;	//最小生成树长度
		while (!_IsAllJoin()) {					
			// 选择当前能够加入该树中的最小代价顶点加入树
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
			std::cout << "顶点" << minIndex << "加入生成树，路劲长度" << minWeight << "\n";
			ret += minWeight;
		}
		return ret;
	}
protected:
	// 每次新顶点的加入会进行更新
	void _UpdateLowcost(size_t vertexIndex) {
		for (size_t j = 0; j < PRIM_MTRIX_VERTEX_NUM; ++j) {
			//更换最小值，条件是该条边有通路，且没有加入生成树
			if (_edges[vertexIndex][j] < _lowCost[j] && _edges[vertexIndex][j] != 0 && _isJoin[j] != true) {
				_lowCost[j] = _edges[vertexIndex][j];	//存入最小值
			}
		}
	}
	// 判断顶点是否全部加入生成树
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
	int(*_edges)[PRIM_MTRIX_VERTEX_NUM];	//边二维数组指针
	bool _isJoin[PRIM_MTRIX_VERTEX_NUM] = { false };	//已经加入树中的节点
	int _lowCost[PRIM_MTRIX_VERTEX_NUM] = { INFINIT };		//记录个节点加入该树的最小代价
};