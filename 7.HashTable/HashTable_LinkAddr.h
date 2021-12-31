#pragma once 
#include<iostream>

/*
	处理哈希冲突采用,哈希表链地址存储
	时间复杂度: 在不产生哈希冲突的前提下，查询某个节点的效率是O(1)
*/


/*
	桶节点
	在链地址存储法下，每个具有相同地址的关键码归于同一个子集合中，每一个子集合称之为一个桶
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
	size_t _size;	//记录桶的个数
};


// 默认处理hash函数键值的函数
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
		std::cout << "在" << hashIndex << "插入新的元素" << "\n";
		auto buket = new BucketNode<KeyType, ValType>(elem);
		_table[hashIndex]._size++;
		//使用头插法
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

	// 计算哈希表的载荷因子= 存储的元素个数/表长
	float CalculateLoadFactor()const{
		if (!_table)return 0.f;
		return (float)GetBuckets() / _capacity;
	}

protected: 
	size_t _HashFunc(const KeyType key){
		return DealInt()(key) % _primeNumber;	//哈希函数使用除留余数法
	}
private:
	size_t _capacity;	//容量
	size_t _primeNumber;	//除留余数法中的除素数
	_tableNode _table;
};


