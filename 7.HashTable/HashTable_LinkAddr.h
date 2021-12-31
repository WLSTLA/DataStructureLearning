#pragma once 
#include<iostream>

/*
	�����ϣ��ͻ����,��ϣ������ַ�洢
	ʱ�临�Ӷ�: �ڲ�������ϣ��ͻ��ǰ���£���ѯĳ���ڵ��Ч����O(1)
*/


/*
	Ͱ�ڵ�
	������ַ�洢���£�ÿ��������ͬ��ַ�Ĺؼ������ͬһ���Ӽ����У�ÿһ���Ӽ��ϳ�֮Ϊһ��Ͱ
*/
template<class KeyType,class ValType>
struct BucketNode {
	typedef BucketNode<KeyType, ValType>* bucketNode;
	BucketNode(const std::pair<KeyType, ValType>& inPair) :_pair(inPair) {};
	bucketNode _next;
	std::pair<KeyType, ValType> _pair;
};



template<class KeyType,class ValType>
struct TableNode {
	typedef BucketNode<KeyType, ValType>* bucketNode;
	TableNode() :_firstBucket(nullptr), _size(0){};
	bucketNode _firstBucket;
	size_t _size;	//��¼Ͱ�ĸ���
};


// Ĭ�ϴ���hash������ֵ�ĺ���
class DealInt {
public:
	size_t operator()(const int key) {
		return key;
	}
};


template<class KeyType,class ValType,class HashFuncDeal = DealInt>
class HashTableLinkAddr {
	typedef TableNode<KeyType, ValType>* _tableNode;
	typedef BucketNode<KeyType, ValType>* _bucketNode;
public:
	void CreateHashTableLinkAddr(size_t capacity,size_t primeNumber) {
		_table = new TableNode<KeyType, ValType>[capacity]();
		_capacity = capacity;
		_primeNumber = primeNumber;
	}

	~HashTableLinkAddr()
	{
		DestroyHashTableLinkAddr();
	}

	void DestroyHashTableLinkAddr() {
		if (!_table)return;
		for (size_t i = 0; i < _capacity; ++i) {
			auto bucketHead = _table[i]._firstBucket;
			auto nextBucket = bucketHead;
			while (bucketHead) {
				nextBucket = bucketHead->_next;
				delete bucketHead;
				bucketHead = nextBucket;
			}
		}
		delete[] _table;
		_table = nullptr;
	}

	void InsertElem(const std::pair<KeyType, ValType>& elem) {
		size_t hashIndex = _HashFunc(elem.first);
		std::cout << "��" << hashIndex << "�����µ�Ԫ��" << "\n";
		auto buket = new BucketNode<KeyType, ValType>(elem);
		_table[hashIndex]._size++;
		//ʹ��ͷ�巨
		buket->_next = _table[hashIndex]._firstBucket? _table[hashIndex]._firstBucket: nullptr;
		_table[hashIndex]._firstBucket = buket;
	}

	bool FindElem(const KeyType& key,ValType& valRet) {
		size_t hashIndex = _HashFunc(key);
		auto tableNode = _table[hashIndex];
		auto curBucket = tableNode._firstBucket;
		if (!curBucket) return false;
		while (curBucket) {
			if (curBucket->_pair.first == key) {
				valRet = curBucket->_pair.second;
				return true;
			}
			curBucket = curBucket->_next;
		}
		return false;
	}

	void PrintHashTable()const {
		if (!_table)return;
		for (size_t i = 0; i < _capacity; ++i) {
			auto bucketHead = _table[i]._firstBucket;
			if (!bucketHead)std::cout << i << ": valid";
			else std::cout << i << ":";
			while (bucketHead) {
				std::cout << "-->[k:" << bucketHead->_pair.first << " v:" << bucketHead->_pair.second << "]";
				bucketHead = bucketHead->_next;
			}
			std::cout << "\n";
		}
	}

	size_t GetBuckets()const{
		if (!_table)return 0;
		size_t sum = 0;	
		for (size_t i = 0; i < _capacity; ++i) {
			sum += _table[i]._size;
		}
		return sum;
	}

	// �����ϣ����غ�����= �洢��Ԫ�ظ���/��
	float CalculateLoadFactor()const{
		if (!_table)return 0.f;
		return (float)GetBuckets() / _capacity;
	}

protected: 
	size_t _HashFunc(const KeyType key){
		return DealInt()(key) % _primeNumber;	//��ϣ����ʹ�ó���������
	}
private:
	size_t _capacity;	//����
	size_t _primeNumber;	//�����������еĳ�����
	_tableNode _table;
};


