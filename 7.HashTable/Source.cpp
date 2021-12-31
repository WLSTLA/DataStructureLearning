#include"HashTable_LinkAddr.h"


void test01() {
	HashTableLinkAddr<int, int> s;
	s.CreateHashTableLinkAddr(5, 3);
	s.InsertElem(std::make_pair(5, 20));
	s.InsertElem(std::make_pair(4, 99));
	s.InsertElem(std::make_pair(3, 12));
	s.InsertElem(std::make_pair(2, 22));
	s.InsertElem(std::make_pair(1, 23));
	s.InsertElem(std::make_pair(8, 23));
	s.InsertElem(std::make_pair(10, 23));
	s.InsertElem(std::make_pair(9, 23));
	s.PrintHashTable();

	int val;
	std::cout << "查找key=10,成功:" << s.FindElem(10,val);
	if (s.FindElem(10, val)) {
		std::cout << " val = " << val << "\n";
	}
	std::cout << "桶的数量:" << s.GetBuckets() << "\n";
	std::cout << "载荷因子:" << s.CalculateLoadFactor() << "\n";
}

int main() {
	test01();
	return 0;
}