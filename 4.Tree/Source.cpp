#include"BinaryTree.h"
#include"BinarySearchTree.h"
#include"AVLTree.h"
#include"ClueBinaryTree.h"
#include"HuffManTree.h"
#include"Heap.h"

void BinaryTreeTest() {
	typedef BinaryTreeNode<char>* TreeNode;
	BinaryTree<char>t;
	TreeNode head = t.InitBinaryTree();

	t.CreateFullBinaryTree(3);
	std::cout << "���:" << t.GetTreeDepth() << "\n";
	t.TraverseTree(TRAVERSEMODE::LevelOrder);
	std::cout << "�ڵ����:" << t.GetTreeNodeNums() << "\n";
	std::cout << "Ҷ�ӽڵ����:" <<t.GetLeafNums()<< "\n";
	std::cout << "��ʾҶ�ӽڵ�:\n";
	t.DispLeaf();
	std::cout << "\n";
	TreeNode node = t.FindNode('c');
	if (node) {
		std::cout << "�ڵ�c������:" << node->_lChild->_data << "\n";
		std::cout << "�ڵ�c���Һ���:" << node->_rChild->_data << "\n";
	}
	std::cout << "�ǵݹ�ǰ�����:\n";
	t.PreOrder(); //�ǵݹ�ǰ�����
	std::cout << "\n�ǵݹ��������:\n";
	t.InOrder();  //�ǵݹ��������
	std::cout << "\n�ǵݹ�������:\n";
	t.PostOrder();  //�ǵݹ�������
	//BinaryTreeNode<char> b = { nullptr,nullptr,'b' };
	//BinaryTreeNode<char> c = { nullptr,nullptr,'c' };
	//BinaryTreeNode<char> d = { nullptr,nullptr,'d' };
	//BinaryTreeNode<char> e = { nullptr,nullptr,'e' };
	//BinaryTreeNode<char> f = { nullptr,nullptr,'f' };
	//BinaryTreeNode<char> g = { nullptr,nullptr,'g' };
	//head->_data = 'a';
	//head->_lChild = &b;
	//head->_rChild = &c;
	//b._lChild = &d;
	//b._rChild = &e;
	//c._lChild = &f;
	//c._rChild = &g;

	//t.TraverseTree(TRAVERSEMODE::PreOrder);
	//t.TraverseTree(TRAVERSEMODE::InOrder);
	//t.TraverseTree(TRAVERSEMODE::PostOrder);
	//std::cout << "depth:" << t.GetTreeDepth() << "\n";
	//t.TraverseTree(TRAVERSEMODE::LevelOrder);
}

void BinarySearchTest() {
	BSTree<int>s;
	int arr[] = { 5,1,2,4,8 };
	size_t size = sizeof(arr) / sizeof(int);
	s.CreateBSTree(arr,size);
	s.LevelOrder();
	std::cout << "\n";
	std::cout << "max:" << s.GetMaxNode()->_elem << "\n";
	std::cout << "min:" << s.GetMinNode()->_elem << "\n";
	s.InsertNode(10);
	std::cout << "max:" << s.GetMaxNode()->_elem << "\n";
	s.InOrderRecursion(); 
	s.DeleteElem(10);
	s.DeleteElem(1);
	s.DeleteElem(5);

	std::cout << "\n";
	s.InOrderRecursion();
}

void ClueBinaryTreeTest() {
	ClueBinaryTree<char> s;
	s.InitTree();
	s.CreateFullBinaryTree(3);
	s.CreateInOrderClueTree();
	auto elem = s.FindElem('e');
	std::cout << elem->_rChild->_data << "\n";
	s.TraverseInOrderClueTree();
	std::cout << "\n";
}

void AVLTreeTest() {
	AVLTree<int> s;
	s.InitAVLTree();
	int arr[] = { 3,1,2,4,5,10,20 };
	size_t length = sizeof(arr) / sizeof(int);
	auto head = s.CreateAVLTree(arr,length);
	s.InOrderTraverse();

	std::cout << "���ĸ߶�:" << s.CalculateSubTreeHeight(head) << "\n";
	std::cout << "ͷ�ڵ�ƽ������:" << s.CalculateBalanceFactor(head) << "\n";
	std::cout << "�Ƿ�ƽ��:" << s.IsBalanced() << "\n";

	bool isLeftChild;
	auto node = s.GetNode(20);
	if (node) {
		std::cout << "��ȡ�ڵ�:" << node->_data << "\n";
		auto parent = s.GetNodeParent(node, &isLeftChild);
		if (parent) {
			std::cout << "node�ڵ�ĸ��ڵ���:" << parent->_data << "\n";
		}
	}
	auto node2 = s.GetNode(10);
	if (node2) {
		std::cout << "��ȡ�ڵ�:" << node2->_data << "\n";
		if (node2->_lChild) {
			std::cout << "node10 ����:" << node2->_lChild->_data << "\n";
		}
		if (node2->_rChild) {
			std::cout << "node10 �Һ���:" << node2->_rChild->_data << "\n";
		}
	}
	auto node3 = s.GetNode(4);
	std::cout << "�ڵ�" << node3->_data << "�е����ڵ�Ϊ:" << s.GetMaxNode(node3)->_data << "\n";
	std::cout << "�ڵ�" << node3->_data << "�е���С�ڵ�Ϊ:" << s.GetMinNode(node3)->_data << "\n";

	s.DeleteElem(10);
	s.DeleteElem(5);
	s.DeleteElem(20);
	s.InOrderTraverse();
}

void HuffTreeTest() {
	HuffTree<int>s;
	int arr[] = {3,18,20,5,9,6,7,7,8};
	size_t length = sizeof(arr) / sizeof(int);
	s.CreateHuffTree(arr, length);
	auto node = s.FindNode(3);
	if (node) {
		std::cout << "�ڵ�" << node->_weight << "�ĸ��ڵ���" << node->_parent->_weight << "\n";
		std::cout << "�ýڵ��·������Ϊ:" << s.GetNodePathLength(node) << "\n";
		std::cout << "�ýڵ�Ĵ�Ȩ·������Ϊ:" << s.GetNodeWPL(node) << "\n";
	}
	s.printLeaf();
	std::cout << "���Ĵ�Ȩ·������Ϊ:" << s.GetTreeWPL() << "\n";
}


bool IntCmp(const int* val1, const int* val2) {
	return *val1 > *val2;
}

void HeapTest() {
	SqHeap<int> s(10,&IntCmp);
	int arr[] = { 2,4,1,6,2,8,10,20 };
	size_t length = sizeof(arr) / sizeof(int);
	for (size_t i = 0; i < length; ++i) {
		s.InsertElem(arr[i]);
	}
	s.printHeap();
	std::cout << "top:" << s.GetTop() << "\n";

	s.InsertElem(30);
	s.printHeap();
	s.Pop();
	s.printHeap();
	s.Pop();
	s.printHeap();
}

int main() {
	//BinaryTreeTest();
	//BinarySearchTest();
	//ClueBinaryTreeTest();
	//AVLTreeTest();
	//HuffTreeTest();
	HeapTest();
	return 0;
}