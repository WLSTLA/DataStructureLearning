#pragma once
#include<iostream>
#include<queue>

/*
	使用BFS求最短路径。但这种方法只能求无权图的单源最短路径
*/


class MinPathBFS {
public:
	void CreateMinPathBFS(int(*inEdges)[5]) {
		_edges = inEdges;
		memset(_visited, 0, 5);
		for (size_t i = 0; i < 5; ++i) {
			_minDis[i] = 0;
		}
		for (size_t i = 0; i < 5; ++i) {
			_path[i] = 0;
		}
	}

	void BFSFindMinPath(size_t vertex) {
		if (!_IsValidVertex(vertex))return;
		memset(_visited, 0, 5);
		std::queue<int> _queue;
		_queue.push(vertex);
		//_VisitPath(vertex);
		_visited[vertex] = true;
		while (!_queue.empty()) {
			vertex = _queue.front();
			_queue.pop();
			for (size_t neighbor = _GetFirstNeighbor(vertex); neighbor != -1; neighbor = _GetNextNeighbor(vertex, neighbor)) {
				if (_visited[neighbor] != true) {
					_queue.push(neighbor);
					_visited[neighbor] = true;
					_VisitPath(vertex,neighbor);
				}
			}
		}
	}

	void PrintMinPathInfo() {
		for (size_t i = 0; i < 5; ++i) {
			std::cout << "顶点" << i << "最短路径:" << _minDis[i] << " 来自顶点:" << _path[i] << "\n";
		}
	}
protected:
	void _VisitPath(size_t vertex,size_t neighbor) {
		// 因为是无权图，所以假定每段路劲长度为1
		_minDis[neighbor] = _minDis[vertex] + 1;
		_path[neighbor] = vertex;
		std::cout << "顶点" << neighbor << "最短路径:" << _minDis[neighbor] << " 来自顶点:" << _path[neighbor] << "\n";
	}

	bool _IsValidVertex(size_t vertex) {
		return vertex >= 0 && vertex < 5;
	}

	int _GetFirstNeighbor(size_t vertex) {
		if (!_IsValidVertex(vertex))return -1;
		for (size_t i = 0; i < 5; ++i) {
			if (_edges[vertex][i] != 0) {
				return i;
			}
		}
		return -1;
	}

	int _GetNextNeighbor(size_t vertex, size_t neighbor) {
		if (!_IsValidVertex(vertex)|| !_IsValidVertex(neighbor))return -1;
		for (size_t i = neighbor + 1; i < 5; ++i) {
			if (_edges[vertex][i] != 0) {
				return i;
			}
		}
		return -1;
	}

private:
	int _minDis[5];	//记录从n点到各个点之间的最短距离
	int _path[5];	//记录最短路径从哪个顶点过来
	int(*_edges)[5];
	bool _visited[5];
};