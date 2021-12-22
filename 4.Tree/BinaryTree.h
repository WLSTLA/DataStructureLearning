#pragma once
#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
#include<stack>
/*
	顺序存储一般需要要求二叉树是满二叉树，如果不是则会导致存储空间的浪费，所以采用链式存储二叉树，
*/

template<class ElemType>
struct BinaryTreeNode {
	BinaryTreeNode* _lChild;
	BinaryTreeNode* _rChild;
	ElemType _data;
};

enum class TRAVERSEMODE
{
	PreOrder,
	InOrder,
	PostOrder,
	LevelOrder
};

template<class ElemType>
class BinaryTree {
	typedef BinaryTreeNode<ElemType>* TreeNode;
public:
	TreeNode InitBinaryTree() {
		_head = (TreeNode)malloc(sizeof(BinaryTreeNode<ElemType>));
		if (!_head)return nullptr;
		_head->_data = 0;
		_head->_lChild = nullptr;
		_head->_rChild = nullptr;
		return _head;
	}

	//创建一个深度为depth的满二叉树
	bool CreateFullBinaryTree(size_t depth) {
		if (!_head)return false;
		std::queue<TreeNode> _bufferQueue;  //辅助创建满二叉树的队列
		std::vector<TreeNode> _tmpVector;	//占时存放二叉树的子节点，延迟加入vector中，用于队列的判空

		ElemType elem;
		printf("请输入头节点:");
		std::cin >> elem;
		_head->_data = elem;
		TreeNode cur = _head;
		_bufferQueue.push(cur);
		TreeNode lChild = nullptr;
		TreeNode rChild = nullptr;

		while (depth != 1) {
			while (!_bufferQueue.empty()) {
				cur = _bufferQueue.front();
				std::cout << "请输入" << cur->_data << "节点的左孩子: ";
				std::cin >> elem;
				lChild = (TreeNode)malloc(sizeof(BinaryTreeNode<ElemType>));
				if (!lChild)return false;
				lChild->_data = elem;
				lChild->_lChild = nullptr;
				lChild->_rChild = nullptr;
				cur->_lChild = lChild;

				std::cout << "请输入" << cur->_data << "节点的右孩子: ";
				std::cin >> elem;
				rChild = (TreeNode)malloc(sizeof(BinaryTreeNode<ElemType>));
				if (!rChild)return false;
				rChild->_data = elem;
				rChild->_lChild = nullptr;
				rChild->_rChild = nullptr;
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

	~BinaryTree()
	{
		if (!_head)return;
		_DestroyTree(_head);
		_head = nullptr;
	}
	void TraverseTree(TRAVERSEMODE mode) {
		if (!_head)return;
		switch (mode) {
		case TRAVERSEMODE::PreOrder:
			PreOrderRecursion(_head);
			break;
		case TRAVERSEMODE::InOrder:
			InOrderRecursion(_head);
			break;
		case TRAVERSEMODE::PostOrder:
			PostOrderRecursion(_head);
			break;
		case TRAVERSEMODE::LevelOrder:
			LevelOrder(_head);
			break;
		}
		std::cout << "\n";
	}

	//计算深度
	size_t GetTreeDepth() {
		if (!_head)return 0;
		return _TreeDepth(_head);
	}
	//计算节点树
	size_t GetTreeNodeNums() {
		if (!_head)return 0;
		return _TreeNodeNums(_head);
	}
	//计算叶子节点数
	size_t GetLeafNums() {
		if (!_head)return 0;
		return _LeafNums(_head);
	}

	//显示叶子节点
	void DispLeaf() {
		if (!_head)return;
		_DispLeaf(_head);
	}

	//查找节点
	TreeNode FindNode(const ElemType elem) {
		if (!_head)return nullptr;
		return _FindNode(_head, elem);
	}


	//非递归先序遍历
	void PreOrder() {
		if (!_head)return;
		std::stack<TreeNode> _stack;	//模拟元素入栈出栈的访问
		_stack.push(_head);
		while (!_stack.empty()) {
			TreeNode cur = _stack.top();
			VisitNode(cur);//输出节点
			_stack.pop();
			if (cur->_rChild)_stack.push(cur->_rChild);
			if (cur->_lChild)_stack.push(cur->_lChild);
		}
	}

	//非递归中序遍历
	void InOrder() {
		if (!_head)return;
		std::stack<TreeNode> _stack;	//模拟元素入栈出栈的访问
		TreeNode cur = _head;
		while (!_stack.empty()||cur!=nullptr) {
			while (cur != nullptr) {	//将cur的左节点进栈
				_stack.push(cur);
				cur = cur->_lChild;
			}
			cur = _stack.top();	//cur等于当前找到的最左的一个左节点
			VisitNode(cur);
			_stack.pop();
			cur = cur->_rChild;	//处理右节点
		}
	}

	//非递归后序遍历
	void PostOrder() {
		if (!_head)return;
		std::stack<TreeNode> _stack;	//模拟元素入栈出栈的访问
		TreeNode cur = _head;
		bool bFlag;	//记录当前节点的左孩子有没有被访问过
		do{
			while (cur != nullptr) {	//当前节点的左节点依次进栈
				_stack.push(cur);
				cur = cur->_lChild;
			}
			TreeNode tmp = nullptr;
			bFlag = 1;//1表示左孩子已经被访问
			while (bFlag && !_stack.empty()) {
				cur = _stack.top();
				if (cur->_rChild == tmp) {
					VisitNode(cur);
					tmp = cur;
					_stack.pop();
				}
				else {
					cur = cur->_rChild;
					bFlag = 0;	//当前右孩子不为null,所以flag置为0，还没有访问其的左孩子
				}
			}
		} while (!_stack.empty());
	}


protected:
	TreeNode _FindNode(TreeNode preNode,const ElemType elem) {
		if (!preNode)return nullptr;
		else if (preNode->_data == elem)return preNode;
		_FindNode(preNode->_lChild,elem);
		_FindNode(preNode->_rChild,elem);
	}

	void _DispLeaf(TreeNode preNode) {
		if (!preNode)return;
		else if (!preNode->_lChild && !preNode->_rChild)VisitNode(preNode);
		_DispLeaf(preNode->_lChild);
		_DispLeaf(preNode->_rChild);
	}

	size_t _LeafNums(TreeNode PreNode) {
		if (!PreNode->_lChild&&!PreNode->_rChild)return 1;
		return _LeafNums(PreNode->_lChild) + _LeafNums(PreNode->_rChild);
	}


	void _DestroyTree(TreeNode preNode) {
		if (!preNode)return;
		_DestroyTree(preNode->_lChild);
		_DestroyTree(preNode->_rChild);
		free(preNode);
	}

	size_t _TreeDepth(TreeNode preNode) {
		if (!preNode)return 0;
		size_t lDepth = _TreeDepth(preNode->_lChild);
		size_t rDepth = _TreeDepth(preNode->_rChild);
		return lDepth > rDepth ? lDepth + 1 : rDepth + 1;
	}

	size_t _TreeNodeNums(TreeNode preNode) {
		if (!preNode)return 0;
		return (_TreeNodeNums(preNode->_lChild) + _TreeNodeNums(preNode->_rChild)+1);
	}

	void VisitNode(TreeNode curNode)const {
		if (!curNode)return;
		std::cout<< curNode->_data << " ";
	}

	//递归前序遍历
	void PreOrderRecursion(TreeNode preNode) {
		if (!preNode)return;
		VisitNode(preNode);
		PreOrderRecursion(preNode->_lChild);
		PreOrderRecursion(preNode->_rChild);
	}

	//递归中序遍历
	void InOrderRecursion(TreeNode preNode) {
		if (!preNode)return;
		InOrderRecursion(preNode->_lChild);
		VisitNode(preNode);
		InOrderRecursion(preNode->_rChild);
	}

	//递归后序遍历
	void PostOrderRecursion(TreeNode preNode) {
		if (!preNode)return;
		PostOrderRecursion(preNode->_lChild);
		PostOrderRecursion(preNode->_rChild);
		VisitNode(preNode);
	}

	//层序遍历
	void LevelOrder(TreeNode preNode) {
		if (!preNode)return;
		_queue.push(preNode);
		while (!_queue.empty()) {	
			TreeNode cur = _queue.front();
			VisitNode(cur);
			_queue.pop();
			if (cur->_lChild)_queue.push(cur->_lChild);
			if (cur->_rChild)_queue.push(cur->_rChild);
		}
	}


private:
	TreeNode _head;	//头节点
	std::queue<TreeNode> _queue; //实现层序遍历的辅助队列
};