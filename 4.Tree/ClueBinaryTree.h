#pragma once
#include<queue>
#include<iostream>
#include<stack>
/*
	中序二叉线索树
*/

template<class ElemType>
struct ClueBinaryNode {
	ElemType _data;
	ClueBinaryNode* _lChild;
	ClueBinaryNode* _rChild;
	bool _lChildFlag;	//true 指向线索 false 指向左孩子
	bool _rChildFlag;	//true 指向线索 false 指向右孩子
};


template<class ElemType>
class ClueBinaryTree {
	typedef ClueBinaryNode<ElemType>* Node;
	typedef ClueBinaryNode<ElemType>*& NodeRef;
public:
	void InitTree() {
		_head = new ClueBinaryNode<ElemType>();
		_head->_data = 0;
		_head->_lChild = nullptr;
		_head->_rChild = nullptr;
		_head->_lChildFlag = false;
		_head->_rChildFlag = false;
	}


	void DestroyTree(Node curNode) {
		if (!curNode)return;
		if (curNode->_lChildFlag == false)
			DestroyTree(curNode->_lChild);
		if (curNode->_rChildFlag == false)
			DestroyTree(curNode->_rChild);
		delete curNode;
	}

	~ClueBinaryTree()
	{
		if (!_head)return;
		DestroyTree(_head);
		_head = nullptr;
	}

	//创建一个深度为depth的满二叉树
	bool CreateFullBinaryTree(size_t depth) {
		if (!_head)return false;
		std::queue<Node> _bufferQueue;  //辅助创建满二叉树的队列
		std::vector<Node> _tmpVector;	//占时存放二叉树的子节点，延迟加入vector中，用于队列的判空

		ElemType elem;
		printf("请输入头节点:");
		std::cin >> elem;
		_head->_data = elem;
		Node cur = _head;
		_bufferQueue.push(cur);
		Node lChild = nullptr;
		Node rChild = nullptr;

		while (depth != 1) {
			while (!_bufferQueue.empty()) {
				cur = _bufferQueue.front();
				std::cout << "请输入" << cur->_data << "节点的左孩子: ";
				std::cin >> elem;
				lChild = new ClueBinaryNode<ElemType>();
				if (!lChild)return false;
				lChild->_data = elem;
				lChild->_lChild = nullptr;
				lChild->_rChild = nullptr;
				lChild->_lChildFlag = false;
				lChild->_rChildFlag = false;
				cur->_lChild = lChild;

				std::cout << "请输入" << cur->_data << "节点的右孩子: ";
				std::cin >> elem;
				rChild = new ClueBinaryNode<ElemType>();
				if (!rChild)return false;
				rChild->_data = elem;
				rChild->_lChild = nullptr;
				rChild->_rChild = nullptr;
				rChild->_lChildFlag = false;
				rChild->_rChildFlag = false;
				cur->_rChild = rChild;

				_bufferQueue.pop();
				_tmpVector.push_back(lChild);
				_tmpVector.push_back(rChild);
			}

			for (auto child : _tmpVector) {
				_bufferQueue.push(child);
			}
			_tmpVector.clear();
			depth--;
		}
		std::cout << "创建完成!\n";
		return true;
	}


	//创建中序线索树
	void CreateInOrderClueTree() {
		if (!_head)return;
		_preNode = nullptr; //重置父节点
		_InOrder(_head);
	}


	Node FindElem(ElemType elem) {
		if (!_head)return nullptr;
		Node cur = _head;
		while (cur != nullptr) {
			if (cur->_data == elem) {
				return cur;
			}
			while (cur->_lChildFlag == false) {
				cur = cur->_lChild;	//找到当前节点的开始的节点，一开始为中序遍历的初始节点
			}
			while (cur->_rChildFlag == true) {
				cur = cur->_rChild;
			}
			cur = cur->_rChild;
		}
	}

	//中序线索二叉树的遍历
	void TraverseInOrderClueTree() {
		if (!_head)return;
		Node cur = _head->_lChild;
		while (cur!=nullptr) {
			while (cur->_lChildFlag==false) {
				cur = cur->_lChild;	//找到当前节点的开始的节点，一开始为中序遍历的初始节点
			}
			_VisitNode(cur);
			while (cur->_rChildFlag == true) {
				cur = cur->_rChild;
				_VisitNode(cur);
			}
			cur = cur->_rChild;
		}
	}


protected:
	void _VisitNode(Node curNode) {
		if (!curNode)return;
		std::cout << curNode->_data << " ";
	}

	void _InOrder(Node curNode) {
		if (!curNode)return;
		_InOrder(curNode->_lChild);
		_CreateInOrderClueNode(curNode);
		_InOrder(curNode->_rChild);
	}

	//创建中序线索节点
	void _CreateInOrderClueNode(Node curNode) {
		if (curNode->_lChild == nullptr) {
			curNode->_lChildFlag = true;
			curNode->_lChild = _preNode;
		}
		else if (_preNode != nullptr && _preNode->_rChild == nullptr) {
			_preNode->_rChild = curNode;
			_preNode->_rChildFlag = true;
		}
		_preNode = curNode;
	}
private:
	Node _head;
	Node _preNode;//指向当前节点的前一个变量，    
};
