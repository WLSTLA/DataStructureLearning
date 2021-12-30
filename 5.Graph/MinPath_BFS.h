#pragma once
#include<iostream>
#include<queue>

/*
	ʹ��BFS�����·���������ַ���ֻ������Ȩͼ�ĵ�Դ���·��
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
			std::cout << "����" << i << "���·��:" << _minDis[i] << " ���Զ���:" << _path[i] << "\n";
		}
	}
protected:
	void _VisitPath(size_t vertex,size_t neighbor) {
		// ��Ϊ����Ȩͼ�����Լٶ�ÿ��·������Ϊ1
		_minDis[neighbor] = _minDis[vertex] + 1;
		_path[neighbor] = vertex;
		std::cout << "����" << neighbor << "���·��:" << _minDis[neighbor] << " ���Զ���:" << _path[neighbor] << "\n";
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
	int _minDis[5];	//��¼��n�㵽������֮�����̾���
	int _path[5];	//��¼���·�����ĸ��������
	int(*_edges)[5];
	bool _visited[5];
};