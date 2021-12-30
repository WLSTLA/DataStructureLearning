#pragma once
#include<iostream>

/*
	��Դ���·��-�Ͻ�˹����
	��������Ȩͼ�����·��,����:��������������Ȩֵ��ͼ
	�㷨˼��: 
	Dijkstra�㷨���õ���һ��̰�ĵĲ��ԣ�����һ������dis������Դ�㵽�����������̾���
		��һ�������Ѿ��ҵ������·���Ķ���ļ��ϣ�T����ʼʱ��
		ԭ�� s ��·��Ȩ�ر���Ϊ 0 ��dis[s] = 0���������ڶ��� s ������ֱ�ӵ���ıߣ�s,m����
		���dis[m]��Ϊw��s, m��,ͬʱ������������s����ֱ�ӵ���ģ������·��������Ϊ����󡣳�ʼʱ������Tֻ�ж���s��
		Ȼ�󣬴�dis����ѡ����Сֵ�����ֵ����Դ��s����ֵ��Ӧ�Ķ�������·�������ҰѸõ���뵽T�У�OK����ʱ���һ�����㣬
		Ȼ��������Ҫ�����¼���Ķ����Ƿ���Ե����������㲢�ҿ���ͨ���ö���
		�����������·�������Ƿ��Դ��ֱ�ӵ���̣�����ǣ���ô���滻��Щ������dis�е�ֵ��
		Ȼ���ִ�dis���ҳ���Сֵ���ظ�����������ֱ��T�а�����ͼ�����ж��㡣
	ʱ�临�Ӷ�: O(V^2)
*/

/*
	�����ڽӾ����Ȩͼ�洢
*/

class MinPathDijkstra {
public:
	void CreateMinPathDijkstra(int(*inEdges)[5]) {
		_edges = inEdges;
		memset(_isFindMinDis,0,5);
		for (size_t i = 0; i < 5; ++i) {
			_minDis[i] = INFINITY;
		}
		for (size_t i = 0; i < 5; ++i) {
			_path[i] = 0;
		}
	}

	void DijkstraFindMinPath(int vertex) {
		if (!_IsValidVertex(vertex))return;
		_isFindMinDis[vertex] = true;
		for (size_t i = 0; i < 5; ++i) {
			_minDis[i] = _edges[vertex][i];
		}
		_path[vertex] = 0;
		std::cout << "[" << vertex << "]";
		while (!_IsAllFindMinPath()) {
			int vertexIndex = 0;
			int minDis = INFINIT;
			for (size_t i = 0; i < 5; ++i) {
				if (_minDis[i] < minDis && _minDis[i]>0&&_isFindMinDis[i]!=true) {
					minDis = _minDis[i];
					vertexIndex = i;
				}
			}
			
			std::cout << " --" << minDis << "-->" << "[" << vertexIndex << "]";		
			_UpdateMinDisAndPath(vertexIndex);
		}
	}

protected:
	void _UpdateMinDisAndPath(size_t vertex) {
		_isFindMinDis[vertex] = true;		
		for (size_t i = 0; i < 5; ++i) {
			// ֻ������Сֵ��û�з���Find����Ķ���
			// ��ǰֵ(����ǰһ��path�����м�¼�Ķ��㵽�ö����·�����ϸ�·����Ҫ���ﶥ���Ȩֵ)
			// ����Ҫ���ﶥ��֮ǰ���õ�ֵ���бȽ�
			int sumDis = _edges[vertex][i] + _minDis[vertex];
			if (_minDis[i] > sumDis && _isFindMinDis[i] != true&& _edges[vertex][i]!=INFINIT) {
				_minDis[i] = sumDis;
				_path[i] = vertex;
			}
		}
	}

	bool _IsValidVertex(size_t vertex) {
		return vertex >= 0 && vertex < 5;
	}

	bool _IsAllFindMinPath(){
		for (size_t i = 0; i < 5; ++i) {
			if (_isFindMinDis[i] != true) {
				return false;
			}
		}
		return true;
	}
private:
	int (*_edges)[5];	
	bool _isFindMinDis[5];	//������¼�Ƿ��Ѿ��ҵ������·���Ľڵ�
	int _minDis[5];	//��¼��n�ڵ㵽���ڵ�֮������·��
	int _path[5];		//·���ϵ�ǰ��
};