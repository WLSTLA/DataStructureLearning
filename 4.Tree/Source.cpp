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
	std::cout << "深度:" << t.GetTreeDepth() << "\n";
	t.TraverseTree(TRAVERSEMODE::LevelOrder);
	std::cout << "节点个数:" << t.GetTreeNodeNums() << "\n";
	std::cout << "叶子节点个数:" <<t.GetLeafNums()<< "\n";
	std::cout << "显示叶子节点:\n";
	t.DispLeaf();
	std::cout << "\n";
	TreeNode node = t.FindNode('c');
	if (node) {
		std::cout << "节点c的左孩子:" << node->_lChild->_data << "\n";
		std::cout << "节点c的右孩子:" << node->_rChild->_data << "\n";
	}
	std::cout << "非递归前序遍历:\n";
	t.PreOrder(); //非递归前序遍历
	std::cout << "\n非递归中序遍历:\n";
	t.InOrder();  //非递归中序遍历
	std::cout << "\n非递归后序遍历:\n";
	t.PostOrder();  //非递归后序遍历
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

	std::cout << "树的高度:" << s.CalculateSubTreeHeight(head) << "\n";
	std::cout << "头节点平衡因子:" << s.CalculateBalanceFactor(head) << "\n";
	std::cout << "是否平衡:" << s.IsBalanced() << "\n";

	bool isLeftChild;
	auto node = s.GetNode(20);
	if (node) {
		std::cout << "获取节点:" << node->_data << "\n";
		auto parent = s.GetNodeParent(node, &isLeftChild);
		if (parent) {
			std::cout << "node节点的父节点是:" << parent->_data << "\n";
		}
	}
	auto node2 = s.GetNode(10);
	if (node2) {
		std::cout << "获取节点:" << node2->_data << "\n";
		if (node2->_lChild) {
			std::cout << "node10 左孩子:" << node2->_lChild->_data << "\n";
		}
		if (node2->_rChild) {
			std::cout << "node10 右孩子:" << node2->_rChild->_data << "\n";
		}
	}
	auto node3 = s.GetNode(4);
	std::cout << "节点" << node3->_data << "中的最大节点为:" << s.GetMaxNode(node3)->_data << "\n";
	std::cout << "节点" << node3->_data << "中的最小节点为:" << s.GetMinNode(node3)->_data << "\n";

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
		std::cout << "节点" << node->_weight << "的父节点是" << node->_parent->_weight << "\n";
		std::cout << "该节点的路劲长度为:" << s.GetNodePathLength(node) << "\n";
		std::cout << "该节点的带权路径长度为:" << s.GetNodeWPL(node) << "\n";
	}
	s.printLeaf();
	std::cout << "树的带权路径长度为:" << s.GetTreeWPL() << "\n";
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