#pragma once
#include<queue>
#include<iostream>
#include<stdlib.h>

template<class ElemType>
struct AVLTreeNode {
	ElemType _data;
	AVLTreeNode* _lChild;
	AVLTreeNode* _rChild;
	int _balanceFactor;	//ƽ������
};

enum class RotateMode {
	LL,	//����				�����ӵ��������еĲ��뵼�µĲ�ƽ��
	RR,	//����				���Һ��ӵ��������еĲ��뵼�µĲ�ƽ��
	LR,	//������,������		�����ӵ��������еĲ��뵼�µĲ�ƽ��
	RL	//������,������		���Һ��ӵ��������еĲ��뵼�µĲ�ƽ��
};

template<class ElemType>
class AVLTree {
	typedef AVLTreeNode<ElemType>* Node;
	typedef AVLTreeNode<ElemType>*& NodeRef;
public:
	void InitAVLTree() {
		if (_head)return;//�Ѿ���ʼ��
		_head = new AVLTreeNode<ElemType>();
		_head->_data = 0;
		_head->_balanceFactor = 0;
		_head->_lChild = nullptr;
		_head->_rChild = nullptr;
	}

	Node CreateAVLTree(ElemType* elemArray,size_t arrayLength) {
		if (!_head)return nullptr;
		_head->_data = elemArray[0];
		for (size_t i = 1; i < arrayLength; ++i) {
			_head = _InsertNode(_head, elemArray[i]); //ÿ�ε���֮���ͷ�ڵ㶼���ܷ����仯
		}
		return _head;		
	}

	void InOrderTraverse() {
		if (!_head)return;
		_InOrderTraverse(_head);
	}

	//����ĳ�����ĸ߶�
	size_t CalculateSubTreeHeight(Node curNode) {
		if (!curNode)return 0;
		size_t	lTreeHeight = CalculateSubTreeHeight(curNode->_lChild);
		size_t	rTreeHeight = CalculateSubTreeHeight(curNode->_rChild);
		return lTreeHeight > rTreeHeight ? lTreeHeight + 1 : rTreeHeight + 1;
	}


	//����ĳ���ڵ��ƽ������
	int CalculateBalanceFactor(Node curNode) {
		int _bf = 0;	//ƽ������
		//���Һ��Ӷ�Ϊ��
		if (!curNode->_lChild && !curNode->_rChild)
			return _bf;
		//����Ϊ��,�Һ��Ӳ�Ϊ��
		else if (!curNode->_lChild) {
			_bf = CalculateSubTreeHeight(curNode->_rChild);
			return -_bf;	//������-������<0
		}
		//�Һ���Ϊ��,���Ӳ�Ϊ��
		else if (!curNode->_rChild) {
			_bf = CalculateSubTreeHeight(curNode->_lChild);
			return _bf;
		}
		else {
			size_t lTreeHeight = CalculateSubTreeHeight(curNode->_lChild);
			size_t rTreeHeight = CalculateSubTreeHeight(curNode->_rChild);
			_bf = lTreeHeight - rTreeHeight;
			return _bf;
		}
	}

	~AVLTree()
	{
		if (!_head)return;
		DestroyAVLTree(_head);
		_head = nullptr;
	}

	void DestroyAVLTree(Node curNode) {
		if (!curNode)return;
		DestroyAVLTree(curNode->_lChild);
		DestroyAVLTree(curNode->_rChild);
		delete curNode;
	}

	bool IsBalanced() {
		if (!_head)return false;
		return _IsBalanced(_head);
	}


	Node GetNodeParent(Node curNode,bool* isLeftChild) {
		if (!curNode||!_head)return nullptr;
		Node cur = _head;
		Node pre = cur;	
		while (cur->_data != curNode->_data) {
			pre = cur;
			if (cur->_data > curNode->_data) {
				cur = cur->_lChild;
			}
			else if (cur->_data < curNode->_data) {
				cur = cur->_rChild;
			}
		}
		if (cur != nullptr)
			if (pre->_lChild == cur) {
				*isLeftChild = true;
				return pre;
			}
			else if (pre->_rChild == cur) {
				*isLeftChild = false;
				return pre;
			}
		else
			return nullptr;	//û���ҵ��ýڵ�
	}
	

	Node GetNode(ElemType elem) {
		if (!_head)return nullptr;
		Node cur = _head;
		while (cur&&cur->_data != elem) {
			if (cur->_data > elem) {
				cur = cur->_lChild;
			}
			else if (cur->_data < elem) {
				cur = cur->_rChild;
			}
		}
		if (cur != nullptr)
			return cur;
		else
			return nullptr;
	}

	void DeleteElem(ElemType elem) {
		if (!_head)return;
		_head = _DeleteElem(_head,elem);
	}

	Node GetMaxNode(Node curNode) {
		if (!curNode)return nullptr;
		while (curNode->_rChild) {
			curNode = curNode->_rChild;
		}
		return curNode;
	}

	Node GetMinNode(Node curNode) {
		if (!curNode)return nullptr;
		while (curNode->_lChild) {
			curNode = curNode->_lChild;
		}
		return curNode;
	}
protected:
	Node _DeleteElem(Node curNode, ElemType elem) {
		if (!curNode)return nullptr;
		if (curNode->_data > elem) 
			curNode->_lChild = _DeleteElem(curNode->_lChild, elem);
		else if(curNode->_data < elem)
			curNode->_rChild = _DeleteElem(curNode->_rChild, elem);
		else {	
			// ��ɾ���Ľڵ���Ҷ�ӽڵ�
			if (!curNode->_lChild && !curNode->_rChild) {
				Node tmp = curNode;
				delete tmp;
				curNode = nullptr;
			}
			// ��ɾ���Ľڵ�ֻ���Һ��ӽڵ�
			else if (!curNode->_lChild) {
				Node tmp = curNode;
				Node rChild = curNode->_rChild;
				delete tmp;
				curNode = rChild;
			}
			// ��ɾ���Ľڵ�ֻ�����ӽڵ�
			else if (!curNode->_rChild) {
				Node tmp = curNode;
				Node lChild = curNode->_lChild;
				delete tmp;
				curNode = lChild;
			}
			// ��ɾ���Ľڵ����Һ��Ӷ�����
			else {
				Node maxChild = GetMaxNode(curNode->_lChild);// ����ɾ���ڵ�������ֵ���Ľڵ�
				bool isLeftChild;
				Node maxChildParent = GetNodeParent(maxChild, &isLeftChild);	//�������ڵ�ĸ��ڵ�
				curNode->_data = maxChild->_data;
				if (maxChildParent != curNode)
					maxChildParent->_rChild = maxChild->_lChild;
				else
					maxChildParent->_lChild = nullptr;
				delete maxChild;
				maxChild = nullptr;
			}
		}
		if (!curNode)return curNode;
		// ����ƽ������
		curNode->_balanceFactor = CalculateBalanceFactor(curNode);
		int bf = (int)abs(curNode->_balanceFactor);
		// ���ƽ������
		if (bf > 1) {
			_UpdateNodesBalnceFactor(_head);
			std::cout << "��Ҫ�����ڵ�" << curNode->_data << "��ƽ������Ϊ:" << curNode->_balanceFactor <<"\n";
			curNode = _AdjustTree(curNode);
		}
		return curNode;
	}


	//����Ƿ񹹳�ƽ�������,���ҵ���
	Node _AdjustTree(Node curNode) {
		if (!curNode)return nullptr;
		//��ƽ������
		RotateMode rotate = RotateMode::LL;
		Node tmp = nullptr;

		if (curNode->_lChild && curNode->_balanceFactor > 1 && curNode->_lChild->_balanceFactor >= 0)
			rotate = RotateMode::LL;
		else if (curNode->_rChild &&curNode->_balanceFactor < -1 && curNode->_rChild->_balanceFactor < 0)
			rotate = RotateMode::RR;
		else if (curNode->_rChild && curNode->_balanceFactor < -1 && curNode->_rChild->_balanceFactor >= 0)
			rotate = RotateMode::RL;
		else if (curNode->_lChild && curNode->_balanceFactor > 1 && curNode->_lChild->_balanceFactor < 0)
			rotate = RotateMode::LR;
		switch (rotate)
		{
		case RotateMode::LL:
			tmp = _RightRotate(curNode); //����
			break;
		case RotateMode::RR:
			tmp = _LeftRotate(curNode);	//����
			break;
		case RotateMode::LR:
			curNode->_lChild = _LeftRotate(curNode->_lChild);	//����һ��������һ��
			tmp = _RightRotate(curNode);
			break;
		case RotateMode::RL:
			curNode->_rChild = _RightRotate(curNode->_rChild);	//����һ��������һ��
			tmp = _LeftRotate(curNode);
			break;
		}	
		return tmp;
	}


	// ���� ����Ľڵ���Ҫ����С��ƽ������
	Node _LeftRotate(Node parentNode) {
		Node rChildNode = parentNode->_rChild;	//��Ҫ�����Ľڵ�
		parentNode->_rChild = rChildNode->_lChild;	//���ڵ���Һ��ӱ�Ϊԭ���Һ��ӵ�����
		rChildNode->_lChild = parentNode;	//���ڵ��Ϊ�Һ��ӵ�����
		_UpdateNodesBalnceFactor(_head);
		return rChildNode;
	}
	// ���� ����Ľڵ���Ҫ����С��ƽ������
	Node _RightRotate(Node parentNode) {
		Node lChildNode = parentNode->_lChild; //��Ҫ�����Ľڵ�
		parentNode->_lChild = lChildNode->_rChild; //���ڵ�����ӽڵ��Ϊԭ�����ӽڵ���Һ��ӽڵ�
		lChildNode->_rChild = parentNode;	//���ڵ��Ϊԭ�����ӽڵ���Һ��ӽڵ�
		_UpdateNodesBalnceFactor(_head);	
		return lChildNode;
	}


	void _UpdateNodesBalnceFactor(Node curNode) {
		if (!curNode)return;
		curNode->_balanceFactor = CalculateBalanceFactor(curNode);
		_UpdateNodesBalnceFactor(curNode->_lChild);
		_UpdateNodesBalnceFactor(curNode->_rChild);
	}

	bool _IsBalanced(Node curNode) {
		if (!curNode)return true;
		else if ((int)abs(curNode->_balanceFactor) > 1)return false;
		return _IsBalanced(curNode->_lChild) && _IsBalanced(curNode->_rChild);
	}

	// ��Ҫ����һ��ʼ����ʱ�Ĳ���
	Node _InsertNode(Node curNode, ElemType elem) {
		if (!curNode) {
			Node newNode = new AVLTreeNode<ElemType>();
			newNode->_data = elem;
			newNode->_balanceFactor = 0;
			newNode->_lChild = nullptr;
			newNode->_rChild = nullptr;
			return newNode;
		}
		if (curNode->_data > elem) {
			curNode->_lChild = _InsertNode(curNode->_lChild, elem);
		}
		else if (curNode->_data < elem) {
			curNode->_rChild = _InsertNode(curNode->_rChild, elem);
		}
		//����ƽ������
		curNode->_balanceFactor = CalculateBalanceFactor(curNode);
		//���ƽ������
		if ((int)abs(curNode->_balanceFactor) > 1)
		{
			//std::cout << "ƽ�����Ӵ���1,��Ҫ�����ڵ�" << curNode->_data << "\n";	
			curNode = _AdjustTree(curNode);
		}
		return curNode;
	}


	void _InOrderTraverse(Node curNode) {
		if (!curNode)return;
		_InOrderTraverse(curNode->_lChild);
		_VisitNode(curNode);
		_InOrderTraverse(curNode->_rChild);
	}

	void _VisitNode(Node curNode) {
		if (!curNode)return;
		std::cout << curNode->_data << " ";
	}

private:
	Node _head;
};