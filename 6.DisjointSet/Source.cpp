#include"DisjoinSet_Array.h"



void UnionSetArrayTest() {
	UnionSetArray s;
	s.InitUnionSetArray();
	s.UnionElement(2, 4);
	s.UnionElement(5, 2);
	s.UnionElement(10, 2);
	s.UnionElement(15, 10);
	std::cout << "15 �� 4 �Ƿ�Ϊͬһ����:" << s.IsConnected(15, 4) << "\n";
}


int main() {
	UnionSetArrayTest();
	return 0;
}