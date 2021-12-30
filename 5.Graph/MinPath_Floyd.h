#pragma once
#include<iostream>

/*
	最短路劲—弗洛伊德
	可以求得每对顶点之间的最短路劲，
	算法思想：使用的是动态规划的思想，求得vi-vj的最短路劲可以分为以下几个阶段：
	#初始，不允许在其他顶点中转，最短路劲是？
	#0，允许在顶点0中转，最短路劲是？
	#1，允许在顶点0、顶点1中转，最短路劲是？
	#2，允许在顶点0、顶点1、顶点2中转，最短路劲是？
	....
	#n-1, 允许在顶点0、1、2...n-1中转，最短路径是？

	算法时间复杂度：O(V^3)
	空间复杂度：O(V^2)

	可以求解带负权值图，不能求解带负权值回路的图。
*/

/*
	带权有向图,邻接矩阵存储
*/

class MinPathFloyd {
public:
	void CreateMinPathFloyd(int(*inEdge)[5],int(*inPath)[5]) {
		_minEdges = inEdge;
		_path = inPath;
	}

	void MinDistanceFloyd() {
		for (size_t i = 0; i < 5; ++i) {	//第一层代表了允许顶点0、1、2..4进行中转
			for (size_t j = 0; j < 5; ++j) {
				for (size_t k = 0; k < 5; ++k) {
					if (_minEdges[j][k] > _minEdges[j][i] + _minEdges[i][k]&& _minEdges[j][k]!=0) {
						_minEdges[j][k] = _minEdges[j][i] + _minEdges[i][k];
						_path[j][k] = i;	//代表是由顶点i进行转接
					}
				}
			}
		}
	}
	
	void GetMinDisByVertexIndex(size_t verFrom,size_t verTo) {
		if (!_IsValidVertex(verFrom)|| !_IsValidVertex(verTo))return;
		std::cout << "最短路劲长度:" << _minEdges[verFrom][verTo] << ",路劲为:";
		//std::cout << "[" << verTo << "]<--"<< _minEdges[verFrom][verFrom];
		int PreVertex = verTo;
		while (PreVertex != -1) {		 
			std::cout << " [" << PreVertex << "]<--" << _minEdges[verFrom][PreVertex] << " ";
			PreVertex = _path[verFrom][PreVertex];
		}
	}    

	// 输出最小距离矩阵
	void PrintMinDisMatrix() {
		for (size_t i = 0; i < 5; ++i) {
			for (size_t j = 0; j < 5; ++j) {
				std::cout << _minEdges[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
	// 输出前驱顶点矩阵
	void PrintPathMatrix() {
		for (size_t i = 0; i < 5; ++i) {
			for (size_t j = 0; j < 5; ++j) {
				std::cout << _path[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
protected:
	bool _IsValidVertex(size_t vertex) {
		return vertex >= 0 && vertex < 5;
	}

private:
	int(*_minEdges)[5];	//储存最小路劲的二维数组
	int (*_path)[5];		//记录顶点最小路劲的前驱顶点
};