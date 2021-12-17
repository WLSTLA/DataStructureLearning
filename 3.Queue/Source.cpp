#include"LinkListQueue.h"
#include"SequnceQueue.h"
#include"Deque.h"

void SequnceQueueTest() {
	SequnceQueue<int>s;
	s.CreateQueue();
	s.EnQueue(3);
	s.EnQueue(4);
	s.EnQueue(5);
	s.EnQueue(6);
	s.EnQueue(7);
	std::cout << s.Top() << std::endl;
	int a;
	//s.DeQueue(a);
	//std::cout << "a:" << a << std::endl;
	std::cout << s.Top() << std::endl;
	s.PrintQueue();
	std::cout << "\n";
	s.EnQueue(9);
	s.EnQueue(10);
	s.PrintQueue();
}

void LinkListQueueTest() {
	LinkListQueue<int>s;
	s.CreateQueue();
	s.EnQueue(1);
	s.EnQueue(2);
	s.EnQueue(3);
	s.EnQueue(4);
	std::cout << "s.Top():" << s.Top() << std::endl;
	s.PrintQueue();
	std::cout << "\n";
	int a;
	s.DeQueue(a);
	s.DeQueue(a);
	s.PrintQueue();

	std::cout << "\n";
	s.DeQueue(a);
	s.DeQueue(a);
	s.PrintQueue();
}

void DequeTest() {
	Deque<int>s;
	s.CreateDeque();
	s.EnQueueFront(2);
	s.EnQueueFront(3);
	s.EnQueueFront(4);
	s.EnQueueRear(9);
	s.PrintDeque();

	int x;
	s.DeQueueFront(x);
	s.DeQueueRear(x);
	s.DeQueueFront(x);
	s.DeQueueRear(x);
	s.DeQueueRear(x);
	s.PrintDeque();
	std::cout << "s.Length():" << s.GetLength() << std::endl;
	s.EnQueueFront(999);
	s.EnQueueRear(1000);
	s.PrintDeque();
}

int main() {
	//SequnceQueueTest();
	//LinkListQueueTest();
	DequeTest();
	return 0;
}