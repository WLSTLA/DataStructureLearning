#pragma once
#include<iostream>
#include<queue>
/*
	����ͼ�Ĺ�����Ⱥ�������ȱ����㷨
	BFS�㷨�����е����־��ǲ����������ͼ�У���Ϊͼ��Ϊ��ͨͼ�ͷ���ͨͼ����ͨͼ������£�ÿ�α�����Ҫ�жϵ�ǰ�ڵ��Ƿ��Ѿ�����������
	ʹ��һ��Visited��������ʾ���������Ľڵ㣬
	ʱ�临�Ӷȣ�
		�ڽӾ���洢:	 O(V^2) vΪ�������
		�ڽӱ�洢:	 O(V+E)	EΪ����

	DFS�㷨�����е����־������������ͬ����ҪVisite��������ʾ�������Ľڵ�
	�ռ临�Ӷ�: ���Եݹ� ���O(1) �O(V)
*/

/*
	�ڽӾ���洢
*/

const size_t DEFAULT_NUM = 5;	//Ĭ�϶�������Ϊ5

class  NonDireGrapthMatrixTraverse {
public:
	void InitNonDireGrapthMatrixTraverse(int* inVertexs, int (*edgeArray)[DEFAULT_NUM]) {
		for (size_t i = 0; i < DEFAULT_NUM; ++i) {
			_vertexs[i] = inVertexs[i];
		}
		_edgePtr = edgeArray;
		memset(_Visited, 0, DEFAULT_NUM);
	}

	//��ȡ��һ���ھ�
	int GetFirstNeighbor(int vertex) {
		if (!_IsValidVertex(vertex))return -1;
		for (size_t i = 0; i < DEFAULT_NUM; ++i) {
			if (*(*(_edgePtr + vertex) + i) != 0) {
				return i;
			}
		}
		return -1;
	}

	//��ȡvertex������neighborVertex����һ���ھӶ���
	int GetNextNeighbor(int vertex,int neighborVertex){
		if (!_IsValidVertex(vertex) || !_IsValidVertex(neighborVertex))return -1;
		if (neighborVertex == DEFAULT_NUM - 1)return -1;	//�ýڵ������һ���ڵ�
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

	//�Ӷ���vertex����,����BFS������ȱ���
	void BFSTraverse(int vertex) {
		if (!_IsValidVertex(vertex))return;
		memset(_Visited,0, DEFAULT_NUM);
		std::queue<int> _queue;	//��¼���Ӷ�����ڽӶ���
		_VisiteVertex(vertex);
		_Visited[vertex] = true;
		_queue.push(vertex);
		while (!_queue.empty()) {
			vertex = _queue.front();
			_queue.pop();
			for (int neighbor = GetFirstNeighbor(vertex); neighbor != -1; neighbor = GetNextNeighbor(vertex, neighbor)) {
				if (_Visited[neighbor] != true) {	//�ö���û�б����ʹ�
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
		//�Ѿ����ʹ��Ķ���ֱ��return
	}

	bool _IsValidVertex(int vertex) {
		return vertex >= 0 && vertex < DEFAULT_NUM;
	}

	void _VisiteVertex(int vertex) {
		std::cout << vertex << " ";
	}
private:
	int _vertexs[DEFAULT_NUM];	//��������	��������Ϊint(0-1-2-3-4)�������
	int(*_edgePtr)[DEFAULT_NUM];	//�߶�ά����ָ��
	bool _Visited[DEFAULT_NUM];	//��¼�Ƿ񱻷��ʹ�������
};



/*
	�ڽӱ�洢
*/
struct TableEdge {
	int _weight;
	TableEdge* _next;
	int _adjvex;	//�ڽӶ���
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
		// ��ver1���㣬������ver2�ı�
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

		// ��ver2���㣬������ver1�ı�
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
			std::cout << "����:" << i;
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
		if (_table[vertex]._first == nullptr)return -1;	//û���ڽӽڵ�
		return _table[vertex]._first->_adjvex;
	}

	int _GetNextNeighbor(int vertex, int neighbor) {
		if (!_IsValidVertex(vertex)|| !_IsValidVertex(neighbor))return -1;
		if (_table[vertex]._first == nullptr)return -1;	//û���ڽӽڵ�
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