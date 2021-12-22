#pragma once
#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
#include<stack>
/*
	˳��洢һ����ҪҪ����������������������������ᵼ�´洢�ռ���˷ѣ����Բ�����ʽ�洢��������
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

	//����һ�����Ϊdepth����������
	bool CreateFullBinaryTree(size_t depth) {
		if (!_head)return false;
		std::queue<TreeNode> _bufferQueue;  //�����������������Ķ���
		std::vector<TreeNode> _tmpVector;	//ռʱ��Ŷ��������ӽڵ㣬�ӳټ���vector�У����ڶ��е��п�

		ElemType elem;
		printf("������ͷ�ڵ�:");
		std::cin >> elem;
		_head->_data = elem;
		TreeNode cur = _head;
		_bufferQueue.push(cur);
		TreeNode lChild = nullptr;
		TreeNode rChild = nullptr;

		while (depth != 1) {
			while (!_bufferQueue.empty()) {
				cur = _bufferQueue.front();
				std::cout << "������" << cur->_data << "�ڵ������: ";
				std::cin >> elem;
				lChild = (TreeNode)malloc(sizeof(BinaryTreeNode<ElemType>));
				if (!lChild)return false;
				lChild->_data = elem;
				lChild->_lChild = nullptr;
				lChild->_rChild = nullptr;
				cur->_lChild = lChild;

				std::cout << "������" << cur->_data << "�ڵ���Һ���: ";
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
		std::cout << "�������!\n";
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

	//�������
	size_t GetTreeDepth() {
		if (!_head)return 0;
		return _TreeDepth(_head);
	}
	//����ڵ���
	size_t GetTreeNodeNums() {
		if (!_head)return 0;
		return _TreeNodeNums(_head);
	}
	//����Ҷ�ӽڵ���
	size_t GetLeafNums() {
		if (!_head)return 0;
		return _LeafNums(_head);
	}

	//��ʾҶ�ӽڵ�
	void DispLeaf() {
		if (!_head)return;
		_DispLeaf(_head);
	}

	//���ҽڵ�
	TreeNode FindNode(const ElemType elem) {
		if (!_head)return nullptr;
		return _FindNode(_head, elem);
	}


	//�ǵݹ��������
	void PreOrder() {
		if (!_head)return;
		std::stack<TreeNode> _stack;	//ģ��Ԫ����ջ��ջ�ķ���
		_stack.push(_head);
		while (!_stack.empty()) {
			TreeNode cur = _stack.top();
			VisitNode(cur);//����ڵ�
			_stack.pop();
			if (cur->_rChild)_stack.push(cur->_rChild);
			if (cur->_lChild)_stack.push(cur->_lChild);
		}
	}

	//�ǵݹ��������
	void InOrder() {
		if (!_head)return;
		std::stack<TreeNode> _stack;	//ģ��Ԫ����ջ��ջ�ķ���
		TreeNode cur = _head;
		while (!_stack.empty()||cur!=nullptr) {
			while (cur != nullptr) {	//��cur����ڵ��ջ
				_stack.push(cur);
				cur = cur->_lChild;
			}
			cur = _stack.top();	//cur���ڵ�ǰ�ҵ��������һ����ڵ�
			VisitNode(cur);
			_stack.pop();
			cur = cur->_rChild;	//�����ҽڵ�
		}
	}

	//�ǵݹ�������
	void PostOrder() {
		if (!_head)return;
		std::stack<TreeNode> _stack;	//ģ��Ԫ����ջ��ջ�ķ���
		TreeNode cur = _head;
		bool bFlag;	//��¼��ǰ�ڵ��������û�б����ʹ�
		do{
			while (cur != nullptr) {	//��ǰ�ڵ����ڵ����ν�ջ
				_stack.push(cur);
				cur = cur->_lChild;
			}
			TreeNode tmp = nullptr;
			bFlag = 1;//1��ʾ�����Ѿ�������
			while (bFlag && !_stack.empty()) {
				cur = _stack.top();
				if (cur->_rChild == tmp) {
					VisitNode(cur);
					tmp = cur;
					_stack.pop();
				}
				else {
					cur = cur->_rChild;
					bFlag = 0;	//��ǰ�Һ��Ӳ�Ϊnull,����flag��Ϊ0����û�з����������
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

	//�ݹ�ǰ�����
	void PreOrderRecursion(TreeNode preNode) {
		if (!preNode)return;
		VisitNode(preNode);
		PreOrderRecursion(preNode->_lChild);
		PreOrderRecursion(preNode->_rChild);
	}

	//�ݹ��������
	void InOrderRecursion(TreeNode preNode) {
		if (!preNode)return;
		InOrderRecursion(preNode->_lChild);
		VisitNode(preNode);
		InOrderRecursion(preNode->_rChild);
	}

	//�ݹ�������
	void PostOrderRecursion(TreeNode preNode) {
		if (!preNode)return;
		PostOrderRecursion(preNode->_lChild);
		PostOrderRecursion(preNode->_rChild);
		VisitNode(preNode);
	}

	//�������
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
	TreeNode _head;	//ͷ�ڵ�
	std::queue<TreeNode> _queue; //ʵ�ֲ�������ĸ�������
};