#pragma once
#include<iostream>
#include<queue>
/*
	无向图的广度优先和深度优先遍历算法
	BFS算法在树中的体现就是层序遍历，在图中，因为图分为连通图和非连通图，连通图的情况下，每次遍历需要判断当前节点是否已经被遍历过。
	使用一个Visited数组来表示被遍历过的节点，
	时间复杂度：
		邻接矩阵存储:	 O(V^2) v为顶点个数
		邻接表存储:	 O(V+E)	E为边数

	DFS算法在树中的体现就是先序遍历，同样需要Visite数组来表示遍历过的节点
	空间复杂度: 来自递归 最好O(1) 最坏O(V)
*/

/*
	邻接矩阵存储
*/

const size_t DEFAULT_NUM = 5;	//默认顶点数量为5

class  NonDireGrapthMatrixTraverse {
public:
	void InitNonDireGrapthMatrixTraverse(int* inVertexs, int (*edgeArray)[DEFAULT_NUM]) {
		for (size_t i = 0; i < DEFAULT_NUM; ++i) {
			_vertexs[i] = inVertexs[i];
		}
		_edgePtr = edgeArray;
		memset(_Visited, 0, DEFAULT_NUM);
	}

	//获取第一个邻居
	int GetFirstNeighbor(int vertex) {
		if (!_IsValidVertex(vertex))return -1;
		for (size_t i = 0; i < DEFAULT_NUM; ++i) {
			if (*(*(_edgePtr + vertex) + i) != 0) {
				return i;
			}
		}
		return -1;
	}

	//获取vertex顶点中neighborVertex的下一个邻居顶点
	int GetNextNeighbor(int vertex,int neighborVertex){
		if (!_IsValidVertex(vertex) || !_IsValidVertex(neighborVertex))return -1;
		if (neighborVertex == DEFAULT_NUM - 1)return -1;	//该节点是最后一个节点
		for (size_t i = neighborVertex+1; i < DEFAULT_NUM; ++i) {
			if (*(*(_edgePtr + vertex) + i) != 0) {
				return i;
			}
		}
		return -1;
	}

	void PrintNonDireGrapthMatrixBFS()const{
		if (!_edgePtr)return;
		for (int i = 0; i < DEFAULT_NUM; ++i) {
			for (int j = 0; j < DEFAULT_NUM; ++j) {
				std::cout << *(*(_edgePtr + i) + j) << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	//从顶点vertex出发,进行BFS广度优先遍历
	void BFSTraverse(int vertex) {
		if (!_IsValidVertex(vertex))return;
		memset(_Visited,0, DEFAULT_NUM);
		std::queue<int> _queue;	//记录出队顶点的邻接顶点
		_VisiteVertex(vertex);
		_Visited[vertex] = true;
		_queue.push(vertex);
		while (!_queue.empty()) {
			vertex = _queue.front();
			_queue.pop();
			for (int neighbor = GetFirstNeighbor(vertex); neighbor != -1; neighbor = GetNextNeighbor(vertex, neighbor)) {
				if (_Visited[neighbor] != true) {	//该顶点没有被访问过
					_queue.push(neighbor);
					_Visited[neighbor] = true;
					_VisiteVertex(neighbor);
				}
			}
		}
		std::cout << "\n";
	}

	void DFSTraverse(int vertex) {
		if (!_IsValidVertex(vertex))return;
		memset(_Visited, 0, DEFAULT_NUM);
		_DFS(vertex);
		std::cout << "\n";
	}
protected:
	void _DFS(int vertex) {
		if (!_IsValidVertex(vertex))return;
		if (_Visited[vertex] != true) {
			_Visited[vertex] = true;
			_VisiteVertex(vertex);
			for (int neighbor = GetFirstNeighbor(vertex); neighbor != -1; neighbor = GetNextNeighbor(vertex, neighbor)) {
				_DFS(neighbor);
			}
		}
		//已经访问过的顶点直接return
	}

	bool _IsValidVertex(int vertex) {
		return vertex >= 0 && vertex < DEFAULT_NUM;
	}

	void _VisiteVertex(int vertex) {
		std::cout << vertex << " ";
	}
private:
	int _vertexs[DEFAULT_NUM];	//顶点数组	顶点类型为int(0-1-2-3-4)方便测试
	int(*_edgePtr)[DEFAULT_NUM];	//边二维数组指针
	bool _Visited[DEFAULT_NUM];	//记录是否被访问过的数组
};



/*
	邻接表存储
*/
struct TableEdge {
	int _weight;
	TableEdge* _next;
	int _adjvex;	//邻接顶点
};

struct TableHead {
	TableEdge* _first;
};

class  NonDireGrapthTableTraverse {
public:
	void InitNonDireGrapthTableTraverse() {
		memset(_Visited, 0, DEFAULT_NUM);
		for (size_t i = 0; i < DEFAULT_NUM; ++i) {
			_table[i]._first = nullptr;
		}
	}

	void InsertEdge(int ver1, int ver2, int weight) {
		if (!_IsValidVertex(ver1) || !_IsValidVertex(ver2))return;
		// 在ver1顶点，加上与ver2的边
		auto Edge1 = new TableEdge();
		if (!_table[ver1]._first) {
			_table[ver1]._first = Edge1;
			Edge1->_next = nullptr;
		}
		else {
			Edge1->_next = _table[ver1]._first;
			_table[ver1]._first = Edge1;
		}
		Edge1->_adjvex = ver2;
		Edge1->_weight = weight;

		// 在ver2顶点，加上与ver1的边
		auto Edge2 = new TableEdge();
		if (!_table[ver2]._first) {
			_table[ver2]._first = Edge2;
			Edge2->_next = nullptr;
		}
		else {
			Edge2->_next = _table[ver2]._first;
			_table[ver2]._first = Edge2;
		}
		Edge2->_adjvex = ver1;
		Edge2->_weight = weight;
	}


	void PrintNonDireGrapthTable() {
		for (size_t i = 0; i < DEFAULT_NUM; ++i) {
			std::cout << "顶点:" << i;
			if (_table[i]._first != nullptr) {
				auto tmpVer = _table[i]._first;
				while (tmpVer) {
					std::cout << "  --" << tmpVer->_weight << " -->(" << tmpVer->_adjvex << ")";
					tmpVer = tmpVer->_next;
				}
			}
			std::cout << "\n";
		}
	}

	void DestroyNonDireGrapthTableTraverse() {
		for (size_t i = 0; i < DEFAULT_NUM; ++i) {
			if (_table[i]._first == nullptr)
				continue;
			auto tmpVertex = _table[i]._first;
			auto next = tmpVertex;
			while (tmpVertex) {
				next = tmpVertex->_next;
				delete tmpVertex;
				tmpVertex = next;
			}
		}
	}

	~NonDireGrapthTableTraverse()
	{
		DestroyNonDireGrapthTableTraverse();
	}

	void BFSTraverse(int vertex) {
		if (!_IsValidVertex(vertex))return;
		memset(_Visited, 0, DEFAULT_NUM);
		std::queue<int> _queue;
		_VisitVertex(vertex);
		_queue.push(vertex);
		_Visited[vertex] = true;
		while (!_queue.empty()) {
			vertex = _queue.front();
			_queue.pop();
			for (int neighbor = _GetFirstNeighbor(vertex); neighbor != -1; neighbor = _GetNextNeighbor(vertex,neighbor)) {
				if (_Visited[neighbor] != true) {
					_VisitVertex(neighbor);
					_Visited[neighbor] = true;
					_queue.push(neighbor);
				}
			}
		}
		std::cout << "\n";
	}

	void DFSTraverse(int vertex) {
		if (!_IsValidVertex(vertex))return;
		memset(_Visited, 0, DEFAULT_NUM);
		_DFS(vertex);
		std::cout << "\n";
	}

protected:
	void _DFS(int vertex) {
		if (vertex == -1)return;
		if (_Visited[vertex] != true) {
			_VisitVertex(vertex);
			_Visited[vertex] = true;
			for (int neighbor = _GetFirstNeighbor(vertex); neighbor != -1; neighbor = _GetNextNeighbor(vertex, neighbor)) {
				_DFS(neighbor);
			}
		}
	}

	void _VisitVertex(int vertex) {
		std::cout << vertex << " ";
	}
	int _GetFirstNeighbor(int vertex) {
		if (!_IsValidVertex(vertex))return -1;
		if (_table[vertex]._first == nullptr)return -1;	//没有邻接节点
		return _table[vertex]._first->_adjvex;
	}

	int _GetNextNeighbor(int vertex, int neighbor) {
		if (!_IsValidVertex(vertex)|| !_IsValidVertex(neighbor))return -1;
		if (_table[vertex]._first == nullptr)return -1;	//没有邻接节点
		auto tmpVer = _table[vertex]._first;
		while (tmpVer->_adjvex != neighbor&&tmpVer) {
			tmpVer = tmpVer->_next;
		}
		if (!tmpVer)return -1;
		return tmpVer->_next ? tmpVer->_next->_adjvex : -1;
	}

	bool _IsValidVertex(int vertex) {
		return vertex >= 0 && vertex < DEFAULT_NUM;
	}
private:
	TableHead _table[DEFAULT_NUM];
	bool _Visited[DEFAULT_NUM];
};