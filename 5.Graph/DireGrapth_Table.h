#pragma once
#include<iostream>

/*
	����ͼ�ڽӱ�洢����Ȩ
	�����������ҵ�ÿ������ĳ��ȣ����ҵ���ȱ�ú����ѣ�������������ڽӱ��ÿ�����㡣
	����ͼʹ���ڽӱ���д洢�����ж���ߵ����������
*/
template<class WeightType>
struct EdgeInfo {			//�߱�ڵ�
	WeightType _weight;
	EdgeInfo* _next;
	size_t _adjvex;	//�ڽӵ�
};

template<class VertexType,class WeightType>
struct VertexInfo {			//�����ڵ�
	EdgeInfo<WeightType>* _firstEdge;
	VertexType _vertex;
};

template<class VertexType, class WeightType>
class DireGraphTable {
public:
	void CreateDireGraphTable(size_t vertexNum, VertexType* vertexs) {
		_table = new VertexInfo<VertexType,WeightType>[vertexNum]();	//����һά�����Ŷ���ṹ
		_vertexNum = vertexNum;
		for (size_t i = 0; i < _vertexNum; ++i) {
			_table[i]._vertex = *vertexs++;
			_table[i]._firstEdge = nullptr;
		}

		return;
		for (size_t i = 0; i < _vertexNum; ++i) {
			while (1) {
				std::cout << "�����붥��" << _table[i]._vertex << "���ڽӱ߽ڵ�(1.�������������,2.'#'�����ô�����):" << "\n";
				char buf;
				std::cin >> buf;
				if (buf == '#')break;
				WeightType weight;
				VertexType vertex;
				std::cout << "�������ڽӵ�:";
				std::cin >> vertex;
				std::cout << "������ߵ�Ȩֵ:";
				std::cin >> weight;
				int vertexIndex = _GetVertexIndex(vertex);
				auto edgeIns = new EdgeInfo<WeightType>();
				edgeIns->_adjvex = vertexIndex;
				edgeIns->_weight = weight;
				//����ͷ�巨	
				edgeIns->_next = _table[i]._firstEdge;
				_table[i]._firstEdge = edgeIns;
			}
		}
	}


	void PrintDireGraphTable()const {
		if (!_table)return;
		for (size_t i = 0; i < _vertexNum; ++i) {
			VertexType vertex = _table[i]._vertex;
			std::cout << "����" << vertex << ":";
			auto tmpEdge = _table[i]._firstEdge;
			if (_table[i]._firstEdge != nullptr) {
				while (tmpEdge!=nullptr) {
					auto tmpVertex = _table[tmpEdge->_adjvex]._vertex;
					std::cout << "--" << tmpEdge->_weight << "-->" << " [" << tmpVertex << "] ";
					tmpEdge = tmpEdge->_next;
				}
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	~DireGraphTable()
	{
		DestoryDireGraphTable();
	}

	//������
	int GetVertexInDegree(const VertexType& vertex) {
		int index = _GetVertexIndex(vertex);
		if (index == -1)return -1;
		int nums = 0;
		for (size_t i = 0; i < _vertexNum; ++i) {
			if (i != index) {	//���ҳ���ǰ�ڵ�����Ľڵ�
				if (_table[i]._firstEdge != nullptr) {
					auto tmpEdge = _table[i]._firstEdge;
					while (tmpEdge) {
						//�ҵ��ýڵ����Ƚڵ�
						if (_table[tmpEdge._adjvex]._vertex == vertex) {
							nums++;
						}
						tmpEdge = tmpEdge->_next;
					}
				}
			}
		}
		return nums;
	}

	//��ó���
	int GetVertexOutDegree(const VertexType& vertex) {
		int index = _GetVertexIndex(vertex);
		if (index == -1)return -1;
		int nums = 0;
		if (_table[index]._firstEdge) {
			auto tmpEdge = _table[index]._firstEdge;
			while(tmpEdge){
				nums++;
				tmpEdge = tmpEdge->_next;
			}
		}
		return nums;
	}

	//ɾ����fromver���㵽tover����ı�
	bool DeleteEdge(VertexType fromVer, VertexType toVer) {
		int fromVerIndex = _GetVertexIndex(fromVer);
		int toVerIndex = _GetVertexIndex(toVer);
		if (fromVerIndex == -1 || toVerIndex == -1)return false;	//����ʧ��
		if (!_table[fromVerIndex]._firstEdge)return false;	//�����ڱ�
		auto tmpEdge = _table[fromVerIndex]._firstEdge;	
		if (toVerIndex == tmpEdge->_adjvex) {	//ɾ�����ǵ�һ����
			_table[fromVerIndex]._firstEdge = tmpEdge->_next;
			delete tmpEdge;
			return true;
		}
		auto preEdge = tmpEdge;
		tmpEdge = tmpEdge->_next;
		while (tmpEdge) {				
			//�ҵ�tover����
			if (tmpEdge->_adjvex== toVerIndex) {
				preEdge->_next = tmpEdge->_next;
				delete tmpEdge;
				break;
			}
			preEdge = tmpEdge;
			tmpEdge = tmpEdge->_next;
		}
		return true;
	}

	// �޸ıߵ�Ȩֵ
	bool ModifyEdge(VertexType fromVer, VertexType toVer,WeightType newWeight) {
		int fromVerIndex = _GetVertexIndex(fromVer);
		int toVerIndex = _GetVertexIndex(toVer);
		if (fromVerIndex == -1 || toVerIndex == -1)return false;	//����ʧ��
		if (!_table[fromVerIndex]._firstEdge)return false;	//�����ڱ�
		auto tmpEdge = _table[fromVerIndex]._firstEdge;
		while (tmpEdge) {
			//�ҵ�tover����
			if (tmpEdge->_adjvex == toVerIndex) {
				tmpEdge->_weight = newWeight;
			}
			tmpEdge = tmpEdge->_next;
		}
		return true;
	}

	// ����±�
	bool AddEdge(VertexType fromVer, VertexType toVer, WeightType weight) {
		int fromVerIndex = _GetVertexIndex(fromVer);
		int toVerIndex = _GetVertexIndex(toVer);
		if (fromVerIndex == -1 || toVerIndex == -1)return false;	//����ʧ��
		if (Adjacent(fromVer, toVer)) {	//����Ѿ����ڱߣ���תΪִ���޸ĸñߵ�Ȩֵ
			return ModifyEdge(fromVer,toVer, weight);
		}
		auto edgeIns = new EdgeInfo<WeightType>();
		edgeIns->_weight = weight;
		edgeIns->_adjvex = toVerIndex;
		edgeIns->_next = _table[fromVerIndex]._firstEdge;
		_table[fromVerIndex]._firstEdge = edgeIns;
		return true;
	}

	//�жϴ�fromVer->toVer��û�б�
	bool Adjacent(VertexType fromVer, VertexType toVer) {
		int fromVerIndex = _GetVertexIndex(fromVer);
		int toVerIndex = _GetVertexIndex(toVer);
		if (fromVerIndex == -1 || toVerIndex == -1)return false;	//����ʧ��
		if (!_table[fromVerIndex]._firstEdge)return false;	//�����ڱ�
		auto tmpEdge = _table[fromVerIndex]._firstEdge;
		while (tmpEdge) {
			//�ҵ�tover����
			if (tmpEdge->_adjvex == toVerIndex) {
				return true;
			}
			tmpEdge = tmpEdge->_next;
		}
		return false;
	}

	void DestoryDireGraphTable() {
		if (!_table)return;
		for (size_t i = 0; i < _vertexNum; ++i) {
			if (_table[i]._firstEdge != nullptr) { 
				auto tmpEdgeIns = _table[i]._firstEdge;
				auto nextEdge = tmpEdgeIns;
				while (tmpEdgeIns)
				{
					nextEdge = tmpEdgeIns->_next;
					delete tmpEdgeIns;
					tmpEdgeIns = nextEdge;
				}
			}
		}
		delete[]_table;
		_table = nullptr;
	}
protected:
	int _GetVertexIndex(const VertexType& vertex) {
		for (size_t i = 0; i < _vertexNum; ++i) {
			if (_table[i]._vertex == vertex)
				return i;
		}
		return -1;
	}
private:
	VertexInfo<VertexType,WeightType>* _table;	//�ڽӱ�
	size_t _vertexNum;
};