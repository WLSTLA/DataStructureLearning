#pragma once
#include<iostream>
#include<vector>

template<class ElemType>
struct HuffTreeNode {
	ElemType _weight;	//Ȩֵ
	HuffTreeNode* _lChild;
	HuffTreeNode* _rChild;
	HuffTreeNode* _parent;
};


int IntCompare(void const* val1,void const* val2) {
	return *(int*)val1 - *(int*)val2;
}


template<class ElemType>
class HuffTree {
	typedef HuffTreeNode<ElemType>* Node;
public:
	void CreateHuffTree(ElemType* weightArray, size_t length) {
		std::qsort(weightArray, length, sizeof(ElemType), &IntCompare);

		Node tmpNode1 = new HuffTreeNode<ElemType>();
		tmpNode1->_lChild = nullptr;
		tmpNode1->_rChild = nullptr;
		tmpNode1->_parent = nullptr;
		tmpNode1->_weight = weightArray[0];
		for (size_t i = 1; i < length; ++i) {
			Node tmpNode2 = new HuffTreeNode<ElemType>();
			tmpNode2->_lChild = nullptr;
			tmpNode2->_rChild = nullptr;
			tmpNode2->_parent = nullptr;
			tmpNode2->_weight = weightArray[i];

			//���������ڵ�ĸ��ڵ�
			Node parentNode = new HuffTreeNode<ElemType>();
			//ѡ��Ȩֵ��С����Ϊ����
			parentNode->_lChild = tmpNode1->_weight > tmpNode2->_weight ? tmpNode2 : tmpNode1;
			//ѡ��Ȩֵ�ϴ����Ϊ�Һ���
			parentNode->_rChild = tmpNode1->_weight > tmpNode2->_weight ? tmpNode1 : tmpNode2;
			parentNode->_parent = nullptr;
			parentNode->_weight = tmpNode1->_weight + tmpNode2->_weight;	//ȨֵΪ����֮��
			tmpNode1->_parent = parentNode;
			tmpNode2->_parent = parentNode;
			tmpNode1 = parentNode;
		}
		_head = tmpNode1;
		_LeafVector.reserve(length);
		_GetLeaves(_head);
	}


	~HuffTree()
	{
		if (!_head)return;
		DestroyTree(_head);
	}

	void DestroyTree(Node curNode) {
		if (!curNode)return;
		DestroyTree(curNode->_lChild);
		DestroyTree(curNode->_rChild);
		delete curNode;
	}

	//���ҽڵ�
	Node FindNode(ElemType weight) {
		if (!_head)return nullptr;
		Node target = nullptr;
		_FindNode(_head, weight, target);
		return target;
	}

	// ��ȡ�ڵ㸸�ڵ�
	Node GetNodeParent(Node curNode) {
		if (!curNode)return nullptr;
		return curNode->_parent;
	}

	// ��ȡ�ڵ��·������
	size_t GetNodePathLength(Node curNode) {
		if (!curNode)return 0;
		size_t length = 0;
		while (curNode->_parent) {
			length++;
			curNode = curNode->_parent;
		}
		return length;
	}

	// �������Ҷ�ӽڵ�
	void printLeaf()const {
		for (const auto& leaf : _LeafVector) {
			std::cout << leaf->_weight << " ";
		}
		std::cout << "\n";
	}

	// ����ڵ��Ȩ·������
	size_t GetNodeWPL(Node curNode) {
		if (!curNode)return 0;
		return curNode->_weight*GetNodePathLength(curNode);
	}

	// ������Ĵ�Ȩ·������
	size_t GetTreeWPL() {
		if (!_head)return 0;
		size_t sum = 0;
		for (auto leaf : _LeafVector) {
			sum += GetNodeWPL(leaf);
		}
		return sum;
	}
	
protected:
	void _GetLeaves(Node curNode) {
		if (!curNode)return;
		else if (!curNode->_lChild && !curNode->_rChild) {
			_LeafVector.emplace_back(curNode);
		}
		_GetLeaves(curNode->_lChild);
		_GetLeaves(curNode->_rChild);
	}
	void _FindNode(Node curNode, ElemType weight,Node& targetNode) {
		if (!curNode)return;
		else if (curNode->_weight == weight)
		{
			targetNode = curNode;
			return;
		}
		_FindNode(curNode->_lChild, weight, targetNode);
		_FindNode(curNode->_rChild, weight, targetNode);
	}

private:
	std::vector<Node> _LeafVector;
	Node _head;
};