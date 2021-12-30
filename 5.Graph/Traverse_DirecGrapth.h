#pragma once
#include<iostream>
#include<queue>

/*
	”–œÚÕºæÿ’Û¥Ê¥¢
*/
const size_t MAX_VERTEX_NUM = 5;

class DirecGrapthMatrix {
public:
	void InitDirecGrapthMatrix(int(*InEdgeArray)[MAX_VERTEX_NUM]) {
		_EdgePtr = InEdgeArray;
		memset(_Visited, 0, MAX_VERTEX_NUM);
	}

	void PrintDirecGrapthMatrix()const {
		if (!_EdgePtr)return;
		for (size_t i = 0; i < MAX_VERTEX_NUM; ++i) {
			for (size_t j = 0; j < MAX_VERTEX_NUM; ++j) {
				std::cout << *(*(_EdgePtr + i) + j) << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	void BFS(int vertex) {
		if (!_IsValidVertex(vertex))return;
		memset(_Visited, 0, MAX_VERTEX_NUM);
		_VisitVertex(vertex);
		_Visited[vertex] = true;
		std::queue<int> _que;
		_que.push(vertex);
		while (!_que.empty()) {
			vertex = _que.front();
			_que.pop();
			for (int neighbor = _GetFirstNeighbor(vertex); neighbor != -1; neighbor = _GetNextNeighbor(vertex, neighbor)) {
				if (_Visited[neighbor] != true) {
					_VisitVertex(neighbor);
					_Visited[neighbor] = true;
					_que.push(neighbor);
				}
			}
		}
		std::cout << "\n";
	}

	void DFS(int vertex) {
		if (!_IsValidVertex(vertex))return;
		memset(_Visited, 0, MAX_VERTEX_NUM);
		_DFS(vertex);
		std::cout << "\n";
	}


protected:
	void _DFS(int vertex) {
		if (!_IsValidVertex(vertex))return;
		if (_Visited[vertex] != true) {
			_Visited[vertex] = true;
			_VisitVertex(vertex);
			for (int neighbor = _GetFirstNeighbor(vertex); neighbor != -1; neighbor = _GetNextNeighbor(vertex, neighbor)) {
				_DFS(neighbor);
			}
		}
	}
	bool _IsValidVertex(int vertex) {
		return vertex >= 0 && vertex < MAX_VERTEX_NUM;
	}

	int _GetFirstNeighbor(int vertex) {
		if (!_IsValidVertex(vertex))return -1;
		for (size_t i = 0; i < MAX_VERTEX_NUM; ++i) {
			if (_EdgePtr[vertex][i] != 0) {
				return i;
			}
		}
		return -1;
	}

	int _GetNextNeighbor(int vertex, int neighbor) {
		if (!_IsValidVertex(vertex) || !_IsValidVertex(neighbor))return -1;
		for (size_t i = neighbor + 1; i < MAX_VERTEX_NUM; ++i) {
			if (_EdgePtr[vertex][i] != 0) {
				return i;
			}
		}
		return -1;
	}

	void _VisitVertex(int vertex) {
		std::cout << vertex << " ";
	}
private:
	int(*_EdgePtr)[MAX_VERTEX_NUM];
	bool _Visited[MAX_VERTEX_NUM];
};


void test01() {
	int edge[][5] = {
		{0,1,1,1,1},
		{1,0,1,1,1},
		{0,1,0,1,1},
		{0,1,1,0,1},
		{0,1,1,1,0},
	};

	DirecGrapthMatrix s;
	s.InitDirecGrapthMatrix(edge);
	s.PrintDirecGrapthMatrix();

	std::cout << "BFS\n";
	s.BFS(0);	// 0 1 2 3 4 
	s.BFS(1);	// 1 0 2 3 4
	s.BFS(2);
	s.BFS(3);
	s.BFS(4);
	std::cout << "DFS\n";
	s.DFS(0);
	s.DFS(1);
	s.DFS(2);
	s.DFS(3);
	s.DFS(4);
}

