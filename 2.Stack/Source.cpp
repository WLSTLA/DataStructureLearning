#include"SequnceStack.h"
#include"LinkListStack.h"

void SequnceStackTest() {
	SequnceStack<int>s;
	s.CreateStack();
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	s.PrintStack();
	s.Push(10);
	s.Pop();
	s.Push(12);
	std::cout << "s.Top():"<<s.Top() <<"s.Size()"<<s.Size()<<std::endl;
	s.PrintStack();
}

void LinkListStackTest() {
	LinkListStack<int>s;
	s.CreateStack();
	s.Push(1);
	s.Push(2);
	s.Push(1);
	s.Push(2);
	s.Push(1);
	s.Push(2);
	s.Push(1);
	s.Push(2);
	s.Pop();
	s.Pop();
	std::cout << s.Size() << std::endl;
	s.PrintStack();
}

int main() {
	//SequnceStackTest();
	LinkListStackTest();
	return 0;
}