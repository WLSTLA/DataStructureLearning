#pragma once
#include<iostream>
/*
	����ͼ�ڽӾ���洢��Ȩ
	�ص㣺�ǶԳƾ��󣬿��Բ�ȡ�����ѹ����ȡ��ʽ��ֻ�洢����������������������n�����㣬��ռ临�Ӷ�Ϊ(O(n*(n-1)/2))
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
		if (_edgeArrayPtr[ver1Index][ver2Index] != 0)return;	//���ڱ�
		_edgeArrayPtr[ver1Index][ver2Index] = weight;
		_edgeArrayPtr[ver2Index][ver1Index] = weight;
	}

	bool DeleteEdge(const VertexType& vertex1, const VertexType& vertex2) {
		int ver1Index = _GetVertexIndex(vertex1);
		int ver2Index = _GetVertexIndex(vertex2);
		if (ver1Index<0 || ver1Index>_vertexNum - 1 || ver2Index<0 || ver2Index>_vertexNum - 1)return false;
		if (_edgeArrayPtr[ver1Index][ver2Index] == 0)return false;	//�����ڱ� ɾ��ʧ��
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
	//��һ���ھ�
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

	//�ҵ�vertex���㣬���ӵĶ���neighbor����һ������
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

	//�ж����������Ƿ��б�
	bool Adjacent(const VertexType& vertex1, const VertexType& vertex2) {
		int ver1Index = _GetVertexIndex(vertex1);
		int ver2Index = _GetVertexIndex(vertex2);
		if (ver1Index<0 || ver1Index>_vertexNum - 1|| ver2Index<0 || ver2Index>_vertexNum - 1)return false;
		return _edgeArrayPtr[ver1Index][ver2Index] > 0 ? true : false;
	}

	//��ȡ�ߵ�Ȩ��
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
	size_t _vertexNum;	 //������
	VertexType _vertexs[DEFAULT_VERTEX_NUM];	//��������
	int** _edgeArrayPtr; //�ߵĶ�ά����ָ��
};