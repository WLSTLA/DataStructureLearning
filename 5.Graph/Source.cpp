#include"DireGrapth_Table.h"
#include"NondireGraph_Matrix.h"
#include"Traverse_DirecGrapth.h"
#include"Traverse_NonDirec.h"
#include"MST_Prim.h"
#include"MST_Kruskal.h"
#include"MinPath_BFS.h"
#include"MinPath_Dijkstra.h"
#include"MinPath_Floyd.h"
//�洢�ṹ
void NondireGrapthMatrxitTest() {
	NonDireGrapth_Matrix<char> s;
	int arr[4][4] = {
		{0,100,1,1},
		{1,0,0,1},
		{0,1,1,1},
		{0,1,1,1},
	};
	int* ptr = &arr[0][0];
	char vertex[] = { 'A','B','C','D' };
	char* p = vertex;
	s.SpawnGrapth(4,&ptr,&p);
	s.printGrapth();

	std::cout << "����A�ĵ�һ���ھ��Ƕ���" << s.GetVertexs()[s.FirstNeighbor('A')] << "\n";
	std::cout << "����A,���˶���B֮�����һ���ھӶ����Ƕ���:" << s.GetVertexs()[s.NextNeighbor('A', 'B')] << "\n";
	std::cout << "����A�Ͷ���B֮���·��ȨֵΪ:" << s.GetEdgeWight('A', 'B')<< "\n";
	std::cout << "����A�Ͷ���C�Ƿ���ڱ�:" << s.Adjacent('A', 'C') << "\n";
	s.DeleteEdge('A', 'B');
	s.printGrapth();
	s.AddEdge('A', 'B', 999);
	s.printGrapth();
}
void DireGrapthTableTest() {
	DireGraphTable<char, int>s;
	char arr[] = { 'A','B','C'};
	s.CreateDireGraphTable(3,arr);
	s.AddEdge('A', 'B', 30);
	s.PrintDireGraphTable();
	s.DeleteEdge('A','B');
	s.AddEdge('A', 'B', 120);
	s.AddEdge('B', 'C', 300);
	s.AddEdge('A', 'C', 500);
	s.PrintDireGraphTable();
	s.DeleteEdge('A', 'C');
	s.DeleteEdge('B', 'C');
	s.PrintDireGraphTable();
}

// ����
void NonDireTraverseTest() {
	// �ڽӾ���洢
	/*
	{
		NonDireGrapthMatrixTraverse s;
		int vertexs[] = { 0,1,2,3,4 };
		int edges[][5] = {
			{0,1,1,1,0},
			{1,0,0,1,0},
			{1,0,0,0,0},
			{1,1,0,0,1},
			{0,0,0,1,0},
		};
		s.InitNonDireGrapthMatrixTraverse(vertexs, edges);
		s.PrintNonDireGrapthMatrixBFS();
		std::cout << "first neighbor:" << s.GetFirstNeighbor(0) << "\n";	//3
		std::cout << "next neighbor:" << s.GetNextNeighbor(0, 3) << "\n";
		std::cout << "BFS\n";
		s.BFSTraverse(0);	//0 1 2 3 4
		s.BFSTraverse(1);	//1 0 3 2 4
		s.BFSTraverse(2);	//2 0 1 3 4
		s.BFSTraverse(3);	//3 0 1 4 2

		std::cout << "DFS\n";
		s.DFSTraverse(0);	//0 1 3 4 2
		s.DFSTraverse(1);	//1 0 2 3 4
		s.DFSTraverse(2);	//2 0 1 3 4
		s.DFSTraverse(3);	//3 0 1 2 4
		s.DFSTraverse(4);	//4 3 0 1 2
	}
	*/
	
	// �ڽӱ�洢
	NonDireGrapthTableTraverse s;
	s.InitNonDireGrapthTableTraverse();
	s.InsertEdge(0, 1, 20);
	s.InsertEdge(0, 2, 30);
	s.InsertEdge(0, 3, 40);
	s.InsertEdge(1, 3, 5);
	s.InsertEdge(3, 4, 50);
	s.PrintNonDireGrapthTable();

	//std::cout << "����0�ĵ�һ���ڽӶ���" << s._GetFirstNeighbor(0) << "\n";
	//std::cout << "����0��1�ڽ���һ���ڽӶ���" << s._GetNextNeighbor(0,2) << "\n";
	std::cout << "BFS\n";
	s.BFSTraverse(0);	
	s.BFSTraverse(1);	
	s.BFSTraverse(2);		
	s.BFSTraverse(3);
	s.BFSTraverse(4);
	std::cout << "DFS\n";
	s.DFSTraverse(0);
	s.DFSTraverse(1);
	s.DFSTraverse(2);
	s.DFSTraverse(3);
	s.DFSTraverse(4);
}

// ��С������
void SpinningTreeTest() {
	// prim
	{
		MinSpinningTreePrimMtrix s;
		int edge[][6] = {
			{0,6,5,1,0,0},
			{6,0,0,5,3,0},
			{5,0,0,4,0,2},
			{1,5,4,0,6,4},
			{0,3,0,6,0,6},
			{0,0,2,4,6,0}
		};
		//s.CreateMinSpinningTreePrimMtrix(edge);
		//std::cout << "��С����������:" << s.MinSpinningTreePRIM(2) << "\n";
	}

	// kruskal
	{
		int edge[][6] = {
			{0,6,5,1,0,0},
			{6,0,0,5,3,0},
			{5,0,0,4,0,2},
			{1,5,4,0,6,4},
			{0,3,0,6,0,6},
			{0,0,2,4,6,0}
		};
		MinSpinningTreeKruskalMtrix s;
		s.CreateMinSpinningTreePrimMtrix(edge);
		s.PrintPriorityEdges();
		std::cout << "��С����������Ϊ:"<<s.Kruskal() << "\n";
	}
}

// ��Դ���·��
void MinPathBFSTest() {
	int arr[][5] = {
		{0,1,1,0,1},
		{1,0,1,1,0},
		{1,1,0,1,0},
		{0,1,1,0,1},
		{1,0,1,1,0}
	};
	MinPathBFS s;
	s.CreateMinPathBFS(arr);
	s.BFSFindMinPath(0);
	//s.PrintMinPathInfo();
}

void MinPathDijkstraTest() {
	int arr[][5] = {
		{0, 10, INFINIT, INFINIT, 5},
		{ INFINIT,0,1,INFINIT,2 },
		{ INFINIT,INFINIT,0,4,INFINIT },
		{ 7,INFINIT,6,0,INFINIT },
		{ INFINIT,3,9,2,0 }
	};
	MinPathDijkstra s;
	s.CreateMinPathDijkstra(arr);
	s.DijkstraFindMinPath(1);
}

void MinPathFloydTest() {
	int arr[][5] = {
	{0, INFINIT, 1, INFINIT, 10},
	{ INFINIT,0,INFINIT,1,5},
	{ INFINIT,1,0,INFINIT,7 },
	{ INFINIT,INFINIT,INFINIT,0,1 },
	{ INFINIT,INFINIT,INFINIT,INFINIT,0 }
	};

	int path[][5] = {
		{-1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1}
	};
	MinPathFloyd s;
	s.CreateMinPathFloyd(arr, path);
	s.MinDistanceFloyd();
	s.GetMinDisByVertexIndex(0,4);
	s.PrintMinDisMatrix();
	s.PrintPathMatrix();
}
int main() {
	//NondireGrapthMatrxitTest();
	//DireGrapthTableTest();
	//NonDireTraverseTest();
	
	//SpinningTreeTest();

	//MinPathBFSTest();
	//MinPathDijkstraTest();
	MinPathFloydTest();
	return 0;
}