#pragma once 
#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>
/*
	克鲁斯卡尔算法
	算法思想：每次选取权值最小的边，使得这条边的两头连同，直到所有节点连同
	时间复杂度：O(Elog2E) E为边的条数
	适用于边稀疏图
*/

/*
	无向图邻接矩阵存储
*/

struct Edge {
	Edge() {};
	Edge(size_t begin, size_t end, size_t weight) :_begin(begin), _end(end), _weight(weight) {};
	size_t _begin;	 //该边的起点
	size_t _end;	 //该边的终点
	size_t _weight;	 //边的权值
	bool operator()(const Edge& edgeRef1,const Edge& edgeRef2)const {
		return edgeRef1._weight < edgeRef2._weight;
	}
};

const size_t KRUSKAL_MTRIX_VERTEX_NUM = 6;

class MinSpinningTreeKruskalMtrix {
public:
	void CreateMinSpinningTreePrimMtrix(int(*inEdge)[KRUSKAL_MTRIX_VERTEX_NUM]) {		
		for (size_t i = 0; i < KRUSKAL_MTRIX_VERTEX_NUM; ++i) {
			for (size_t j = i+1; j < KRUSKAL_MTRIX_VERTEX_NUM; ++j) {	//只需要存储上三角区(或者下三角)，因为无向图关于对角线对称
				if (inEdge[i][j] != 0) {
					Edge tmpEdge(i, j, inEdge[i][j]);
					_priEdges.push_back(tmpEdge);
				}
			}	
		}
		std::sort(_priEdges.begin(), _priEdges.end(), Edge());
		_edgeNums = _priEdges.size();	//边的数量
	}

	void PrintPriorityEdges()const{
		if (_priEdges.empty())return;
		auto ite = _priEdges.begin();
		for (ite; ite != _priEdges.end(); ++ite) {
			std::cout << "begin:" << ite->_begin << " end:" << ite->_end << " weight:" << ite->_weight << "\n";
		}
	}

	int Kruskal() {
		if (_priEdges.empty())return 0 ;
		int* _parent = new int[_edgeNums]{0}; //用来判断构成加入的边是否构成环路
		int ret = 0;	
		for (size_t i = 0; i < _edgeNums; ++i) {
			int beginIndex = FindFreeStack(_parent, _priEdges[i]._begin);
			int endIndex = FindFreeStack(_parent, _priEdges[i]._end);
			if (beginIndex != endIndex) {	//beginIndex==endIndex 说明存在了环路
				// 将此边的结尾顶点放入下标为起始的parent数组中，代表加入该生成树
				_parent[beginIndex] = endIndex;
				std::cout << "顶点" << _priEdges[i]._begin << " 顶点" << _priEdges[i]._end << " 加入,权值为:" << _priEdges[i]._weight << "\n";
				ret += _priEdges[i]._weight;
			}
		}
		int testarr[8];
		for (size_t i = 0; i < _edgeNums; ++i) {
			testarr[i] = _parent[i];
		}
		delete[] _parent;
		return ret;
	}

protected:
	size_t FindFreeStack(int* parent,size_t index) {
		while (parent[index] > 0) {
			index = parent[index];
		}
		return index;
	}

private:
	int _edgeNums;				//边的数量
	std::vector<Edge> _priEdges;
	/*例如：
		 起点	终点   权值
		  v0     v2     1
		  v3     v4     2
	*/
};