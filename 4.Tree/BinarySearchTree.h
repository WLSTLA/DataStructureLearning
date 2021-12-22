#pragma once
#include<iostream>
#include<queue>

/*
	����������
*/


template<class ElemType>
struct BSTNode
{
	ElemType _elem;
	BSTNode* _lChild;
	BSTNode* _rChild;
};

template<class ElemType>
class BSTree {
	typedef BSTNode<ElemType>* Node;
	typedef BSTNode<ElemType>*& NodeRef;
public:
	void CreateBSTree(ElemType* nodeArray,size_t size) {
		_head = new BSTNode<ElemType>();
		_head->_lChild = nullptr;
		_head->_rChild = nullptr;
		_head->_elem = nodeArray[0];
		for (size_t i = 1; i < size; ++i) {
			_InsertNode(_head, nodeArray[i]);
		}
	}

	void DestroyBSTree(Node curNode) {
		if (!curNode)return;
		DestroyBSTree(curNode->_lChild);
		DestroyBSTree(curNode->_rChild);
		delete curNode;
	}

	~BSTree()
	{
		if (!_head)return;
		DestroyBSTree(_head);
		_head = nullptr;
	}

	void PreOrderRecursion() {
		if (!_head)return;
		_PreOrderReCursion(_head);
	}
	void InOrderRecursion() {
		if (!_head)return;
		_InOrderReCursion(_head);
	}

	void PostOrderRecusion() {
		if (!_head)return;
		_PostOrderReCursion(_head);
	}

	void LevelOrder() {
		if (!_head)return;
		_LevelOrder(_head);
	}

	Node FindElem(ElemType elem) {
		if (!_head)return nullptr;
		Node cur = _head;
		while (cur && elem != cur->_elem) {
			if (elem < cur->_elem) {
				cur = cur->_lChild;
			}
			else {
				cur = cur->_rChild;
			}
		}
		return cur;
	}

	//����ڵ�
	void InsertNode(ElemType elem) {
		if (!_head)return;
		_InsertNode(_head,elem);
	}
	//��ȡ�������Ľڵ�
	Node GetMaxNode() {
		if (!_head)return _head;
		Node cur = _head;
		while (cur->_rChild != nullptr) {
			cur = cur->_rChild;
		}
		return cur;
	}
	//��ȡ������С�Ľڵ�
	Node GetMinNode() {
		if (!_head)return nullptr;
		Node cur = _head;
		while (cur->_lChild != nullptr) {
			cur = cur->_lChild;
		}
		return cur;
	}

	//ɾ��һ���ڵ�
	bool DeleteElem(ElemType elem) {
		if (!_head)return false;
		Node deleteNode = FindElem(elem);
		if (!deleteNode)return false;
		NodeRef deleteNodeRef = deleteNode;
		_DeleteElem(deleteNodeRef);
		return true; 
	}

	Node GetPreviousNode(Node curNode,bool& flag){
		if (!curNode||!_head)return nullptr;
		Node tmp = _head;
		Node pre = _head;
		while (tmp->_elem!=curNode->_elem) {
			pre = tmp; //preָ�򸸽ڵ�ڵ�
			if (curNode->_elem < tmp->_elem) {
				tmp = tmp->_lChild;
			}
			else if (curNode->_elem > tmp->_elem) {
				tmp = tmp->_rChild;
			}
		}
		if (pre->_lChild == curNode&&pre)flag = true;	//���ҽڵ��Ǹ��ڵ������
		else if (pre->_rChild == curNode&&pre)flag = false; //���ҽڵ��Ǹ��ڵ���Һ���
		return pre;
	}

protected:
	void _DeleteElem(NodeRef nodeRef) {
		Node tmp = nullptr;
		bool flag;
		//��ɾ���Ľڵ���Ҷ�ӽڵ�
		if (!nodeRef->_rChild && !nodeRef->_lChild) {
			tmp = nodeRef;
			Node parent = GetPreviousNode(tmp,flag);	//��ȡɾ���ڵ�ĸ��ڵ�
			if (flag) {//���ĸ��ڵ�ָ��
				parent->_lChild = nullptr;
			}
			else {
				parent->_rChild = nullptr;
			}
			delete tmp;
		}
		//��ɾ���Ľڵ�û���Һ���
		else if (!nodeRef->_rChild) {
			tmp = nodeRef;
			nodeRef = nodeRef->_lChild;
			Node parent = GetPreviousNode(tmp, flag);
			if (flag) {
				parent->_lChild = nodeRef;	
			}
			else {
				parent->_rChild = nodeRef;
			}
			delete tmp;
		}
		//��ɾ���Ľڵ�û������
		else if (!nodeRef->_lChild) {
			tmp = nodeRef;
			nodeRef = nodeRef->_rChild;
			Node parent = GetPreviousNode(tmp, flag);
			if (flag) {
				parent->_lChild = nodeRef;
			}
			else {
				parent->_rChild = nodeRef;
			}
			delete tmp;
		}
		//��ɾ���Ľڵ������Ӻ��Һ��ӣ�����ѡ�����������ѡ������һ���ڵ㣬���ߴ�������ѡ����С��һ���ڵ㣬���滻
		else {
			tmp = nodeRef;
			Node switchNode = _GetMaxNodeInTree(tmp->_lChild);	//�������������Ľڵ���Ϊ�滻
			NodeRef switchNodeRef = switchNode;
			if (switchNode) {
				tmp = switchNodeRef;
				Node parent = GetPreviousNode(tmp, flag);
				nodeRef->_elem = switchNodeRef->_elem;	//ɾ���ڵ��ֵ���滻�ڵ��ֵ�໥�滻��ֻ������ֵ�滻���൱�ڽ����ˡ�ɾ���������ɾ���滻�ڵ㡣
				switchNodeRef = switchNodeRef->_lChild; //�滻�ڵ���������ӣ���Ϊѡ����������е����ֵ������ֻ����������
				if (flag) {
					parent->_lChild = switchNode;
				}
				else {
					parent->_rChild = switchNode;
				}
				free(tmp);
			}
		}
	}

	Node _GetMaxNodeInTree(Node node) {
		if (!node)return nullptr;
		Node tmp = node;
		while (tmp->_rChild!= nullptr) {
			tmp = tmp->_rChild;
		}
		return tmp;
	}



	void _InsertNode(NodeRef curNode, ElemType elem) {
		if (curNode == nullptr) {
			curNode = new BSTNode<ElemType>();
			curNode->_elem = elem;
			curNode->_lChild = nullptr;
			curNode->_rChild = nullptr;
			return;
		}

		if (elem < curNode->_elem) {
			_InsertNode(curNode->_lChild, elem);
		}
		else {
			_InsertNode(curNode->_rChild, elem);
		}
	}



	void _VisitNode(Node curNode) {
		if (!curNode)return;
		std::cout << curNode->_elem << " ";
	}


	void _PreOrderReCursion(Node curNode) {
		if (!curNode)return;
		_VisitNode(curNode);
		_PreOrderReCursion(curNode->_lChild);
		_PreOrderReCursion(curNode->_rChild);
	}

	void _InOrderReCursion(Node curNode) {
		if (!curNode)return;
		_InOrderReCursion(curNode->_lChild);
		_VisitNode(curNode);
		_InOrderReCursion(curNode->_rChild);
	}

	void _PostOrderReCursion(Node curNode) {
		if (!curNode)return;
		_PostOrderReCursion(curNode->_lChild);
		_PostOrderReCursion(curNode->_rChild);
		_VisitNode(curNode);
	}

	void _LevelOrder(Node headNode) {
		if (!headNode)return;
		std::queue<Node> _queue;
		Node cur = _head;
		_queue.push(cur);
		while (!_queue.empty()) {
			cur = _queue.front();
			_VisitNode(cur);
			_queue.pop();
			if (cur->_lChild)_queue.push(cur->_lChild);
			if (cur->_rChild)_queue.push(cur->_rChild);
		}
	}
private:
	Node _head;
};