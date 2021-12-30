#pragma once 
#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>
/*
	��³˹�����㷨
	�㷨˼�룺ÿ��ѡȡȨֵ��С�ıߣ�ʹ�������ߵ���ͷ��ͬ��ֱ�����нڵ���ͬ
	ʱ�临�Ӷȣ�O(Elog2E) EΪ�ߵ�����
	�����ڱ�ϡ��ͼ
*/

/*
	����ͼ�ڽӾ���洢
*/

struct Edge {
	Edge() {};
	Edge(size_t begin, size_t end, size_t weight) :_begin(begin), _end(end), _weight(weight) {};
	size_t _begin;	 //�ñߵ����
	size_t _end;	 //�ñߵ��յ�
	size_t _weight;	 //�ߵ�Ȩֵ
	bool operator()(const Edge& edgeRef1,const Edge& edgeRef2)const {
		return edgeRef1._weight < edgeRef2._weight;
	}
};

const size_t KRUSKAL_MTRIX_VERTEX_NUM = 6;

class MinSpinningTreeKruskalMtrix {
public:
	void CreateMinSpinningTreePrimMtrix(int(*inEdge)[KRUSKAL_MTRIX_VERTEX_NUM]) {		
		for (size_t i = 0; i < KRUSKAL_MTRIX_VERTEX_NUM; ++i) {
			for (size_t j = i+1; j < KRUSKAL_MTRIX_VERTEX_NUM; ++j) {	//ֻ��Ҫ�洢��������(����������)����Ϊ����ͼ���ڶԽ��߶Գ�
				if (inEdge[i][j] != 0) {
					Edge tmpEdge(i, j, inEdge[i][j]);
					_priEdges.push_back(tmpEdge);
				}
			}	
		}
		std::sort(_priEdges.begin(), _priEdges.end(), Edge());
		_edgeNums = _priEdges.size();	//�ߵ�����
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
		int* _parent = new int[_edgeNums]{0}; //�����жϹ��ɼ���ı��Ƿ񹹳ɻ�·
		int ret = 0;	
		for (size_t i = 0; i < _edgeNums; ++i) {
			int beginIndex = FindFreeStack(_parent, _priEdges[i]._begin);
			int endIndex = FindFreeStack(_parent, _priEdges[i]._end);
			if (beginIndex != endIndex) {	//beginIndex==endIndex ˵�������˻�·
				// ���˱ߵĽ�β��������±�Ϊ��ʼ��parent�����У���������������
				_parent[beginIndex] = endIndex;
				std::cout << "����" << _priEdges[i]._begin << " ����" << _priEdges[i]._end << " ����,ȨֵΪ:" << _priEdges[i]._weight << "\n";
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
	int _edgeNums;				//�ߵ�����
	std::vector<Edge> _priEdges;
	/*���磺
		 ���	�յ�   Ȩֵ
		  v0     v2     1
		  v3     v4     2
	*/
};