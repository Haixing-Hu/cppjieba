#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <fstream>
//#include <ext/hash_map>
#include <map>
#include <cstring>
#include "cppcommon/str_functs.h"
#include "cppcommon/vec_functs.h"
#include "cppcommon/logger.h"
#include "globals.h"


namespace CppJieba
{
    using namespace CPPCOMMON;
    using namespace std;
    //using __gnu_cxx::hash_map;
    typedef uint16_t ChUnicode;
	const size_t ChUniMaxLen = 1024;
    typedef map<ChUnicode, struct TrieNode*> TrieNodeHashMap;

	struct TrieNodeInfo
	{
		string word;
		unsigned int count;
		string tag;
		TrieNodeInfo():word(),count(0),tag()
		{
		}
	};

	struct TrieNode
    {
        TrieNodeHashMap hmap;
        bool isLeaf;
		unsigned int nodeInfoVecPos;

        TrieNode()
        :hmap(), isLeaf(false), nodeInfoVecPos(0)
        {
        }
    };

    struct TrieNodeIterator
    {
        TrieNode* ptNode;
        
        TrieNodeIterator():ptNode(NULL)
        {
        }

        TrieNodeIterator(TrieNode* ptr):ptNode(NULL)
        {
            ptNode = ptr;
        }

        const int operator++(int)
        {
            return 1;
        }

        TrieNodeIterator& operator++()
        {
            return *this;
        }

        TrieNode& operator*() const
        {
            return *ptNode;
        }

        TrieNode* operator->() const
        {
            return ptNode;
        }
        
        bool operator==(const TrieNodeIterator& x) const
        {
            return ptNode == x.ptNode;
        }
        
        bool operator!=(const TrieNodeIterator& x) const
        {
            return ptNode != x.ptNode;
        }
    };

    class Trie
    {
        private:
            TrieNode* _root;
			vector<TrieNodeInfo> _nodeInfoVec;
        public:
            typedef TrieNodeIterator iterator;

        public:
            iterator begin();
            iterator end();

        public:
            Trie();
            ~Trie();
            bool init(const char* const filepath = DICT_FILE_PATH);
            bool destroy();
            void display();

		public:
            bool find(const ChUnicode* chUniStr, size_t len);
			//bool find(const vector<ChUnicode>& uniVec);
			int findMaxMatch(const ChUnicode* chUniStr, size_t len);

		public:
            bool cut(const ChUnicode* chUniStr, size_t len, vector< vector<size_t> >& res);
			//bool cutUni(const vector<ChUnicode>& uniVec, )
			bool cutUtf8(const string& str, vector< vector<size_t> >& res);
			//bool cutMa

        private:
            bool _destroyNode(TrieNode* node);
            void _display(TrieNode* node, int level);
			bool _insert(const TrieNodeInfo& nodeInfo);

		private:
			enum {bufSize = 1024};
    };
}

#endif
