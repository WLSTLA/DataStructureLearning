#pragma once
#include<iostream>

/*
	有向图邻接表存储，带权
	这样很容易找到每个顶点的出度，但找到入度变得很困难，如果遍历整个邻接表的每个顶点。
	无向图使用邻接表进行存储，会有多个边的冗余情况。
*/
template<class WeightType>
struct EdgeInfo {			//边表节点
	WeightType _weight;
	EdgeInfo* _next;
	size_t _adjvex;	//邻接点
};

template<class VertexType,class WeightType>
struct VertexInfo {			//顶点表节点
	EdgeInfo<WeightType>* _firstEdge;
	VertexType _vertex;
};

template<class VertexType, class WeightType>
class DireGraphTable {
public:
	void CreateDireGraphTable(size_t vertexNum, VertexType* vertexs) {
		_table = new VertexInfo<VertexType,WeightType>[vertexNum]();	//声明一维数组存放顶点结构
		_vertexNum = vertexNum;
		for (size_t i = 0; i < _vertexNum; ++i) {
			_table[i]._vertex = *vertexs++;
			_table[i]._firstEdge = nullptr;
		}

		return;
		for (size_t i = 0; i < _vertexNum; ++i) {
			while (1) {
				std::cout << "请输入顶点" << _table[i]._vertex << "的邻接边节点(1.任意键继续输入,2.'#'结束该次输入):" << "\n";
				char buf;
				std::cin >> buf;
				if (buf == '#')break;
				WeightType weight;
				VertexType vertex;
				std::cout << "请输入邻接点:";
				std::cin >> vertex;
				std::cout << "请输入边的权值:";
				std::cin >> weight;
				int vertexIndex = _GetVertexIndex(vertex);
				auto edgeIns = new EdgeInfo<WeightType>();
				edgeIns->_adjvex = vertexIndex;
				edgeIns->_weight = weight;
				//采用头插法	
				edgeIns->_next = _table[i]._firstEdge;
				_table[i]._firstEdge = edgeIns;
			}
		}
	}


	void PrintDireGraphTable()const {
		if (!_table)return;
		for (size_t i = 0; i < _vertexNum; ++i) {
			VertexType vertex = _table[i]._vertex;
			std::cout << "顶点" << vertex << ":";
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

	//获得入度
	int GetVertexInDegree(const VertexType& vertex) {
		int index = _GetVertexIndex(vertex);
		if (index == -1)return -1;
		int nums = 0;
		for (size_t i = 0; i < _vertexNum; ++i) {
			if (i != index) {	//查找除当前节点以外的节点
				if (_table[i]._firstEdge != nullptr) {
					auto tmpEdge = _table[i]._firstEdge;
					while (tmpEdge) {
						//找到该节点的入度节点
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

	//获得出度
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

	//删除从fromver顶点到tover顶点的边
	bool DeleteEdge(VertexType fromVer, VertexType toVer) {
		int fromVerIndex = _GetVertexIndex(fromVer);
		int toVerIndex = _GetVertexIndex(toVer);
		if (fromVerIndex == -1 || toVerIndex == -1)return false;	//查找失败
		if (!_table[fromVerIndex]._firstEdge)return false;	//不存在边
		auto tmpEdge = _table[fromVerIndex]._firstEdge;	
		if (toVerIndex == tmpEdge->_adjvex) {	//删除的是第一条边
			_table[fromVerIndex]._firstEdge = tmpEdge->_next;
			delete tmpEdge;
			return true;
		}
		auto preEdge = tmpEdge;
		tmpEdge = tmpEdge->_next;
		while (tmpEdge) {				
			//找到tover顶点
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

	// 修改边的权值
	bool ModifyEdge(VertexType fromVer, VertexType toVer,WeightType newWeight) {
		int fromVerIndex = _GetVertexIndex(fromVer);
		int toVerIndex = _GetVertexIndex(toVer);
		if (fromVerIndex == -1 || toVerIndex == -1)return false;	//查找失败
		if (!_table[fromVerIndex]._firstEdge)return false;	//不存在边
		auto tmpEdge = _table[fromVerIndex]._firstEdge;
		while (tmpEdge) {
			//找到tover顶点
			if (tmpEdge->_adjvex == toVerIndex) {
				tmpEdge->_weight = newWeight;
			}
			tmpEdge = tmpEdge->_next;
		}
		return true;
	}

	// 添加新边
	bool AddEdge(VertexType fromVer, VertexType toVer, WeightType weight) {
		int fromVerIndex = _GetVertexIndex(fromVer);
		int toVerIndex = _GetVertexIndex(toVer);
		if (fromVerIndex == -1 || toVerIndex == -1)return false;	//查找失败
		if (Adjacent(fromVer, toVer)) {	//如果已经存在边，则转为执行修改该边的权值
			return ModifyEdge(fromVer,toVer, weight);
		}
		auto edgeIns = new EdgeInfo<WeightType>();
		edgeIns->_weight = weight;
		edgeIns->_adjvex = toVerIndex;
		edgeIns->_next = _table[fromVerIndex]._firstEdge;
		_table[fromVerIndex]._firstEdge = edgeIns;
		return true;
	}

	//判断从fromVer->toVer有没有边
	bool Adjacent(VertexType fromVer, VertexType toVer) {
		int fromVerIndex = _GetVertexIndex(fromVer);
		int toVerIndex = _GetVertexIndex(toVer);
		if (fromVerIndex == -1 || toVerIndex == -1)return false;	//查找失败
		if (!_table[fromVerIndex]._firstEdge)return false;	//不存在边
		auto tmpEdge = _table[fromVerIndex]._firstEdge;
		while (tmpEdge) {
			//找到tover顶点
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
	VertexInfo<VertexType,WeightType>* _table;	//邻接表
	size_t _vertexNum;
};