#pragma once
#include<iostream>
/*
	无向图邻接矩阵存储带权
	特点：是对称矩阵，可以采取矩阵的压缩存取方式，只存储上三角区或下三角区，有n个顶点，则空间复杂度为(O(n*(n-1)/2))
*/

const int NULL_VERTEX = -9999;
const size_t DEFAULT_VERTEX_NUM = 10;
template<class VertexType>
class NonDireGrapth_Matrix {
public:
	void SpawnGrapth(size_t vertexNum, int** edgeArr, VertexType** vertexArray) {
		_vertexNum = vertexNum;
		_edgeArrayPtr = new int* [_vertexNum];
		for (size_t i = 0; i < _vertexNum; ++i) {
			_edgeArrayPtr[i] = new int[_vertexNum];
			for (size_t j = 0; j < _vertexNum; ++j) {
				_edgeArrayPtr[i][j] = *(*edgeArr)++;
			}
		}

		for (size_t i = 0; i < _vertexNum; ++i) {
			_vertexs[i] = *(*vertexArray)++;
		}
	}

	void AddEdge(const VertexType& vertex1, const VertexType& vertex2, int weight) {
		int ver1Index = _GetVertexIndex(vertex1);
		int ver2Index = _GetVertexIndex(vertex2);
		if (ver1Index<0 || ver1Index>_vertexNum - 1 || ver2Index<0 || ver2Index>_vertexNum - 1)return;
		if (_edgeArrayPtr[ver1Index][ver2Index] != 0)return;	//存在边
		_edgeArrayPtr[ver1Index][ver2Index] = weight;
		_edgeArrayPtr[ver2Index][ver1Index] = weight;
	}

	bool DeleteEdge(const VertexType& vertex1, const VertexType& vertex2) {
		int ver1Index = _GetVertexIndex(vertex1);
		int ver2Index = _GetVertexIndex(vertex2);
		if (ver1Index<0 || ver1Index>_vertexNum - 1 || ver2Index<0 || ver2Index>_vertexNum - 1)return false;
		if (_edgeArrayPtr[ver1Index][ver2Index] == 0)return false;	//不存在边 删除失败
		_edgeArrayPtr[ver1Index][ver2Index] = 0;
		_edgeArrayPtr[ver2Index][ver1Index] = 0;
		return true;
	}
	

	void printGrapth()const {
		for (size_t i = 0; i < _vertexNum; ++i) {
			for (size_t j = 0; j < _vertexNum; ++j) {
				std::cout << _edgeArrayPtr[i][j] << " ";
			}
			std::cout << "\n";
		}
	}

	~NonDireGrapth_Matrix()
	{
		DestoryGrapth();
	}
	//第一个邻居
	int FirstNeighbor(const VertexType& vertex) {
		int vertexIndex = _GetVertexIndex(vertex);
		if (vertexIndex == NULL_VERTEX)return -1;
		if (vertexIndex <0 || vertexIndex>_vertexNum - 1)return -1;
		for (size_t index = 0; index < _vertexNum; ++index) {
			if (_edgeArrayPtr[vertexIndex][index] != 0)
				return index;
		}
		return -1;
	}

	//找到vertex顶点，连接的顶点neighbor的下一个顶点
	int NextNeighbor(const VertexType& vertex, const VertexType& neighbor) {
		int vertexIndex = _GetVertexIndex(vertex);
		int neighborvertex = _GetVertexIndex(neighbor);
		if (vertexIndex == NULL_VERTEX)return -1;
		if (vertexIndex<0 || vertexIndex>_vertexNum - 1 || neighborvertex<0 || neighborvertex>_vertexNum - 1)return -1;
		for (size_t index = 0; index < _vertexNum; ++index) {
			if (_edgeArrayPtr[vertexIndex][index] != 0 && index != neighborvertex)
				return index;
		}
		return -1;
	}

	//判断两个顶点是否有边
	bool Adjacent(const VertexType& vertex1, const VertexType& vertex2) {
		int ver1Index = _GetVertexIndex(vertex1);
		int ver2Index = _GetVertexIndex(vertex2);
		if (ver1Index<0 || ver1Index>_vertexNum - 1|| ver2Index<0 || ver2Index>_vertexNum - 1)return false;
		return _edgeArrayPtr[ver1Index][ver2Index] > 0 ? true : false;
	}

	//获取边的权重
	int GetEdgeWight(const VertexType& vertex1, const VertexType& vertex2) {
		int ver1Index = _GetVertexIndex(vertex1);
		int ver2Index = _GetVertexIndex(vertex2);
		if (ver1Index<0 || ver1Index>_vertexNum - 1 || ver2Index<0 || ver2Index>_vertexNum - 1)return -1;
		return _edgeArrayPtr[ver1Index][ver2Index];
	}

	bool SetEdgeWight(const VertexType& vertex1, const VertexType& vertex2,int wight) {
		int ver1Index = _GetVertexIndex(vertex1);
		int ver2Index = _GetVertexIndex(vertex2);
		if (ver1Index<0 || ver1Index>_vertexNum - 1 || ver2Index<0 || ver2Index>_vertexNum - 1)return false;
		_edgeArrayPtr[ver1Index][ver2Index] = wight;
		_edgeArrayPtr[ver2Index][ver1Index] = wight;
		return true;
	}

	void DestoryGrapth() {
		if (!_edgeArrayPtr)return;
		for (size_t i = 0; i < _vertexNum; ++i) {
			delete[]_edgeArrayPtr[i];
		 }
		delete[] _edgeArrayPtr;
	}

	VertexType* GetVertexs(){
		return _vertexs;
	}

protected:
	int _GetVertexIndex(VertexType vertex) {
		for (size_t i = 0; i < _vertexNum; ++i) {
			if (_vertexs[i] == vertex)
				return i;
		}
		return NULL_VERTEX;
	}
private:
	size_t _vertexNum;	 //顶点数
	VertexType _vertexs[DEFAULT_VERTEX_NUM];	//顶点数组
	int** _edgeArrayPtr; //边的二维数组指针
};