#pragma once
#include<iostream>
#include<string>
using std::string;
using std::cout;

/*
	�ֵ���
	��һ�������������ڱ���������飬���еļ�ͨ�����ַ�����������������ͬ��
	������ֱ�ӱ����ڽڵ��У������ɽڵ������е�λ�þ�����
	һ���ڵ���������ﶼ����ͬ��ǰ׺��Ҳ��������ڵ��Ӧ���ַ����������ڵ��Ӧ���ַ���
*/
const size_t MAX_CHILD_COUNT = 26;	//Ĭ��ΪСдӢ����ĸ��26��

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

	// �ж�ǰ׺�ַ����Ƿ����
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

	// �������ǰ׺�Ӵ�
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