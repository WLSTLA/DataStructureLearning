#pragma once
#include<iostream>
#include<string>
using std::string;
using std::cout;

/*
	字典树
	是一种有序树，用于保存关联数组，其中的键通常是字符串。与二叉查找树不同，
	键不是直接保存在节点中，而是由节点在树中的位置决定。
	一个节点的所有子孙都有相同的前缀，也就是这个节点对应的字符串，而根节点对应空字符串
*/
const size_t MAX_CHILD_COUNT = 26;	//默认为小写英语字母，26个

struct TrieNode {
	TrieNode() {
		_IsEndWord = true;
		for (size_t i = 0; i < MAX_CHILD_COUNT; ++i) {
			_child[i] = nullptr;
		}
	}
	bool _IsEndWord;
	TrieNode* _child[MAX_CHILD_COUNT];
	string _str;
};


class Trie {
public:
	void InitTrie() {
		_root = new TrieNode();
	}

	void InsertStr(const char* str) {
		if (!_root)return;
		TrieNode* cur = _root;
		std::string preChar;
		for (size_t i = 0; str[i]; ++i) {
			size_t index = str[i] - 'a';		
			if (cur->_child[index] == nullptr) {
				cur->_child[index] = new TrieNode();
				preChar = cur->_str;
			}
			cur = cur->_child[index];
		}
		cur->_str = str;
		cur->_IsEndWord = true;
	}

	bool FindStr(const char* str) {
		if (!_root)return false;
		TrieNode* cur = _root;
		for (size_t i = 0; str[i]; ++i) {
			size_t index = str[i] - 'a';
			if (cur->_child[index] == nullptr) {
				return false;
			}
			cur = cur->_child[index];
		}
		return cur->_IsEndWord;
	}

	// 判断前缀字符串是否存在
	bool IsPrefixExist(const char* str) {
		if (!_root)return false;
		TrieNode* cur = _root;
		for (size_t i = 0; str[i]; ++i) {
			size_t index = str[i] - 'a';
			if (cur->_child[index] == nullptr) {
				return false;
			}
			cur = cur->_child[index];
		}
		return true;
	}

	// 输出所有前缀子串
	bool PrintAllPrefixSubStr(const char* str) {
		if (!_root)return false;
		TrieNode* cur = _root;
		for (size_t i = 0; str[i]; ++i) {
			size_t index = str[i] - 'a';
			if (cur->_child[index] != nullptr && cur->_child[index]->_IsEndWord == true) {
				std::cout << cur->_child[index]->_str << " ";
			}
			cur = cur->_child[index];
		}
	}


	void test(const char* str) {
		if (!_root)return;
		TrieNode* cur = _root;
		for (size_t i = 0; str[i]; ++i) {
			size_t index = str[i] - 'a';
			if (cur->_child[index] == nullptr) {
				return;
			}
			cur = cur->_child[index];
		}
		std::cout << cur->_str << "\n";
	}
private:
	TrieNode* _root;
};