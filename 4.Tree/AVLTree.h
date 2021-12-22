#pragma once
#include<queue>
#include<iostream>
#include<stdlib.h>

template<class ElemType>
struct AVLTreeNode {
	ElemType _data;
	AVLTreeNode* _lChild;
	AVLTreeNode* _rChild;
	int _balanceFactor;	//平衡因子
};

enum class RotateMode {
	LL,	//右旋				在左孩子的左子树中的插入导致的不平衡
	RR,	//左旋				在右孩子的右子树中的插入导致的不平衡
	LR,	//先左旋,再右旋		在左孩子的右子树中的插入导致的不平衡
	RL	//先右旋,再左旋		在右孩子的左子树中的插入导致的不平衡
};

template<class ElemType>
class AVLTree {
	typedef AVLTreeNode<ElemType>* Node;
	typedef AVLTreeNode<ElemType>*& NodeRef;
public:
	void InitAVLTree() {
		if (_head)return;//已经初始化
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
			_head = _InsertNode(_head, elemArray[i]); //每次调整之后的头节点都可能发生变化
		}
		return _head;		
	}

	void InOrderTraverse() {
		if (!_head)return;
		_InOrderTraverse(_head);
	}

	//计算某子树的高度
	size_t CalculateSubTreeHeight(Node curNode) {
		if (!curNode)return 0;
		size_t	lTreeHeight = CalculateSubTreeHeight(curNode->_lChild);
		size_t	rTreeHeight = CalculateSubTreeHeight(curNode->_rChild);
		return lTreeHeight > rTreeHeight ? lTreeHeight + 1 : rTreeHeight + 1;
	}


	//计算某个节点的平衡因子
	int CalculateBalanceFactor(Node curNode) {
		int _bf = 0;	//平衡因子
		//左右孩子都为空
		if (!curNode->_lChild && !curNode->_rChild)
			return _bf;
		//左孩子为空,右孩子不为空
		else if (!curNode->_lChild) {
			_bf = CalculateSubTreeHeight(curNode->_rChild);
			return -_bf;	//左子树-右子树<0
		}
		//右孩子为空,左孩子不为空
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
			return nullptr;	//没有找到该节点
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
			// 被删除的节点是叶子节点
			if (!curNode->_lChild && !curNode->_rChild) {
				Node tmp = curNode;
				delete tmp;
				curNode = nullptr;
			}
			// 被删除的节点只有右孩子节点
			else if (!curNode->_lChild) {
				Node tmp = curNode;
				Node rChild = curNode->_rChild;
				delete tmp;
				curNode = rChild;
			}
			// 被删除的节点只有左孩子节点
			else if (!curNode->_rChild) {
				Node tmp = curNode;
				Node lChild = curNode->_lChild;
				delete tmp;
				curNode = lChild;
			}
			// 被删除的节点左右孩子都存在
			else {
				Node maxChild = GetMaxNode(curNode->_lChild);// 查找删除节点左孩子中值最大的节点
				bool isLeftChild;
				Node maxChildParent = GetNodeParent(maxChild, &isLeftChild);	//查找最大节点的父节点
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
		// 更新平衡因子
		curNode->_balanceFactor = CalculateBalanceFactor(curNode);
		int bf = (int)abs(curNode->_balanceFactor);
		// 检测平衡因子
		if (bf > 1) {
			_UpdateNodesBalnceFactor(_head);
			std::cout << "需要调整节点" << curNode->_data << "其平衡因子为:" << curNode->_balanceFactor <<"\n";
			curNode = _AdjustTree(curNode);
		}
		return curNode;
	}


	//检查是否构成平衡二叉树,并且调整
	Node _AdjustTree(Node curNode) {
		if (!curNode)return nullptr;
		//不平衡的情况
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
			tmp = _RightRotate(curNode); //右旋
			break;
		case RotateMode::RR:
			tmp = _LeftRotate(curNode);	//左旋
			break;
		case RotateMode::LR:
			curNode->_lChild = _LeftRotate(curNode->_lChild);	//左旋一次再右旋一次
			tmp = _RightRotate(curNode);
			break;
		case RotateMode::RL:
			curNode->_rChild = _RightRotate(curNode->_rChild);	//右旋一次再再旋一次
			tmp = _LeftRotate(curNode);
			break;
		}	
		return tmp;
	}


	// 左旋 传入的节点需要是最小不平衡子树
	Node _LeftRotate(Node parentNode) {
		Node rChildNode = parentNode->_rChild;	//需要左旋的节点
		parentNode->_rChild = rChildNode->_lChild;	//父节点的右孩子变为原来右孩子的左孩子
		rChildNode->_lChild = parentNode;	//父节点变为右孩子的左孩子
		_UpdateNodesBalnceFactor(_head);
		return rChildNode;
	}
	// 右旋 传入的节点需要是最小不平衡子树
	Node _RightRotate(Node parentNode) {
		Node lChildNode = parentNode->_lChild; //需要右旋的节点
		parentNode->_lChild = lChildNode->_rChild; //父节点的左孩子节点变为原来左孩子节点的右孩子节点
		lChildNode->_rChild = parentNode;	//父节点变为原来左孩子节点的右孩子节点
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

	// 主要用于一开始创建时的插入
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
		//更新平衡因子
		curNode->_balanceFactor = CalculateBalanceFactor(curNode);
		//检查平衡因子
		if ((int)abs(curNode->_balanceFactor) > 1)
		{
			//std::cout << "平衡因子大于1,需要调整节点" << curNode->_data << "\n";	
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