#pragma once
#include<iostream>

/*
	���·������������
	�������ÿ�Զ���֮������·����
	�㷨˼�룺ʹ�õ��Ƕ�̬�滮��˼�룬���vi-vj�����·�����Է�Ϊ���¼����׶Σ�
	#��ʼ��������������������ת�����·���ǣ�
	#0�������ڶ���0��ת�����·���ǣ�
	#1�������ڶ���0������1��ת�����·���ǣ�
	#2�������ڶ���0������1������2��ת�����·���ǣ�
	....
	#n-1, �����ڶ���0��1��2...n-1��ת�����·���ǣ�

	�㷨ʱ�临�Ӷȣ�O(V^3)
	�ռ临�Ӷȣ�O(V^2)

	����������Ȩֵͼ������������Ȩֵ��·��ͼ��
*/

/*
	��Ȩ����ͼ,�ڽӾ���洢
*/

class MinPathFloyd {
public:
	void CreateMinPathFloyd(int(*inEdge)[5],int(*inPath)[5]) {
		_minEdges = inEdge;
		_path = inPath;
	}

	void MinDistanceFloyd() {
		for (size_t i = 0; i < 5; ++i) {	//��һ�������������0��1��2..4������ת
			for (size_t j = 0; j < 5; ++j) {
				for (size_t k = 0; k < 5; ++k) {
					if (_minEdges[j][k] > _minEdges[j][i] + _minEdges[i][k]&& _minEdges[j][k]!=0) {
						_minEdges[j][k] = _minEdges[j][i] + _minEdges[i][k];
						_path[j][k] = i;	//�������ɶ���i����ת��
					}
				}
			}
		}
	}
	
	void GetMinDisByVertexIndex(size_t verFrom,size_t verTo) {
		if (!_IsValidVertex(verFrom)|| !_IsValidVertex(verTo))return;
		std::cout << "���·������:" << _minEdges[verFrom][verTo] << ",·��Ϊ:";
		//std::cout << "[" << verTo << "]<--"<< _minEdges[verFrom][verFrom];
		int PreVertex = verTo;
		while (PreVertex != -1) {		 
			std::cout << " [" << PreVertex << "]<--" << _minEdges[verFrom][PreVertex] << " ";
			PreVertex = _path[verFrom][PreVertex];
		}
	}    

	// �����С�������
	void PrintMinDisMatrix() {
		for (size_t i = 0; i < 5; ++i) {
			for (size_t j = 0; j < 5; ++j) {
				std::cout << _minEdges[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
	// ���ǰ���������
	void PrintPathMatrix() {
		for (size_t i = 0; i < 5; ++i) {
			for (size_t j = 0; j < 5; ++j) {
				std::cout << _path[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
protected:
	bool _IsValidVertex(size_t vertex) {
		return vertex >= 0 && vertex < 5;
	}

private:
	int(*_minEdges)[5];	//������С·���Ķ�ά����
	int (*_path)[5];		//��¼������С·����ǰ������
};