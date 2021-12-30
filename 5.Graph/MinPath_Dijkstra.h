#pragma once
#include<iostream>

/*
	单源最短路劲-迪杰斯特拉
	可以求解带权图的最短路劲,局限:不适用于求解带负权值的图
	算法思想: 
	Dijkstra算法采用的是一种贪心的策略，声明一个数组dis来保存源点到各个顶点的最短距离
		和一个保存已经找到了最短路径的顶点的集合：T，初始时，
		原点 s 的路径权重被赋为 0 （dis[s] = 0）。若对于顶点 s 存在能直接到达的边（s,m），
		则把dis[m]设为w（s, m）,同时把所有其他（s不能直接到达的）顶点的路径长度设为无穷大。初始时，集合T只有顶点s。
		然后，从dis数组选择最小值，则该值就是源点s到该值对应的顶点的最短路径，并且把该点加入到T中，OK，此时完成一个顶点，
		然后，我们需要看看新加入的顶点是否可以到达其他顶点并且看看通过该顶点
		到达其他点的路径长度是否比源点直接到达短，如果是，那么就替换这些顶点在dis中的值。
		然后，又从dis中找出最小值，重复上述动作，直到T中包含了图的所有顶点。
	时间复杂度: O(V^2)
*/

/*
	有向邻接矩阵带权图存储
*/

class MinPathDijkstra {
public:
	void CreateMinPathDijkstra(int(*inEdges)[5]) {
		_edges = inEdges;
		memset(_isFindMinDis,0,5);
		for (size_t i = 0; i < 5; ++i) {
			_minDis[i] = INFINITY;
		}
		for (size_t i = 0; i < 5; ++i) {
			_path[i] = 0;
		}
	}

	void DijkstraFindMinPath(int vertex) {
		if (!_IsValidVertex(vertex))return;
		_isFindMinDis[vertex] = true;
		for (size_t i = 0; i < 5; ++i) {
			_minDis[i] = _edges[vertex][i];
		}
		_path[vertex] = 0;
		std::cout << "[" << vertex << "]";
		while (!_IsAllFindMinPath()) {
			int vertexIndex = 0;
			int minDis = INFINIT;
			for (size_t i = 0; i < 5; ++i) {
				if (_minDis[i] < minDis && _minDis[i]>0&&_isFindMinDis[i]!=true) {
					minDis = _minDis[i];
					vertexIndex = i;
				}
			}
			
			std::cout << " --" << minDis << "-->" << "[" << vertexIndex << "]";		
			_UpdateMinDisAndPath(vertexIndex);
		}
	}

protected:
	void _UpdateMinDisAndPath(size_t vertex) {
		_isFindMinDis[vertex] = true;		
		for (size_t i = 0; i < 5; ++i) {
			// 只更新最小值和没有放入Find数组的顶点
			// 当前值(等于前一项path数组中记录的顶点到该顶点的路劲加上该路径所要到达顶点的权值)
			// 与需要到达顶点之前设置的值进行比较
			int sumDis = _edges[vertex][i] + _minDis[vertex];
			if (_minDis[i] > sumDis && _isFindMinDis[i] != true&& _edges[vertex][i]!=INFINIT) {
				_minDis[i] = sumDis;
				_path[i] = vertex;
			}
		}
	}

	bool _IsValidVertex(size_t vertex) {
		return vertex >= 0 && vertex < 5;
	}

	bool _IsAllFindMinPath(){
		for (size_t i = 0; i < 5; ++i) {
			if (_isFindMinDis[i] != true) {
				return false;
			}
		}
		return true;
	}
private:
	int (*_edges)[5];	
	bool _isFindMinDis[5];	//用来记录是否已经找到了最短路径的节点
	int _minDis[5];	//记录从n节点到个节点之间的最短路劲
	int _path[5];		//路劲上的前驱
};