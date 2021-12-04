// https://leetcode.com/problems/stream-of-characters/

class TrieNode {
    
    TrieNode* children[26] = {};
    bool isWord = false;

public:
    
    void addWordInReverseOrder(string& word) {
        TrieNode* cur = this;
        for (int i = word.size() - 1; i >= 0; --i) {
            char c = word[i] - 'a';
            if (cur->children[c] == nullptr)
                cur->children[c] = new TrieNode();
            cur = cur->children[c];
        }
        cur->isWord = true;
    }

    bool search(string& pattern) {
        TrieNode* cur = this;
        for (int i = pattern.size() - 1; i >= 0; --i) {
            char c = pattern[i] - 'a';
            if (cur->children[c] == nullptr) return false;
            cur = cur->children[c];
            if (cur->isWord) return true;
        }
        return false;
    }
};

class StreamChecker {
public:
    string typed = "";
    TrieNode trieRoot;
    StreamChecker(vector<string>& words) {
        for (string& word : words) {
            trieRoot.addWordInReverseOrder(word);
        }
    }

    bool query(char letter) {
        typed.push_back(letter);
        return trieRoot.search(typed);
    }
};
